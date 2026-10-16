if get_option('ENABLE_SANITIZERS') and get_option('ENABLE_SANITIZERS_THREADS')
  error(
    'ENABLE_SANITIZERS and ENABLE_SANITIZERS_THREADS are mutually exclusive ' +
    'because ThreadSanitizer is incompatible with the Address+Leak sanitizers.'
  )
endif

if get_option('ENABLE_SANITIZERS')
  sanitizers_flags = ['-fsanitize=address,leak,undefined']
  message('Sanitizers enabled: address+leak+undefined')
else
  sanitizers_flags = ['-fsanitize=thread']
  message('Sanitizers enabled: thread')
endif

# The project wide arguments reach every target, the tests and the internal
# libraries among them, so the sanitized build checks the very code it runs.
add_project_arguments(
  sanitizers_flags + ['-fno-omit-frame-pointer', '-g'],
  language: 'cpp'
)

add_project_link_arguments(sanitizers_flags, language: 'cpp')
