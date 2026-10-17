if host_machine.system() != 'windows'
  warning(
    'ENABLE_WIX was requested on a non-Windows host. The wix target will be ' +
    'configured but the actual MSI build requires the WiX Toolset (candle.exe / ' +
    'light.exe) which is only available on Microsoft Windows.'
  )
endif

candle_exec = find_program('candle', 'candle.exe', required: false)
light_exec = find_program('light', 'light.exe', required: false)

# the WiX names of the CPUs, the 32-bit ones install into the 32-bit Program Files
wix_arch = {'x86_64': 'x64', 'aarch64': 'arm64'}.get(host_machine.cpu_family(), host_machine.cpu_family())
wix_program_files = wix_arch in ['x64', 'arm64'] ? 'ProgramFiles64Folder' : 'ProgramFilesFolder'
wix_upgrade_guid = '12345678-1234-1234-1234-123456789012'
wix_output = meson.project_name() + '-' + meson.project_version() + '-' + wix_arch + '-' + package_os + '.msi'

wxs_path = join_paths(meson.current_build_dir(), meson.project_name() + '.wxs')

configure_file(
  output: meson.project_name() + '.wxs',
  configuration: {
    'PROJECT_NAME': meson.project_name(),
    'PROJECT_VERSION': meson.project_version(),
    'PROJECT_DESCRIPTION': project_description,
    'PROJECT_MAINTAINER': get_option('PROJECT_MAINTAINER'),
    'WIX_UPGRADE_GUID': wix_upgrade_guid,
    'WIX_ARCH': wix_arch,
    'WIX_PROGRAM_FILES': wix_program_files,
  },
  input: join_paths(meson.project_source_root(), 'misc', 'wix.wxs.in')
)

if candle_exec.found() and light_exec.found()
  wix_obj = join_paths(meson.current_build_dir(), meson.project_name() + '.wixobj')
  wix_cmd = [
    'sh', '-c',
    'set -e && ' +
    candle_exec.full_path() + ' -arch ' + wix_arch + ' -out ' + wix_obj + ' ' + wxs_path + ' && ' +
    light_exec.full_path() + ' -out ' + join_paths(meson.project_build_root(), wix_output) + ' ' + wix_obj
  ]

  wix_target = custom_target(
    'wix',
    command: wix_cmd,
    build_always_stale: true,
    output: wix_output,
    console: true
  )
else
  message(
    'WiX Toolset (candle/light) not found. The .wxs source has been configured ' +
    'at ' + wxs_path + ' but no MSI target was declared.'
  )
endif
