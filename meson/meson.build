find_program('git', required: true)

subdir('template-project-all-source-files')
subdir('template-project-misc-variables-declare')
subdir('template-project-configure-file')

if get_option('ENABLE_CPPCHECK')
  subdir('template-project-cppcheck-target')
endif

if get_option('ENABLE_CLANGFORMAT')
  subdir('template-project-clang-format-target')
endif

if get_option('ENABLE_FLATPAK')
  subdir('template-project-flatpak-target')
endif

if get_option('ENABLE_DOCKER')
  subdir('template-project-dockerers')
endif