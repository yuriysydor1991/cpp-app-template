find_program('rpmbuild', required: true)

rpm_arch = run_command('uname', '-m', check: true).stdout().strip()
rpm_topdir = join_paths(meson.project_build_root(), 'rpm-build')
rpm_buildroot = join_paths(rpm_topdir, 'BUILDROOT', meson.project_name() + '-' + meson.project_version())
rpm_output = meson.project_name() + '-' + meson.project_version() + '-1.' + rpm_arch + '.rpm'

rpm_spec_path = join_paths(meson.current_build_dir(), meson.project_name() + '.spec')

configure_file(
  output: meson.project_name() + '.spec',
  configuration: {
    'PROJECT_NAME': meson.project_name(),
    'PROJECT_VERSION': meson.project_version(),
    'PROJECT_DESCRIPTION': project_description,
    'PROJECT_MAINTAINER': get_option('PROJECT_MAINTAINER'),
    'PROJECT_MAINTAINER_EMAIL': get_option('PROJECT_MAINTAINER_EMAIL'),
  },
  input: join_paths(meson.project_source_root(), 'misc', 'rpm.spec.in')
)

rpm_cmd = [
  'sh', '-c',
  'set -e && ' +
  'rm -rf ' + rpm_topdir + ' && ' +
  'mkdir -p ' + rpm_topdir + '/{BUILD,BUILDROOT,RPMS,SOURCES,SPECS,SRPMS} && ' +
  'mkdir -p ' + rpm_buildroot + ' && ' +
  'DESTDIR=' + rpm_buildroot + ' meson install -C ' + meson.project_build_root() + ' && ' +
  'rpmbuild --define "_topdir ' + rpm_topdir + '"' +
    ' --define "_buildrootdir ' + rpm_topdir + '/BUILDROOT"' +
    ' --buildroot ' + rpm_buildroot +
    ' -bb ' + rpm_spec_path + ' && ' +
  'cp ' + rpm_topdir + '/RPMS/' + rpm_arch + '/*.rpm ' + meson.project_build_root() + '/'
]

rpm_target = custom_target(
  'rpm',
  command: rpm_cmd,
  build_always_stale: true,
  output: rpm_output,
  console: true
)
