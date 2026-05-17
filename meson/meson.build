find_program('git', required: true)

template_project_extra_deps = []
template_project_extra_cpp_args = []
template_project_extra_link_args = []

subdir('template-project-all-source-files')
subdir('template-project-misc-variables-declare')
subdir('template-project-configure-file')

if get_option('ENABLE_SANITIZERS') or get_option('ENABLE_SANITIZERS_THREADS')
  subdir('template-project-sanitizers')
endif

if get_option('ENABLE_GPROF')
  subdir('template-project-profiler-gprof')
endif

if get_option('ENABLE_CPPCHECK')
  subdir('template-project-cppcheck-target')
endif

if get_option('ENABLE_CLANGFORMAT')
  subdir('template-project-clang-format-target')
endif

if get_option('ENABLE_CLANG_TIDY')
  subdir('template-project-clang-tidy-target')
endif

if get_option('ENABLE_LIBCURL')
  subdir('template-project-libcurl-enabler')
endif

if get_option('ENABLE_LIBXML2')
  subdir('template-project-libxml2-enabler')
endif

if get_option('ENABLE_NLOHMANN_JSON')
  subdir('template-project-nlohmann-json-enabler')
endif

if get_option('ENABLE_OPENCV')
  subdir('template-project-OpenCV-enabler')
endif

if get_option('ENABLE_FLATPAK')
  subdir('template-project-flatpak-target')
endif

if get_option('ENABLE_SNAP')
  subdir('template-project-snap-enabler')
endif

if get_option('ENABLE_DEB')
  subdir('template-project-deb-enabler')
endif

if get_option('ENABLE_RPM')
  subdir('template-project-rpm-enabler')
endif

if get_option('ENABLE_FREEBSD_PKG')
  subdir('template-project-freebsd-pkg-enabler')
endif

if get_option('ENABLE_APPIMAGE')
  subdir('template-project-AppImage-enabler')
endif

if get_option('ENABLE_WIX')
  subdir('template-project-wix-enabler')
endif

if get_option('ENABLE_DOCKER')
  subdir('template-project-dockerers')
endif
