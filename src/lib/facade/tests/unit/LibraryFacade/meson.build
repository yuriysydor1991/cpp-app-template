UTEST_LibraryFacade_sources = files(
  'UTEST_LibraryFacade.cpp',
  join_paths(project_include_root, 'src', 'lib', 'facade', 'LibraryFacade.cpp'),
)

UTEST_LibraryFacade = executable(
  'UTEST_LibraryFacade',
  UTEST_LibraryFacade_sources,
  dependencies: gtest_deps,
  include_directories: [
    MOCK_LibraryContext,
    MOCK_LibMain,
    FACADE_MOCK_LibFactory,
    configuration_inc,
    lib_public_includes,
  ],
  cpp_args: ['-DNDEBUG=1'],
)

test(
  'gtest',
  UTEST_LibraryFacade,
  suite: 'UTEST_LibraryFacade',
)
