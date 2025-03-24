gtest_dep = dependency('gtest', required: true)
gmock_dep = dependency('gmock', required: true)
gtest_main_dep = dependency('gtest_main', required: true)

gtest_deps = [gtest_dep, gmock_dep, gtest_main_dep]

app_mocks_root_str = join_paths(meson.current_source_dir(), 'mocks')

subdir('mocks')
subdir('unit')
