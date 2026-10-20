find_program('docker', required: true)

# The container, the image, the Dockerfile and the Jenkins Web GUI port of the
# commands below.
jenkins_pipeline_docker_env = [
  'DOCKER_BUILDKIT=1',
  'CONTAINER=' + meson.project_name().to_lower() + '-jenkins-pipeline-run-container',
  'IMAGE=' + meson.project_name().to_lower() + '-jenkins-pipeline-image',
  'DOCKERFILE=' + join_paths(meson.project_source_root(), 'misc', 'Dockerfile.Jenkins.pipeline.meson'),
  'PORT=' + get_option('JENKINS_PIPELINES_PANEL_HTTP_PORT').to_string(),
]

# The commands look the image and the container up each time they run, so the
# already built image and the already created container are reused.
jenkins_pipeline_docker_build_cmd = [
  'docker image inspect "$IMAGE" > /dev/null 2>&1 && echo "Image $IMAGE already built" ||',
  'docker build -f "$DOCKERFILE" -t "$IMAGE" .',
]

# The forced rebuild erases the container and the image. The erased image
# leaves both its own layers and the pulled base image of the Dockerfile behind
# in the builder cache, so the build refuses the cache and pulls the base image
# anew, otherwise it reproduces the very same image.
if get_option('JENKINS_PIPELINE_FORCE_REBUILD')
  jenkins_pipeline_docker_build_cmd = [
    'docker container rm -f "$CONTAINER" 2> /dev/null;',
    'docker image rm -f "$IMAGE" 2> /dev/null;',
    'docker build --no-cache --pull -f "$DOCKERFILE" -t "$IMAGE" .',
  ]
endif

jenkins_pipeline_docker_run_cmd = [
  'echo "Connect to the Jenkins GUI at started docker at http://127.0.0.1:$PORT" &&',
  'if docker container inspect "$CONTAINER" > /dev/null 2>&1;',
  'then docker container start -ia "$CONTAINER";',
  'else docker run -it -p "$PORT:8080" -p 50000:50000 --name "$CONTAINER" "$IMAGE";',
  'fi',
]

jenkins_pipeline_docker_build_target = custom_target(
  'jenkins-pipeline-docker-build',
  command: ['sh', '-c', ' '.join(jenkins_pipeline_docker_build_cmd)],
  env: jenkins_pipeline_docker_env,
  build_always_stale: false,
  output: 'jenkins-pipeline-docker-build-stub.txt',
  console: true
)

jenkins_pipeline_docker_run_target = custom_target(
  'jenkins-pipeline-docker-run',
  command: ['sh', '-c', ' '.join(jenkins_pipeline_docker_run_cmd)],
  env: jenkins_pipeline_docker_env,
  depends: jenkins_pipeline_docker_build_target,
  build_always_stale: false,
  output: 'jenkins-pipeline-docker-run-stub.txt',
  console: true
)
