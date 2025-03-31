conf_data = configuration_data()

conf_data.set('PROJECT_VERSION', meson.project_version())
conf_data.set('PROJECT_NAME', meson.project_name())
conf_data.set('PROJECT_GIT_COMMIT', git_hash)
conf_data.set('PROJECT_CONFIGURE_DATE', timestamp)

configure_file(
  input : join_paths(project_include_root, 'src', 'project-global-decls.h.meson.in'),
  output : 'project-global-decls.h',
  configuration : conf_data
)

configuration_inc = [
  configuration_inc,
  include_directories('.')
]

template_project_config_include = meson.current_build_dir()
