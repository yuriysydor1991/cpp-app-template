project_description = 'The C++ Template project with Meson for you!'

project_include_root = meson.global_source_root()
configuration_inc = include_directories(join_paths('..', '..'))

if host_machine.system() == 'windows'
  timestamp = run_command('powershell', '-Command', 'Get-Date -Format "yyyy-MM-dd HH:mm:ss"', check: true).stdout().strip()
else
  timestamp = run_command('date', '+%Y-%m-%d %H:%M:%S', check: true).stdout().strip()
endif

# The destination OS of the package file names, so the packages of the
# different OS releases differ in name: the ID and the VERSION_ID of the
# os-release the Linux distributions and the FreeBSD ship (e.g. ubuntu-24.04,
# freebsd-15.1), the NT version on the Windows (the windows-10.0 the Windows 10
# and 11 share). A cross build names the system of its host machine alone,
# since the build machine runs another one.
package_os = get_option('PACKAGE_OS')

if package_os == '' and meson.is_cross_build()
  package_os = host_machine.system()
elif package_os == '' and host_machine.system() == 'windows'
  package_os = 'windows-' + run_command(
    'powershell', '-Command', '$v = [Environment]::OSVersion.Version; "$($v.Major).$($v.Minor)"',
    check: true
  ).stdout().strip()
elif package_os == ''
  package_os = run_command(
    'sh', '-c',
    'if [ -r /etc/os-release ]; then . /etc/os-release; ' +
    'else ID=$(uname -s | tr A-Z a-z); VERSION_ID=$(uname -r | sed "s/[^0-9.].*//"); fi; ' +
    'echo "$ID${VERSION_ID:+-$VERSION_ID}"',
    check: true
  ).stdout().strip()
endif

# A source tree without the git history (a release tarball, a copied source
# directory) still configures, it just carries an empty commit hash.
git_hash = run_command(
  'git', '-C', meson.project_source_root(), 'rev-parse', 'HEAD',
  check: false
).stdout().strip()
