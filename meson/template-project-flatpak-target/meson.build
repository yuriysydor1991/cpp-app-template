find_program('flatpak', required: true)
find_program('flatpak-builder', required: true)

FLATPAK_PROJECT_URL = 'ua.org.kytok.template.' + meson.project_name()
FLATPAK_TARGET_ARCH = run_command('flatpak', '--default-arch', check: true).stdout().strip()
FLATPAK_REPO = join_paths(meson.current_build_dir(), meson.project_name() + '-repo')
FLATPAK_BUILD = join_paths(meson.current_build_dir(), meson.project_name() + '-flatpak-build')
flatpakConfDst = 'flatpak.conf.json'
FLATPAK_CONF_SRC = join_paths('..', '..', 'misc', 'flatpak.conf.json.meson.in')

# the runtime the bundle demands, the GUI framework picks it (e.g. gnome-49 for
# the org.gnome.Platform 49), so the bundle names it instead of the build host
flatpak_conf_text = import('fs').read(FLATPAK_CONF_SRC)
FLATPAK_RUNTIME = '-'.join([
  flatpak_conf_text.split('"runtime": "')[1].split('"')[0].split('.')[1],
  flatpak_conf_text.split('"runtime-version": "')[1].split('"')[0],
])
FLATPAK_DST_NAME = '-'.join(
  [meson.project_name(), meson.project_version(), FLATPAK_TARGET_ARCH, FLATPAK_RUNTIME]
) + '.flatpak'

FLATPAK_DEPS_REMOTE = 'flathub'
FLATPAK_DEPS_REMOTE_URL = 'https://dl.flathub.org/repo/flathub.flatpakrepo'

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
  'flatpak', 'remote-add', '--user', '--if-not-exists', 
    FLATPAK_DEPS_REMOTE, FLATPAK_DEPS_REMOTE_URL,
  '&&',
  'flatpak-builder', '--user', '--install-deps-from=' + FLATPAK_DEPS_REMOTE, 
    '--assumeyes', '--force-clean', '--repo=' + FLATPAK_REPO, 
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
