project_description = 'The C++ Template project with Meson for you!'

project_include_root = meson.global_source_root()
configuration_inc = include_directories(join_paths('..', '..'))

if host_machine.system() == 'windows'
  timestamp = run_command('powershell', '-Command', 'Get-Date -Format "yyyy-MM-dd HH:mm:ss"', check: true).stdout().strip()
else
  timestamp = run_command('date', '+%Y-%m-%d %H:%M:%S', check: true).stdout().strip()
endif

# A source tree without the git history (a release tarball, a copied source
# directory) still configures, it just carries an empty commit hash.
git_hash = run_command(
  'git', '-C', meson.project_source_root(), 'rev-parse', 'HEAD',
  check: false
).stdout().strip()
