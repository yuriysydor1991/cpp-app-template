if get_option('ENABLE_LOGS_MICROSECONDS_TIME')
  add_project_arguments('-DENABLE_LOGS_MICROSECONDS_TIME=1', language: 'cpp')
endif

add_project_arguments(
  '-DMAX_LOG_LEVEL=' + get_option('MAX_LOG_LEVEL').to_string(),
  language: 'cpp',
)

DEFAULT_LOG_FILE_PATH = get_option('DEFAULT_LOG_FILE_PATH')

add_project_arguments(
  '-DDEFAULT_LOG_FILE_PATH="' + DEFAULT_LOG_FILE_PATH + '"',
  language: 'cpp',
)

subdir('simple-logger')
