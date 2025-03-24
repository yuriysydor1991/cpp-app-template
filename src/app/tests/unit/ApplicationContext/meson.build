UTEST_ApplicationContext_files = files(
  'UTEST_ApplicationContext.cpp',
  join_paths(project_include_root, 'src', 'app', 'ApplicationContext.cpp')
)

UTEST_ApplicationContext = executable(
  'UTEST_ApplicationContext', 
  UTEST_ApplicationContext_files, 
  dependencies: gtest_deps,
  include_directories: [
    configuration_inc
  ],
  cpp_args: ['-DNDEBUG=1']
)

test(
  'gtest', 
  UTEST_ApplicationContext,
  suite: 'UTEST_ApplicationContext'
)
