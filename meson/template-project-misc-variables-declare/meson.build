project_description = 'The C++ Template project with Meson for you!'

project_include_root = meson.global_source_root()
configuration_inc = include_directories(join_paths('..', '..'))

project_major_version = meson.project_version().split('.')[0]

PROJECT_LIBRARY_NAME = meson.project_name() + '-' + project_major_version

if host_machine.system() == 'windows'
  timestamp = run_command('powershell', '-Command', 'Get-Date -Format "yyyy-MM-dd HH:mm:ss"').stdout().strip()
else
  timestamp = run_command('date', '+%Y-%m-%d %H:%M:%S').stdout().strip()
endif

git_hash = run_command('git', 'rev-parse', 'HEAD').stdout().strip()
