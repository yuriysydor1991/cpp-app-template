find_program('cppcheck', required: true)

# cppcheck resolves the quoted includes on its own, so it needs every directory
# the build system hands to the compiler as an include path. Without them the
# project headers stay unresolved, each one is reported as a missingInclude
# finding and the checker never sees the declarations behind them.
cppcheck_include_dirs_py = '''
import glob, os, sys

headers = glob.glob(sys.argv[1] + '/src/**/*.h', recursive=True)

for include_dir in sorted({os.path.dirname(header) for header in headers}):
  print(include_dir)
'''

cppcheck_header_dirs = run_command(
  python3,
  '-c',
  cppcheck_include_dirs_py,
  meson.project_source_root(),
  check: true,
).stdout().strip().split('\n')

cppcheck_include_args = []

foreach include_dir : cppcheck_header_dirs
  if include_dir != ''
    cppcheck_include_args += '-I' + include_dir
  endif
endforeach

cppcheck_cmd = [
  'cppcheck',
  '--language=c++',
  '--std=c++17',
  '--error-exitcode=1',
  '--inconclusive',
  '--enable=all',
  '--suppressions-list=' + join_paths(meson.project_source_root(), 'misc', '.cppcheck-suppress'),
  '-v',
  '-I' + project_include_root,
  '-I' + meson.global_build_root(),
  '-I' + template_project_config_include,
  ] + cppcheck_include_args + all_CPP_sources

cppcheck_target = custom_target(
  'cppcheck',
  command: cppcheck_cmd,
  build_always_stale: false,
  output: 'cppcheck-output-stub.txt'
)
