UTEST_LibFactory_sources = files(
  'UTEST_LibFactory.cpp',
  join_paths(project_include_root, 'src', 'lib', 'libmain', 'LibFactory.cpp'),
)

UTEST_LibFactory = executable(
  'UTEST_LibFactory',
  UTEST_LibFactory_sources,
  dependencies: gtest_deps,
  include_directories: [
    MOCK_LibraryContext,
    MOCK_LibMain,
    configuration_inc,
    lib_public_includes,
  ],
  cpp_args: ['-DNDEBUG=1'],
)

test(
  'gtest',
  UTEST_LibFactory,
  suite: 'UTEST_LibFactory',
)
