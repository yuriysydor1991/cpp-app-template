appimagetool_exec = find_program('appimagetool', required: true)

appimage_arch = run_command('uname', '-m', check: true).stdout().strip()
appimage_name = meson.project_name() + '-' + meson.project_version() + '-' + appimage_arch + '-' + package_os
appimage_appdir = join_paths(meson.project_build_root(), appimage_name + '.AppDir')
appimage_output = appimage_name + '.AppImage'
appimage_icon_name = meson.project_name().to_lower() + '.svg'

apprun_build_path = join_paths(meson.current_build_dir(), 'AppRun')
desktop_build_path = join_paths(meson.current_build_dir(), meson.project_name() + '.desktop')
icon_build_path = join_paths(meson.current_build_dir(), appimage_icon_name)

configure_file(
  output: 'AppRun',
  configuration: {
    'PROJECT_BINARY_NAME': meson.project_name(),
    'PROJECT_BINARY_INSTALLATION_DIR': 'bin',
    'PROJECT_LIBRARY_INSTALLATION_DIR': get_option('libdir'),
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

configure_file(
  output: appimage_icon_name,
  configuration: {
    'DESKTOP_ICON_LETTER': meson.project_name().substring(0, 1),
  },
  input: join_paths(meson.project_source_root(), 'misc', 'template-project.icon.svg.meson.in')
)

# The AppDir root carries the AppRun entry point, the desktop entry and the
# icon it names, the install prefix tree (usr/local/bin by default, usr/bin
# with the --prefix=/usr) lands under it. The appimagetool packs the AppDir
# into the AppImage runtime.
appimage_cmd = [
  'sh', '-c',
  'set -e && ' +
  'rm -rf ' + appimage_appdir + ' && ' +
  'mkdir -p ' + appimage_appdir + ' && ' +
  'DESTDIR=' + appimage_appdir + ' meson install -C ' + meson.project_build_root() + ' && ' +
  'install -m 0755 ' + apprun_build_path + ' ' + appimage_appdir + '/AppRun && ' +
  'install -m 0644 ' + desktop_build_path + ' ' + appimage_appdir + '/' + meson.project_name() + '.desktop && ' +
  'install -m 0644 ' + icon_build_path + ' ' + appimage_appdir + '/' + appimage_icon_name + ' && ' +
  'cd ' + meson.project_build_root() + ' && ' +
  'ARCH=' + appimage_arch + ' ' + appimagetool_exec.full_path() + ' ' + appimage_appdir + ' ' + appimage_output
]

appimage_target = custom_target(
  'AppImage',
  command: appimage_cmd,
  build_always_stale: true,
  output: appimage_output,
  console: true
)
