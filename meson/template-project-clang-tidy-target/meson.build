clang_tidy_exec = find_program('clang-tidy', required: true)

clang_tidy_cmd = [
  clang_tidy_exec,
  '--config-file=' + join_paths(meson.project_source_root(), 'misc', '.clang-tidy'),
  '-p', meson.project_build_root(),
  '--extra-arg=-Wno-unused-command-line-argument',
] + all_CPP_sources

clang_tidy_target = custom_target(
  'clang-tidy',
  command: clang_tidy_cmd,
  build_always_stale: true,
  output: 'clang-tidy-output-stub.txt',
  console: true
)
