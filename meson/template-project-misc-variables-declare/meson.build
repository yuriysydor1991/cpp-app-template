project_description = 'The C++ Template project with Meson for you!'

project_include_root = meson.global_source_root()
configuration_inc = include_directories(join_paths('..', '..'))

_project_version_components = meson.project_version().split('.')
project_major_version = _project_version_components[0]
project_minor_version = _project_version_components.length() > 1 ? _project_version_components[1] : '0'
project_micro_version = _project_version_components.length() > 2 ? _project_version_components[2] : '0'

_lib_include_minor = get_option('LIB_INCLUDE_MINOR_IN_NAME')
_lib_include_micro = get_option('LIB_INCLUDE_MICRO_IN_NAME')
_lib_name_suffix = get_option('LIB_NAME_SUFFIX')

if _lib_include_micro and not _lib_include_minor
  warning('LIB_INCLUDE_MICRO_IN_NAME=true requires LIB_INCLUDE_MINOR_IN_NAME=true - enabling minor implicitly.')
  _lib_include_minor = true
endif

PROJECT_LIBRARY_NAME = meson.project_name() + '-' + project_major_version
if _lib_include_minor
  PROJECT_LIBRARY_NAME += '.' + project_minor_version
endif
if _lib_include_micro
  PROJECT_LIBRARY_NAME += '.' + project_micro_version
endif
if _lib_name_suffix != ''
  PROJECT_LIBRARY_NAME += _lib_name_suffix
endif

message('PROJECT_LIBRARY_NAME: ' + PROJECT_LIBRARY_NAME)

if host_machine.system() == 'windows'
  timestamp = run_command('powershell', '-Command', 'Get-Date -Format "yyyy-MM-dd HH:mm:ss"').stdout().strip()
else
  timestamp = run_command('date', '+%Y-%m-%d %H:%M:%S').stdout().strip()
endif

git_hash = run_command('git', 'rev-parse', 'HEAD').stdout().strip()
