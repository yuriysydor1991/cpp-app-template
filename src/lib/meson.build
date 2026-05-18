lib_facade_sources = files(
  'facade/LibraryFacade.cpp',
)

lib_libmain_sources = files(
  'libmain/LibFactory.cpp',
  'libmain/LibMain.cpp',
)

lib_public_includes = include_directories('facade/public')

template_project_main_library = library(
  PROJECT_LIBRARY_NAME,
  lib_facade_sources + lib_libmain_sources,
  include_directories: [configuration_inc, lib_public_includes],
  link_whole: [loglib],
  dependencies: template_project_extra_deps,
  cpp_args: template_project_extra_cpp_args,
  link_args: template_project_extra_link_args,
  version: meson.project_version(),
  soversion: project_major_version,
  install: true,
)

install_subdir(
  'facade/public',
  install_dir: join_paths(get_option('includedir'), PROJECT_LIBRARY_NAME),
  strip_directory: true,
)

pkgconfig = import('pkgconfig')
pkgconfig.generate(
  template_project_main_library,
  name: PROJECT_LIBRARY_NAME,
  filebase: PROJECT_LIBRARY_NAME,
  description: project_description,
  subdirs: PROJECT_LIBRARY_NAME,
  url: 'http://www.kytok.org.ua/',
)

cmake_config_install_subdir = join_paths(
  get_option('libdir'), 'cmake', PROJECT_LIBRARY_NAME
)

relative_back_from_cmake_dir = ''
foreach _ : cmake_config_install_subdir.split('/')
  relative_back_from_cmake_dir += '../'
endforeach
relative_back_from_cmake_dir = relative_back_from_cmake_dir.substring(0, -1)

cmake_conf = configuration_data()
cmake_conf.set('PROJECT_LIBRARY_NAME', PROJECT_LIBRARY_NAME)
cmake_conf.set('PROJECT_VERSION', meson.project_version())
cmake_conf.set('PROJECT_VERSION_MAJOR', project_major_version)
cmake_conf.set('CMAKE_CONFIG_INSTALL_DIR', cmake_config_install_subdir)
cmake_conf.set('LIB_INSTALL_SUBDIR', get_option('libdir'))
cmake_conf.set('INCLUDE_INSTALL_SUBDIR',
  join_paths(get_option('includedir'), PROJECT_LIBRARY_NAME))
cmake_conf.set('RELATIVE_BACK_FROM_CMAKE_DIR', relative_back_from_cmake_dir)

configure_file(
  input: join_paths(meson.current_source_dir(), 'cmake', 'TemplateLibraryConfig.cmake.in'),
  output: PROJECT_LIBRARY_NAME + 'Config.cmake',
  configuration: cmake_conf,
  install: true,
  install_dir: cmake_config_install_subdir,
)

configure_file(
  input: join_paths(meson.current_source_dir(), 'cmake', 'TemplateLibraryConfigVersion.cmake.in'),
  output: PROJECT_LIBRARY_NAME + 'ConfigVersion.cmake',
  configuration: cmake_conf,
  install: true,
  install_dir: cmake_config_install_subdir,
)

configure_file(
  input: join_paths(meson.current_source_dir(), 'cmake', 'TemplateLibraryTargets.cmake.in'),
  output: PROJECT_LIBRARY_NAME + 'Targets.cmake',
  configuration: cmake_conf,
  install: true,
  install_dir: cmake_config_install_subdir,
)

subdir('facade')
subdir('libmain')
