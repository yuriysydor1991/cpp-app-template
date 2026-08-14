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
# The test also asserts that no library opens a log file of its own: the
# logging destination belongs to the application which uses the libraries, not
# to the libraries themselves.

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
# index. It drives the installed library name, the installed headers directory
# and the library C++ namespace, so it is the only thing which makes the
# generated projects distinguishable.
lib_project_name() { echo "CppAppTemplateLib$1"; }

# The PROJECT_LIBRARY_NAME the template derives from the project name.
lib_target_name() { echo "$(lib_project_name "$1")-0"; }

# The library public C++ namespace the template derives from the project name.
lib_namespace() { echo "$(lib_project_name "$1")_0"; }

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

  # The library user passes a number in and reads the answer back, the way the
  # template asks for the LibraryContext fields to be introduced.
  sed -i \
    's|  // Introduce here the library required data fields.|  int number{0};\n  int result{0};\n|' \
    "${dst}/src/lib/facade/public/LibraryContext.h.in"

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
    echo '#include <vector>'
    echo

    for ((index = 0; index < LIBS_COUNT; ++index)); do
      echo "#include \"$(lib_target_name "${index}")/LibraryFacade.h\""
    done

    echo
    echo "namespace"
    echo "{"
    echo
    echo "using LibCall = std::function<bool(int, int&)>;"
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
    echo "  std::cout << \"libraries called: \" << libcalls.size()"
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
    fail "the libraries do not answer with their own generation index"
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
