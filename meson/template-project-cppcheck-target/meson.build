find_program('cppcheck', required: true)

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
  ] + all_CPP_sources

cppcheck_target = custom_target(
  'cppcheck',
  command: cppcheck_cmd,
  build_always_stale: false,
  output: 'cppcheck-output-stub.txt'
)
