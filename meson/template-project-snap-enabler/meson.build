snapcraft_exec = find_program('snapcraft', required: true)

snap_grade = 'devel'
snap_confinement = 'strict'
# The part installs into this prefix of the snap, the app command points into
# the very same place.
snap_install_prefix = '/usr'

snapcraft_yaml_path = join_paths(meson.current_build_dir(), 'snapcraft.yaml')

configure_file(
  output: 'snapcraft.yaml',
  configuration: {
    'PROJECT_NAME': meson.project_name(),
    'PROJECT_BINARY_NAME_lower': meson.project_name().to_lower(),
    'PROJECT_VERSION': meson.project_version(),
    'PROJECT_DESCRIPTION': project_description,
    'PROJECT_BINARY_INSTALLATION_DIR': join_paths(snap_install_prefix, 'bin').substring(1),
    'SNAP_INSTALL_PREFIX': snap_install_prefix,
    'PROJECT_SOURCE_DIR': meson.project_source_root(),
    'TEMPLATE_PROJECT_SNAP_GRADE': snap_grade,
    'TEMPLATE_PROJECT_SNAP_CONFINEMENT': snap_confinement,
  },
  input: join_paths(meson.project_source_root(), 'misc', 'snap', 'snapcraft.yaml.meson.in')
)

snap_dir = join_paths(meson.current_build_dir(), 'snap')

snap_cmd = [
  'sh', '-c',
  'set -e && ' +
  'mkdir -p ' + snap_dir + ' && ' +
  'cp ' + snapcraft_yaml_path + ' ' + snap_dir + '/snapcraft.yaml && ' +
  'cd ' + meson.current_build_dir() + ' && ' +
  snapcraft_exec.full_path() + ' pack'
]

snap_target = custom_target(
  'snap',
  command: snap_cmd,
  build_always_stale: true,
  output: 'snap-output-stub.txt',
  console: true
)
