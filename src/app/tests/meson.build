app_mocks_root_str = join_paths(meson.current_source_dir(), 'mocks')

subdir('mocks')

if get_option('ENABLE_UNIT_TESTS')
  subdir('unit')
endif

if get_option('ENABLE_COMPONENT_TESTS')
  subdir('component')
endif
