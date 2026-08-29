#!/usr/bin/env bash
#
# Integration test: many template derived libraries inside a single
# application.
#
# The test answers the question the template alone can not: may an application
# depend on more than one library derived from this `lib` branch at once? It
# generates a configurable amount of whole derived projects, gives every one of
# them its own top level CMake project name (the base name with the generation
# index appended), builds and installs each of them, and then builds a single
# application which links all of them at once and drives every library through
# a cycle.
#
# Every generated library returns `the given number + its own generation index`,
# so an application which receives the same answer from two different libraries
# has silently bound both calls to the same implementation - which is exactly
# what identical symbols in every derived library cause.
#
# Every generated project performs the by-hand renames the template asks a
# derived project for - the public namespace with its include guard stamp and
# the implementation namespace - so the test drives the very same rename
# procedure the documentation describes.
#
# The test also asserts that no library opens a log file of its own: the
# logging destination belongs to the application which uses the libraries, not
# to the libraries themselves.
#
# The logging destination is handed over the only way a library user really has
# it - through the installed public LibraryFacade::init_logger of every library.
# The application implements the installed logger::ILogger once and every
# library must answer into that single instance, so the test covers the
# installed header surface and not the build tree one: an interface which is
# not installed alongside the library can not be implemented by its user at all.
#
# The test then hands every library a logger of its OWN and asserts that none of
# them receives the messages of another. Every derived library carries a copy of
# the whole logging subsystem under one and the same default_logger namespace,
# so the copies are kept apart by the hidden symbol visibility of the library
# alone: were those symbols exported, the libraries would share a single real
# logger instance holder, one logger would collect everything while the rest
# stay silent, and the logger one library adopted would silently serve the
# others too.

set -euo pipefail

readonly SCRIPT_NAME="$(basename "${BASH_SOURCE[0]}")"

# The number handed over to every library. Each one must answer with
# BASE_NUMBER + <its own index>.
readonly BASE_NUMBER=1000

SOURCE_DIR=""
WORK_DIR=""
LIBS_COUNT=100
BUILD_JOBS="$(nproc 2>/dev/null || echo 4)"

usage()
{
  cat <<USAGE
Usage: ${SCRIPT_NAME} --source-dir DIR --work-dir DIR [--count N] [--jobs N]

  --source-dir DIR  the template project checkout to derive the libraries from
  --work-dir DIR    the scratch directory for the generated projects
  --count N         count of the libraries to generate (default ${LIBS_COUNT})
  --jobs N          parallel build jobs (default ${BUILD_JOBS})
USAGE
}

fail()
{
  echo "FAIL: $*" >&2
  exit 1
}

info()
{
  echo "[${SCRIPT_NAME}] $*"
}

parse_args()
{
  while [ "$#" -gt 0 ]; do
    case "$1" in
      --source-dir) SOURCE_DIR="${2:-}"; shift 2 ;;
      --work-dir)   WORK_DIR="${2:-}";   shift 2 ;;
      --count)      LIBS_COUNT="${2:-}"; shift 2 ;;
      --jobs)       BUILD_JOBS="${2:-}"; shift 2 ;;
      -h|--help)    usage; exit 0 ;;
      *)            usage >&2; fail "unknown argument: $1" ;;
    esac
  done

  [ -n "${SOURCE_DIR}" ] || { usage >&2; fail "no --source-dir given"; }
  [ -n "${WORK_DIR}" ]   || { usage >&2; fail "no --work-dir given"; }
  [ -f "${SOURCE_DIR}/CMakeLists.txt" ] || \
    fail "no CMakeLists.txt inside the --source-dir ${SOURCE_DIR}"
  [ "${LIBS_COUNT}" -ge 1 ] || fail "the --count must be a positive number"
}

# The top level CMake project name of the generated library with the given
# index. It drives the installed library name and the installed headers
# directory; the C++ namespaces are renamed after it by hand below.
lib_project_name() { echo "CppAppTemplateLib$1"; }

# The PROJECT_LIBRARY_NAME the template derives from the project name and the
# project version. The minor version segment is a part of it by default.
lib_target_name() { echo "$(lib_project_name "$1")-0.12"; }

# The library public C++ namespace, renamed by hand the way the template asks a
# derived project to rename it.
lib_namespace() { echo "$(lib_project_name "$1")012"; }

# The include guard stamp of the public headers, renamed along with it.
lib_guard() { echo "CPP_APP_TEMPLATE_LIB$1_012_"; }

# The library implementation C++ namespace, renamed along with them: it never
# leaves the shared object, but its weak template instantiations may.
lib_impl_namespace() { echo "lib$1impl"; }

prepare_work_dir()
{
  rm -rf "${WORK_DIR}"
  mkdir -p "${WORK_DIR}"

  GEN_DIR="${WORK_DIR}/generated"
  INSTALL_DIR="${WORK_DIR}/install"
  APP_DIR="${WORK_DIR}/app"
  RUN_DIR="${WORK_DIR}/run"

  mkdir -p "${GEN_DIR}" "${INSTALL_DIR}" "${APP_DIR}" "${RUN_DIR}"
}

# Copies the template sources and turns the copy into an own project which
# implements `libcall` as `the given number + the generation index`.
generate_library_project()
{
  local index="$1"
  local name dst

  name="$(lib_project_name "${index}")"
  dst="${GEN_DIR}/${name}"

  mkdir -p "${dst}"

  # Only the library build inputs are copied. The doc/ subproject is dropped
  # together with its add_subdirectory call to keep the generation cheap.
  cp -R "${SOURCE_DIR}/CMakeLists.txt" "${SOURCE_DIR}/cmake" "${SOURCE_DIR}/src" \
    "${dst}/"

  sed -i '/add_subdirectory(doc)/d' "${dst}/CMakeLists.txt"

  # The whole point of the generation: give the project its own name, so the
  # template derives an own library name, an own installed headers directory
  # and an own library namespace out of it.
  sed -i "0,/^  CppAppTemplate$/s//  ${name}/" "${dst}/CMakeLists.txt"

  grep -q "^  ${name}$" "${dst}/CMakeLists.txt" || \
    fail "failed to rename the top level CMake project into ${name}"

  # The renames the template asks a derived project to perform by hand: the
  # public namespace and the include guard stamp of the public headers, which
  # an application naming two derived libraries at once has to tell apart, and
  # the implementation namespace, whose weak template instantiations may leave
  # the shared object even though the classes themselves do not. The logging
  # subsystem namespace is deliberately left alone - the hidden symbol
  # visibility of the library is what keeps those copies apart.
  grep -rl -e 'CppAppTemplate012' -e 'CPP_APP_TEMPLATE_012_' -e 'lib0impl' \
    "${dst}/src" | xargs sed -i \
      -e "s/CppAppTemplate012/$(lib_namespace "${index}")/g" \
      -e "s/CPP_APP_TEMPLATE_012_/$(lib_guard "${index}")/g" \
      -e "s/\blib0impl\b/$(lib_impl_namespace "${index}")/g"

  grep -q "namespace $(lib_namespace "${index}")$" \
    "${dst}/src/lib/facade/public/LibraryFacade.h" || \
    fail "failed to rename the public namespace of the ${name} library"

  # The library user passes a number in and reads the answer back, the way the
  # template asks for the LibraryContext fields to be introduced.
  sed -i \
    's|  // Introduce here the library required data fields.|  int number{0};\n  int result{0};\n|' \
    "${dst}/src/lib/facade/public/LibraryContext.h"

  # The library implementation itself. Every generated library answers with its
  # own generation index added to the given number.
  sed -i \
    "s|  LOGI(\"Your library implementation goes here!\");|  ctx->result = ctx->number + ${index};\n\n  LOGI(\"The library ${index} libcall\");|" \
    "${dst}/src/lib/libmain/LibMain.cpp"

  grep -q "ctx->result = ctx->number + ${index};" "${dst}/src/lib/libmain/LibMain.cpp" || \
    fail "failed to implement the libcall of the ${name} library"
}

build_library_project()
{
  local index="$1"
  local name build_dir log

  name="$(lib_project_name "${index}")"
  build_dir="${GEN_DIR}/${name}/build"
  log="${WORK_DIR}/${name}.build.log"

  {
    cmake -S "${GEN_DIR}/${name}" -B "${build_dir}" \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX="${INSTALL_DIR}" &&
    cmake --build "${build_dir}" -j1 &&
    cmake --install "${build_dir}"
  } > "${log}" 2>&1
}

generate_all_libraries()
{
  info "generating ${LIBS_COUNT} derived library projects in ${GEN_DIR}"

  local index

  for ((index = 0; index < LIBS_COUNT; ++index)); do
    generate_library_project "${index}"
  done
}

build_all_libraries()
{
  info "building and installing ${LIBS_COUNT} libraries with ${BUILD_JOBS} jobs"

  local index running=0

  for ((index = 0; index < LIBS_COUNT; ++index)); do
    build_library_project "${index}" &

    running=$((running + 1))

    if [ "${running}" -ge "${BUILD_JOBS}" ]; then
      wait -n || true
      running=$((running - 1))
    fi
  done

  wait

  for ((index = 0; index < LIBS_COUNT; ++index)); do
    local name
    name="$(lib_project_name "${index}")"

    if [ ! -f "${INSTALL_DIR}/lib/lib$(lib_target_name "${index}").so" ]; then
      echo "----- ${name} build log -----" >&2
      tail -40 "${WORK_DIR}/${name}.build.log" >&2 || true
      fail "the ${name} library was not built and installed"
    fi
  done
}

# The application which uses every generated library at once. Every library is
# wrapped into a uniform callable, so the libraries really are driven through a
# cycle and not through a hardcoded call sequence.
generate_application()
{
  info "generating the application which uses all the ${LIBS_COUNT} libraries"

  local main="${APP_DIR}/main.cpp"
  local index ns

  {
    echo '#include <cstddef>'
    echo '#include <functional>'
    echo '#include <iostream>'
    echo '#include <memory>'
    echo '#include <string>'
    echo '#include <vector>'
    echo

    for ((index = 0; index < LIBS_COUNT; ++index)); do
      echo "#include \"$(lib_target_name "${index}")/LibraryFacade.h\""
    done

    echo
    echo "namespace"
    echo "{"
    echo
    echo "// The application owned logger. It arrives at every library through"
    echo "// the public LibraryFacade::init_logger, and the logger::ILogger"
    echo "// interface it implements arrives through the installed public"
    echo "// headers of those very libraries."
    echo "class AppLogger : public logger::ILogger"
    echo "{"
    echo " public:"
    echo "  inline static const std::string lvlRepr{\"APP\"};"
    echo
    echo "  void log(const unsigned short& loglvl, const std::string& msg) override"
    echo "  {"
    echo "    lvls.push_back(loglvl);"
    echo "    msgs.push_back(msg);"
    echo "  }"
    echo
    echo "  void log(const unsigned short& loglvl, const char* const filePath,"
    echo "           const int& fileLine, const std::string& msg) override"
    echo "  {"
    echo "    log(loglvl,"
    echo "        std::string{filePath} + \":\" + std::to_string(fileLine) + \" : \" + msg);"
    echo "  }"
    echo
    echo "  void logfile(const std::string&) override {}"
    echo "  void print(const bool) override {}"
    echo "  void level(const unsigned short&) override {}"
    echo "  const std::string& lvl_repr(const unsigned short&) override"
    echo "  {"
    echo "    return lvlRepr;"
    echo "  }"
    echo "  void init(const std::string&, const unsigned short&, const bool) override {}"
    echo
    echo "  std::vector<unsigned short> lvls;"
    echo "  std::vector<std::string> msgs;"
    echo "};"
    echo
    echo "using LibCall = std::function<bool(int, int&)>;"
    echo "using LoggerInit = std::function<void(const logger::ILoggerPtr&)>;"
    echo
    echo "std::vector<LoggerInit> all_logger_inits()"
    echo "{"
    echo "  std::vector<LoggerInit> inits;"
    echo

    for ((index = 0; index < LIBS_COUNT; ++index)); do
      ns="$(lib_namespace "${index}")"

      echo "  inits.push_back(&${ns}::LibraryFacade::init_logger);"
    done

    echo
    echo "  return inits;"
    echo "}"
    echo
    echo "std::vector<LibCall> all_libcalls()"
    echo "{"
    echo "  std::vector<LibCall> libcalls;"
    echo

    for ((index = 0; index < LIBS_COUNT; ++index)); do
      ns="$(lib_namespace "${index}")"

      echo "  libcalls.push_back([](int number, int& result) {"
      echo "    auto ctx = ${ns}::LibraryFacade::create_library_context();"
      echo "    auto lib = ${ns}::LibraryFacade::create_default_lib();"
      echo "    if (!ctx || !lib) {"
      echo "      return false;"
      echo "    }"
      echo "    ctx->number = number;"
      echo "    if (!lib->libcall(ctx)) {"
      echo "      return false;"
      echo "    }"
      echo "    result = ctx->result;"
      echo "    return true;"
      echo "  });"
    done

    echo
    echo "  return libcalls;"
    echo "}"
    echo
    echo "}  // namespace"
    echo
    echo "int main()"
    echo "{"
    echo "  const auto appLogger = std::make_shared<AppLogger>();"
    echo "  const auto loggerInits = all_logger_inits();"
    echo
    echo "  // Every library adopts the very same application logger instance."
    echo "  for (const auto& initLogger : loggerInits) {"
    echo "    initLogger(appLogger);"
    echo "  }"
    echo
    echo "  const auto libcalls = all_libcalls();"
    echo "  int failures = 0;"
    echo
    echo "  for (std::size_t iter = 0U; iter < libcalls.size(); ++iter) {"
    echo "    const int expect = ${BASE_NUMBER} + static_cast<int>(iter);"
    echo "    int result = 0;"
    echo
    echo "    if (!libcalls[iter](${BASE_NUMBER}, result)) {"
    echo "      std::cerr << \"library \" << iter << \" libcall failed\\n\";"
    echo "      ++failures;"
    echo "      continue;"
    echo "    }"
    echo
    echo "    if (result != expect) {"
    echo "      std::cerr << \"library \" << iter << \" answered \" << result"
    echo "                << \" instead of \" << expect << '\\n';"
    echo "      ++failures;"
    echo "    }"
    echo "  }"
    echo
    echo "  // Every library must have logged into the application logger. A"
    echo "  // library which stays silent here kept an own logger instance"
    echo "  // instead of the adopted one."
    echo "  for (std::size_t iter = 0U; iter < libcalls.size(); ++iter) {"
    echo "    const std::string expect ="
    echo "        \"The library \" + std::to_string(iter) + \" libcall\";"
    echo "    bool found = false;"
    echo
    echo "    for (const auto& msg : appLogger->msgs) {"
    echo "      if (msg.find(expect) != std::string::npos) {"
    echo "        found = true;"
    echo "        break;"
    echo "      }"
    echo "    }"
    echo
    echo "    if (!found) {"
    echo "      std::cerr << \"library \" << iter"
    echo "                << \" never logged into the application logger\\n\";"
    echo "      ++failures;"
    echo "    }"
    echo "  }"
    echo
    echo "  // Every library must hold an OWN adopted logger instance. Give each"
    echo "  // of them a logger of its own and let none of them receive the"
    echo "  // messages of another: a shared logger holder makes a single logger"
    echo "  // collect everything while the rest stay empty."
    echo "  std::vector<std::shared_ptr<AppLogger>> ownLoggers;"
    echo
    echo "  for (const auto& initLogger : loggerInits) {"
    echo "    ownLoggers.push_back(std::make_shared<AppLogger>());"
    echo "    initLogger(ownLoggers.back());"
    echo "  }"
    echo
    echo "  for (std::size_t iter = 0U; iter < libcalls.size(); ++iter) {"
    echo "    int result = 0;"
    echo "    libcalls[iter](${BASE_NUMBER}, result);"
    echo "  }"
    echo
    echo "  for (std::size_t iter = 0U; iter < ownLoggers.size(); ++iter) {"
    echo "    const std::string expect ="
    echo "        \"The library \" + std::to_string(iter) + \" libcall\";"
    echo
    echo "    if (ownLoggers[iter]->msgs.size() != 1U) {"
    echo "      std::cerr << \"library \" << iter << \" own logger received \""
    echo "                << ownLoggers[iter]->msgs.size()"
    echo "                << \" messages instead of exactly 1 - the libraries \""
    echo "                << \"share a single logger holder\\n\";"
    echo "      ++failures;"
    echo "      continue;"
    echo "    }"
    echo
    echo "    if (ownLoggers[iter]->msgs.front().find(expect) == std::string::npos) {"
    echo "      std::cerr << \"library \" << iter"
    echo "                << \" own logger received a message of another \""
    echo "                << \"library: \" << ownLoggers[iter]->msgs.front() << '\\n';"
    echo "      ++failures;"
    echo "    }"
    echo "  }"
    echo
    echo "  std::cout << \"libraries called: \" << libcalls.size()"
    echo "            << \", log messages received: \" << appLogger->msgs.size()"
    echo "            << \", failures: \" << failures << '\\n';"
    echo
    echo "  return failures == 0 ? 0 : 1;"
    echo "}"
  } > "${main}"

  {
    echo 'cmake_minimum_required(VERSION 3.13)'
    echo
    echo 'project(ManyLibsApp LANGUAGES CXX)'
    echo
    echo 'set(CMAKE_CXX_STANDARD 17)'
    echo 'set(CMAKE_CXX_STANDARD_REQUIRED ON)'
    echo
    echo 'add_executable(many-libs-app main.cpp)'
    echo

    for ((index = 0; index < LIBS_COUNT; ++index)); do
      echo "find_package($(lib_target_name "${index}") REQUIRED)"
      echo "target_link_libraries("
      echo "  many-libs-app"
      echo "  $(lib_target_name "${index}")::$(lib_target_name "${index}")"
      echo ")"
    done
  } > "${APP_DIR}/CMakeLists.txt"
}

build_application()
{
  info "building the application against all the ${LIBS_COUNT} libraries"

  local log="${WORK_DIR}/app.build.log"

  if ! {
    cmake -S "${APP_DIR}" -B "${APP_DIR}/build" \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_PREFIX_PATH="${INSTALL_DIR}" > "${log}" 2>&1 &&
    cmake --build "${APP_DIR}/build" -j"${BUILD_JOBS}" >> "${log}" 2>&1
  }; then
    echo "----- application build log -----" >&2
    tail -60 "${log}" >&2 || true
    fail "the application which uses all the ${LIBS_COUNT} libraries fails to build"
  fi
}

run_application()
{
  info "calling every library libcall through a cycle"

  local out="${WORK_DIR}/app.run.log"
  local status=0

  # A dedicated empty directory: any log file which shows up here was opened by
  # a library and not by the application.
  ( cd "${RUN_DIR}" && \
    LD_LIBRARY_PATH="${INSTALL_DIR}/lib${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}" \
    "${APP_DIR}/build/many-libs-app" ) > "${out}" 2>&1 || status=$?

  cat "${out}"

  [ "${status}" -eq 0 ] || \
    fail "the libraries do not answer with their own generation index, or do not log into the application logger"
}

check_no_library_log_files()
{
  info "checking that no library opened a log file of its own"

  local logs

  logs="$(find "${RUN_DIR}" -type f -name '*.log' | sort)"

  if [ -n "${logs}" ]; then
    echo "${logs}" >&2
    fail "the libraries listed above opened own log files, while the logging destination belongs to the application"
  fi
}

main()
{
  parse_args "$@"

  prepare_work_dir
  generate_all_libraries
  build_all_libraries
  generate_application
  build_application
  run_application
  check_no_library_log_files

  info "PASS: ${LIBS_COUNT} derived libraries coexist in a single application"
}

main "$@"
