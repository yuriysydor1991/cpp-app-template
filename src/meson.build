configuration_inc = [
  configuration_inc,
  include_directories('.')
]

if get_option('ENABLE_UNIT_TESTS') or get_option('ENABLE_COMPONENT_TESTS')
  gtest_dep = dependency('gtest', required: true)
  gmock_dep = dependency('gmock', required: true)
  gtest_main_dep = dependency('gtest_main', required: true)

  gtest_deps = [gtest_dep, gmock_dep, gtest_main_dep]
endif

if get_option('ENABLE_UNIT_TESTS')
  subdir('tests/mocks')
endif

subdir('log')
subdir('lib')
