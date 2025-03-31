find_program('clang-format', required: true)

clangformat_cmd = [
  'clang-format', 
  '--style=file:' + join_paths(meson.project_source_root(), 'misc', '.clang-format'),
  '--Werror', 
  '--verbose',
  '-i'] + all_CPP_sources

clangformat_target = custom_target(
  'clang-format',
  command: clangformat_cmd,
  build_always_stale: true,
  output: 'clang-format-output-stub.txt'
)
