find_program('rpmbuild', required: true)

rpm_arch = run_command('uname', '-m', check: true).stdout().strip()
rpm_topdir = join_paths(meson.project_build_root(), 'rpm-build')
rpm_stage_dir = join_paths(rpm_topdir, 'STAGE')
rpm_file_list = join_paths(rpm_topdir, 'files.list')
# the one package the rpmbuild names after its release and dist tag (e.g. the
# 1.fc44) lands under the name scheme of the other packagers
rpm_output = meson.project_name() + '-' + meson.project_version() + '-' + rpm_arch + '-' + package_os + '.rpm'

rpm_spec_path = join_paths(meson.current_build_dir(), meson.project_name() + '.spec')

configure_file(
  output: meson.project_name() + '.spec',
  configuration: {
    'PROJECT_NAME': meson.project_name(),
    'PROJECT_VERSION': meson.project_version(),
    'PROJECT_DESCRIPTION': project_description,
    'PROJECT_MAINTAINER': get_option('PROJECT_MAINTAINER'),
    'PROJECT_MAINTAINER_EMAIL': get_option('PROJECT_MAINTAINER_EMAIL'),
    'RPM_STAGE_DIR': rpm_stage_dir,
    'RPM_FILE_LIST': rpm_file_list,
  },
  input: join_paths(meson.project_source_root(), 'misc', 'rpm.spec.in')
)

# The spec copies the staged tree into its buildroot and packs the files the
# list below names, so any configured prefix works. The directories carrying
# the project name (the headers, the CMake package and the docs ones) belong
# to the package as well, the shared system ones do not.
rpm_cmd = [
  'sh', '-c',
  'set -e && ' +
  'rm -rf ' + rpm_topdir + ' && ' +
  'mkdir -p ' + rpm_stage_dir + ' ' + rpm_topdir + '/BUILD ' + rpm_topdir + '/RPMS ' +
    rpm_topdir + '/SOURCES ' + rpm_topdir + '/SPECS ' + rpm_topdir + '/SRPMS && ' +
  'DESTDIR=' + rpm_stage_dir + ' meson install -C ' + meson.project_build_root() + ' && ' +
  '(cd ' + rpm_stage_dir + ' && (find . -type f -o -type l) | cut -c2- && ' +
    'find . -type d -path "*' + meson.project_name() + '*" | cut -c2- | sed "s/^/%dir /") > ' +
    rpm_file_list + ' && ' +
  'rpmbuild --define "_topdir ' + rpm_topdir + '" -bb ' + rpm_spec_path + ' && ' +
  'cp ' + rpm_topdir + '/RPMS/' + rpm_arch + '/*.rpm ' + join_paths(meson.project_build_root(), rpm_output)
]

rpm_target = custom_target(
  'rpm',
  command: rpm_cmd,
  build_always_stale: true,
  output: rpm_output,
  console: true
)
