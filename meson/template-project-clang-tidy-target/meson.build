clang_tidy_exec = find_program('clang-tidy', required: true)

# clang-tidy does not inherit the header search path of the compiler that
# produced the compilation database, so with a GCC toolchain it fails to locate
# the standard library headers. Ask the compiler for its implicit search list
# and hand it over, the way the CMake based branches pass the
# CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES contents to the very same tool.
# The GCC own headers (the intrinsics among them) call the GCC builtins clang
# does not know, so clang-tidy takes the ones of its own resource directory.
clang_tidy_implicit_includes_py = '''
import os, re, subprocess, sys

gcc_own = re.compile(r'/gcc/[^/]+/[^/]+/include(-fixed)?$')

probe = subprocess.run(
  sys.argv[1:] + ['-E', '-x', 'c++', '-v', os.devnull],
  capture_output=True,
  text=True,
)

inside = False
for line in probe.stderr.splitlines():
  if line.startswith('#include <...> search starts here:'):
    inside = True
  elif line.startswith('End of search list.'):
    break
  elif inside and os.path.isdir(line.strip()) and not gcc_own.search(line.strip()):
    print(line.strip())
'''

clang_tidy_implicit_includes = run_command(
  python3,
  '-c',
  clang_tidy_implicit_includes_py,
  meson.get_compiler('cpp').cmd_array(),
  check: true,
).stdout().strip().split('\n')

clang_tidy_extra_args = ['--extra-arg=-Wno-unused-command-line-argument']

foreach include_dir : clang_tidy_implicit_includes
  if include_dir != ''
    clang_tidy_extra_args += '--extra-arg=-isystem' + include_dir
  endif
endforeach

# Only the translation units are handed over: a header carries no compilation
# database entry of it's own, so clang-tidy would analyze it with the guessed
# flags of an unrelated file and report it's project includes as not found. The
# headers still get checked as a part of the sources including them.
clang_tidy_sources = []

foreach source_file : all_CPP_sources
  if source_file.endswith('.cpp')
    clang_tidy_sources += source_file
  endif
endforeach

clang_tidy_cmd = [
  clang_tidy_exec,
  '--config-file=' + join_paths(meson.project_source_root(), 'misc', '.clang-tidy'),
  '-p', meson.project_build_root(),
] + clang_tidy_extra_args + clang_tidy_sources

clang_tidy_target = custom_target(
  'clang-tidy',
  command: clang_tidy_cmd,
  build_always_stale: true,
  output: 'clang-tidy-output-stub.txt',
  console: true
)
