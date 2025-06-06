find_program('docker', required: true)

DOCKER_HOST_ADDRESS = '127.0.0.1'
DOCKER_HOST_PORT = '2375'
DOCKER_HOST_STR = 'tcp://' + DOCKER_HOST_ADDRESS + ':' + DOCKER_HOST_PORT
DOCKER_SINGLE_RUN_NAME = meson.project_name().to_lower() + '-docker-single-run'
DOCKERFILE_SRC = join_paths(meson.project_source_root(), 'misc', 'Dockerfile.meson.in')
DOCKERFILE_DST = 'Dockerfile'
DOCKERFILE_DST_PATH = join_paths(meson.current_build_dir(), DOCKERFILE_DST)

conf_data = configuration_data()

conf_data.set('PROJECT_BINARY_NAME', meson.project_name())

configure_file(
  input : DOCKERFILE_SRC,
  output : DOCKERFILE_DST,
  configuration : conf_data
)

docker_single_run_cmd_str = 'docker build -f ' + DOCKERFILE_DST_PATH + ' --build-context project='
docker_single_run_cmd_str += meson.project_source_root() + ' --build-arg CACHEBUST="' + timestamp + '" -t' + DOCKER_SINGLE_RUN_NAME
docker_single_run_cmd_str += ' . && docker run --rm ' + DOCKER_SINGLE_RUN_NAME

docker_single_run_target = custom_target(
  'docker-single-run',
  command: ['sh', '-c', docker_single_run_cmd_str],
  env: ['DOCKER_HOST=' + DOCKER_HOST_STR, 'DOCKER_BUILDKIT=1'],
  build_always_stale: false,
  output: 'docker-output-stub.txt',
  console: true
)
