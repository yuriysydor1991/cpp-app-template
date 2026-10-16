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

# A dependency object instead of the project arguments, which Meson would
# advise against in favour of the b_sanitize built-in option. Every target
# takes it through the template_project_extra_deps, the tests through the
# template_project_sanitizers_deps, so the sanitized build checks the very code
# it runs.
template_project_sanitizers_deps += declare_dependency(
  compile_args: sanitizers_flags + ['-fno-omit-frame-pointer', '-g'],
  link_args: sanitizers_flags,
)

template_project_extra_deps += template_project_sanitizers_deps
