configuration_inc = [
  configuration_inc,
  include_directories('.')
]

subdir('app')
subdir('log')

executable(
  meson.project_name(), 
  ['main.cpp'],
  include_directories: configuration_inc,
  link_whole: [applib, loglib],
  install: true,
  install_dir: 'bin'
)
