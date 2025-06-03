find_program('flatpak', required: true)
find_program('flatpak-builder', required: true)

FLATPAK_PROJECT_URL = 'ua.org.kytok.template.' + meson.project_name()
FLATPAK_REPO = join_paths(meson.current_build_dir(), meson.project_name() + '-repo')
FLATPAK_BUILD = join_paths(meson.current_build_dir(), meson.project_name() + '-flatpak-build')
FLATPAK_DST_NAME = meson.project_name() + '-' + meson.project_version() + '.flatpak'
flatpakConfDst = 'flatpak.conf.json'
FLATPAK_CONF_SRC = join_paths('..', '..', 'misc', 'flatpak.conf.json.meson.in')

flatpak_conf_data = configuration_data()

flatpak_conf_data.set('PROJECT_NAME', meson.project_name())
flatpak_conf_data.set('PROJECT_SOURCE_DIR', meson.project_source_root())
flatpak_conf_data.set('FLATPAK_PROJECT_URL', FLATPAK_PROJECT_URL)

configure_file(
  input : FLATPAK_CONF_SRC,
  output : flatpakConfDst,
  configuration : flatpak_conf_data
)

flatpak_cmd = [
  'flatpak-builder', '--repo=' + FLATPAK_REPO, 
    FLATPAK_BUILD, 
    join_paths(meson.current_build_dir(), flatpakConfDst),
  '&&',
  'flatpak', 'build-bundle', 
    FLATPAK_REPO, FLATPAK_DST_NAME, FLATPAK_PROJECT_URL
]

flatpak_target = custom_target(
  'flatpak',
  command: flatpak_cmd,
  build_always_stale: false,
  output: FLATPAK_DST_NAME,
  console: true
)
