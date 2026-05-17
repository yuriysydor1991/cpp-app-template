appimage_arch = run_command('uname', '-m', check: true).stdout().strip()
appimage_name = meson.project_name() + '-' + meson.project_version() + '-' + appimage_arch
appimage_appdir = join_paths(meson.project_build_root(), appimage_name + '.AppDir')
appimage_output = appimage_name + '.AppImage'

apprun_build_path = join_paths(meson.current_build_dir(), 'AppRun')
desktop_build_path = join_paths(meson.current_build_dir(), meson.project_name() + '.desktop')

configure_file(
  output: 'AppRun',
  configuration: {
    'PROJECT_BINARY_NAME': meson.project_name(),
    'PROJECT_BINARY_INSTALLATION_DIR': 'bin',
  },
  input: join_paths(meson.project_source_root(), 'misc', 'AppRun.meson.in')
)

configure_file(
  output: meson.project_name() + '.desktop',
  configuration: {
    'PROJECT_NAME': meson.project_name(),
    'PROJECT_BINARY_NAME': meson.project_name(),
    'PROJECT_BINARY_NAME_lower': meson.project_name().to_lower(),
    'PROJECT_DESCRIPTION': project_description,
  },
  input: join_paths(meson.project_source_root(), 'misc', 'template-project.desktop.meson.in')
)

appimage_cmd = [
  'sh', '-c',
  'set -e && ' +
  'rm -rf ' + appimage_appdir + ' && ' +
  'mkdir -p ' + appimage_appdir + '/usr && ' +
  'DESTDIR=' + appimage_appdir + '/usr meson install -C ' + meson.project_build_root() + ' && ' +
  'install -m 0755 ' + apprun_build_path + ' ' + appimage_appdir + '/AppRun && ' +
  'install -m 0644 ' + desktop_build_path + ' ' + appimage_appdir + '/' + meson.project_name() + '.desktop && ' +
  'cd ' + meson.project_build_root() + ' && ' +
  'tar czf ' + appimage_output + ' ' + appimage_name + '.AppDir'
]

appimage_target = custom_target(
  'AppImage',
  command: appimage_cmd,
  build_always_stale: true,
  output: appimage_output,
  console: true
)
