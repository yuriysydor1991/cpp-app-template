find_program('dpkg-deb', required: true)

deb_arch = run_command('dpkg', '--print-architecture', check: true).stdout().strip()

deb_package_name = meson.project_name() + '-' + meson.project_version() + '_' + deb_arch
deb_stage_dir = join_paths(meson.project_build_root(), 'deb-staging', deb_package_name)
deb_output = deb_package_name + '.deb'

deb_control_path = join_paths(meson.current_build_dir(), 'deb-control')

configure_file(
  output: 'deb-control',
  configuration: {
    'PROJECT_NAME': meson.project_name(),
    'PROJECT_VERSION': meson.project_version(),
    'PROJECT_DESCRIPTION': project_description,
    'PROJECT_MAINTAINER': get_option('PROJECT_MAINTAINER'),
    'PROJECT_MAINTAINER_EMAIL': get_option('PROJECT_MAINTAINER_EMAIL'),
    'DEB_ARCH': deb_arch,
  },
  input: join_paths(meson.project_source_root(), 'misc', 'deb-control.in')
)

deb_cmd = [
  'sh', '-c',
  'set -e && ' +
  'rm -rf ' + deb_stage_dir + ' && ' +
  'mkdir -p ' + deb_stage_dir + '/DEBIAN && ' +
  'cp ' + deb_control_path + ' ' + deb_stage_dir + '/DEBIAN/control && ' +
  'DESTDIR=' + deb_stage_dir + ' meson install -C ' + meson.project_build_root() + ' && ' +
  'dpkg-deb --build ' + deb_stage_dir + ' ' + join_paths(meson.project_build_root(), deb_output)
]

deb_target = custom_target(
  'deb',
  command: deb_cmd,
  build_always_stale: true,
  output: deb_output,
  console: true
)
