UTEST_LibMain_sources = files(
  'UTEST_LibMain.cpp',
  join_paths(project_include_root, 'src', 'lib', 'libmain', 'LibMain.cpp'),
)

UTEST_LibMain = executable(
  'UTEST_LibMain',
  UTEST_LibMain_sources,
  dependencies: gtest_deps,
  include_directories: [
    MOCK_LibraryContext,
    MOCK_log,
    configuration_inc,
    lib_public_includes,
  ],
  cpp_args: ['-DNDEBUG=1'],
)

test(
  'gtest',
  UTEST_LibMain,
  suite: 'UTEST_LibMain',
)
