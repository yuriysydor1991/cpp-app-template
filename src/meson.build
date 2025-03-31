configuration_inc = [
  configuration_inc,
  include_directories('.')
]

subdir('app')

executable(
  meson.project_name(), 
  ['main.cpp'],
  include_directories: configuration_inc,
  link_whole: applib,
  install: true,
  install_dir: 'bin'
)
