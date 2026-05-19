UTEST_ApplicationContext2LibraryContext_sources = files(
  'UTEST_ApplicationContext2LibraryContext.cpp',
  join_paths(project_include_root, 'src', 'converters', 'ApplicationContext2LibraryContext.cpp'),
  join_paths(app_mocks_root_str, 'ApplicationContext', 'src', 'app', 'ApplicationContext.cpp'),
)

UTEST_ApplicationContext2LibraryContext = executable(
  'UTEST_ApplicationContext2LibraryContext',
  UTEST_ApplicationContext2LibraryContext_sources,
  dependencies: gtest_deps,
  include_directories: [
    MOCK_ApplicationContext,
    MOCK_LibraryContext,
    configuration_inc,
    lib_public_includes,
  ],
  cpp_args: ['-DNDEBUG=1'],
)

test(
  'gtest',
  UTEST_ApplicationContext2LibraryContext,
  suite: 'UTEST_ApplicationContext2LibraryContext',
)
