pkg_exec = find_program('pkg', required: true)

freebsd_arch = run_command('uname', '-m', check: true).stdout().strip()
freebsd_pkg_stage = join_paths(meson.project_build_root(), 'freebsd-pkg-staging')
freebsd_pkg_output = meson.project_name() + '-' + meson.project_version() + '.pkg'

freebsd_manifest_path = join_paths(meson.current_build_dir(), '+MANIFEST')

configure_file(
  output: '+MANIFEST',
  configuration: {
    'PROJECT_NAME': meson.project_name(),
    'PROJECT_VERSION': meson.project_version(),
    'PROJECT_DESCRIPTION': project_description,
    'PROJECT_MAINTAINER': get_option('PROJECT_MAINTAINER'),
    'PROJECT_MAINTAINER_EMAIL': get_option('PROJECT_MAINTAINER_EMAIL'),
    'FREEBSD_ARCH': freebsd_arch,
  },
  input: join_paths(meson.project_source_root(), 'misc', 'freebsd-pkg.manifest.in')
)

freebsd_pkg_cmd = [
  'sh', '-c',
  'set -e && ' +
  'rm -rf ' + freebsd_pkg_stage + ' && ' +
  'mkdir -p ' + freebsd_pkg_stage + ' && ' +
  'DESTDIR=' + freebsd_pkg_stage + ' meson install -C ' + meson.project_build_root() + ' && ' +
  pkg_exec.full_path() + ' create -M ' + freebsd_manifest_path +
    ' -r ' + freebsd_pkg_stage +
    ' -o ' + meson.project_build_root()
]

freebsd_pkg_target = custom_target(
  'freebsd-pkg',
  command: freebsd_pkg_cmd,
  build_always_stale: true,
  output: freebsd_pkg_output,
  console: true
)
