doc_conf_data = configuration_data()

doc_conf_data.set('PROJECT_VERSION', meson.project_version())
doc_conf_data.set('PROJECT_NAME', meson.project_name())
doc_conf_data.set('PROJECT_BINARY_NAME', meson.project_name())
doc_conf_data.set('PROJECT_GIT_COMMIT', git_hash)
doc_conf_data.set('PROJECT_CONFIGURE_DATE', timestamp)
doc_conf_data.set('DOXYGEN_MAIN_PAGE_MD', join_paths(meson.project_source_root(), 'README.md'))
doc_conf_data.set('DOXYGEN_OUT_HTML_NAME', meson.project_name() + '-html')
doc_conf_data.set('MESON_PROJECT_DESCRIPTION', project_description)
# Meson runs the doxygen from the build root, so every input is an absolute
# path and the HTML lands next to this file in the build tree.
doc_conf_data.set('DOXYGEN_OUTPUT_DIR', meson.current_build_dir())
doc_conf_data.set('DOXYGEN_STRIP_FROM_PATH', meson.project_source_root())
doc_conf_data.set('DOXYGEN_CONFIG_HEADER', join_paths(template_project_config_include, 'project-global-decls.h'))
doc_conf_data.set('DOXYGEN_SOURCES_DIR', join_paths(meson.project_source_root(), 'src'))
doc_conf_data.set('DOXYGEN_OUTPUT_LANGUAGE', 'English')

configure_file(
  input: 'Doxyfile.meson.in',
  output: 'Doxyfile',
  configuration: doc_conf_data
)

find_program('doxygen', required: true)

doxygen_target = custom_target(
  'Doxygen-doc',
  output: [doc_conf_data.get('DOXYGEN_OUT_HTML_NAME')],
  command: [
    'doxygen', 
    join_paths(meson.current_build_dir(), 'Doxyfile')
  ],
  build_by_default: true,
  install: get_option('DOXYGEN_DO_INSTALL'),
  install_dir: join_paths(get_option('datadir'), 'doc'),
  install_tag: 'doc'
)
