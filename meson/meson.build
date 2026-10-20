find_program('git', required: true)

template_project_extra_deps = []
template_project_extra_cpp_args = []
template_project_extra_link_args = []
# The sanitizers instrumentation every target, the tests among them, carries.
template_project_sanitizers_deps = []

subdir('compile-options/hardening/template-project-hardening')

subdir('tools/template-project-all-source-files')
subdir('template-project-misc-variables-declare')
subdir('template-project-configure-file')

if get_option('ENABLE_SANITIZERS') or get_option('ENABLE_SANITIZERS_THREADS')
  subdir('compile-options/sanitizers/template-project-sanitizers')
endif

if get_option('ENABLE_GPROF')
  subdir('enablers/profilers/template-project-profiler-gprof')
endif

if get_option('ENABLE_CPPCHECK')
  subdir('enablers/template-project-cppcheck-target')
endif

if get_option('ENABLE_CLANGFORMAT')
  subdir('enablers/template-project-clang-format-target')
endif

if get_option('ENABLE_CLANG_TIDY')
  subdir('enablers/template-project-clang-tidy-target')
endif

if get_option('ENABLE_LIBCURL')
  subdir('enablers/template-project-libcurl-enabler')
endif

if get_option('ENABLE_LIBXML2')
  subdir('enablers/template-project-libxml2-enabler')
endif

if get_option('ENABLE_NLOHMANN_JSON')
  subdir('enablers/template-project-nlohmann-json-enabler')
endif

if get_option('ENABLE_OPENCV')
  subdir('enablers/template-project-OpenCV-enabler')
endif

if get_option('ENABLE_FLATPAK')
  subdir('enablers/packagers/template-project-flatpak-target')
endif

if get_option('ENABLE_SNAP')
  subdir('enablers/packagers/template-project-snap-enabler')
endif

if get_option('ENABLE_DEB')
  subdir('enablers/packagers/template-project-deb-enabler')
endif

if get_option('ENABLE_RPM')
  subdir('enablers/packagers/template-project-rpm-enabler')
endif

if get_option('ENABLE_FREEBSD_PKG')
  subdir('enablers/packagers/template-project-freebsd-pkg-enabler')
endif

if get_option('ENABLE_APPIMAGE')
  subdir('enablers/packagers/template-project-AppImage-enabler')
endif

if get_option('ENABLE_WIX')
  subdir('enablers/packagers/template-project-wix-enabler')
endif

if get_option('ENABLE_DOCKER')
  subdir('enablers/dockerers/template-project-dockerers')
endif
