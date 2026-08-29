lib_facade_sources = files(
  'facade/LibraryFacade.cpp',
)

lib_libmain_sources = files(
  'libmain/LibFactory.cpp',
  'libmain/LibMain.cpp',
)

lib_public_includes = include_directories('facade/public')

# Only the TEMPLATE_LIB_API marked interface of facade/public leaves the shared
# object. That is a correctness requirement and not a size optimisation: every
# library derived from this template carries the very same lib0impl and
# project_decls names, and an application which loads two of them would
# otherwise let the dynamic linker bind the calls of one library into the
# definitions of the other.
#
# The logging subsystem linked in whole below is the one exception on this
# branch: it is compiled by its own static_library() call and keeps the default
# visibility, because the application of this very project resolves its own
# logging through this shared object and carries no copy of that subsystem. The
# two of them therefore share a single logger instance, which is what makes the
# application log file hold the library messages as well.
#
# TEMPLATE_LIB_BUILDING turns that macro into the export half of the __declspec
# pair while the library itself is being compiled. Nothing outside of this
# build ever defines it, so a consumer of the installed headers gets the import
# half.
template_project_main_library = library(
  PROJECT_LIBRARY_NAME,
  lib_facade_sources + lib_libmain_sources,
  include_directories: [configuration_inc, lib_public_includes],
  link_whole: [loglib],
  dependencies: template_project_extra_deps,
  cpp_args: template_project_extra_cpp_args + ['-DTEMPLATE_LIB_BUILDING=1'],
  link_args: template_project_extra_link_args,
  gnu_symbol_visibility: 'hidden',
  version: meson.project_version(),
  soversion: project_major_version,
  install: true,
)

# Everything below installs development files - the public headers, the
# pkg-config file and the CMake package integration files. The library binary
# itself is installed by the library() call above and stays unaffected, so
# turning the option off leaves a runtime only installation behind.
if get_option('LIB_INSTALL_DEV_FILES')

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
  # Both the versioned sub-directory and the plain include root, so a consumer
  # may write either <CppAppTemplate-0.11/LibraryFacade.h> (recommended) or the
  # short <LibraryFacade.h>. The prefixed form is the safe one: every library
  # derived from this template installs a LibraryFacade.h of its own.
  subdirs: [PROJECT_LIBRARY_NAME, '.'],
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
cmake_conf.set('INCLUDE_ROOT_SUBDIR', get_option('includedir'))
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

endif

subdir('facade')
subdir('libmain')

if get_option('ENABLE_COMPONENT_TESTS')
  subdir('tests')
endif
