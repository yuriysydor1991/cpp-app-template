if get_option('ENABLE_SANITIZERS') and get_option('ENABLE_SANITIZERS_THREADS')
  error(
    'ENABLE_SANITIZERS and ENABLE_SANITIZERS_THREADS are mutually exclusive ' +
    'because ThreadSanitizer is incompatible with the Address+Leak sanitizers.'
  )
endif

if get_option('ENABLE_SANITIZERS')
  template_project_extra_cpp_args += [
    '-fsanitize=address,leak,undefined',
    '-fno-omit-frame-pointer',
    '-g'
  ]
  template_project_extra_link_args += [
    '-fsanitize=address,leak,undefined'
  ]
  message('Sanitizers enabled: address+leak+undefined')
endif

if get_option('ENABLE_SANITIZERS_THREADS')
  template_project_extra_cpp_args += [
    '-fsanitize=thread',
    '-fno-omit-frame-pointer',
    '-g'
  ]
  template_project_extra_link_args += [
    '-fsanitize=thread'
  ]
  message('Sanitizers enabled: thread')
endif
