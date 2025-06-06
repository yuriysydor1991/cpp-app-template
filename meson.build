project(
  'CppAppTemplate',
  'cpp',
  license: 'Free to use',
  version: '0.10.0',
  meson_version: '>= 0.61.2',
  default_options: [
    'cpp_std=c++17',
    'warning_level=3',
  ],
)

subdir('meson')
subdir('src')

if get_option('ENABLE_DOC_DOXYGEN')
  subdir('doc')
endif
