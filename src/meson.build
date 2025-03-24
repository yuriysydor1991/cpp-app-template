configuration_inc = [
  configuration_inc,
  include_directories('.')
]

subdir('app')

conf_data = configuration_data()

conf_data.set('PROJECT_VERSION', meson.project_version())
conf_data.set('PROJECT_NAME', meson.project_name())
conf_data.set('PROJECT_GIT_COMMIT', git_hash)
conf_data.set('PROJECT_CONFIGURE_DATE', timestamp)

configure_file(
  input : 'project-global-decls.h.meson.in',
  output : 'project-global-decls.h',
  configuration : conf_data
)

executable(
  meson.project_name(), 
  [
    'main.cpp'
  ],
  include_directories: configuration_inc,
  link_whole: applib
)
