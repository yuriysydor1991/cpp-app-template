## Enabling the Docker container build and run

To be able to build and run the Docker container with current template project' target binary file enable it's Meson target with setting the `ENABLE_DOCKER` option to the `true` value by using the next command:

```
# inside the project root directory

meson setup build -DENABLE_DOCKER=true
```

After that there should be available the Docker build and run Meson target `docker-single-run` which may be triggered with the command:

```
# inside the project root directory

meson compile -C build docker-single-run
```

Examine the `meson/enablers/dockerers/template-project-dockerers/meson.build` file for the `docker-single-run` target details.

### Starter scripts

The [scripts/docker](/scripts/docker) directory holds the shortcuts which perform both commands above, so the whole run takes a single command:

| Script | Starts the Meson target |
| --- | --- |
| [single-run.sh](/scripts/docker/single-run.sh) | `docker-single-run` |
| [single-build.sh](/scripts/docker/single-build.sh) | `docker-single-build` |

```
# inside the project root directory

scripts/docker/single-run.sh
```

Each of them configures the `build/release` directory with the `ENABLE_DOCKER` option set to `true` (an already configured directory is reconfigured and keeps its other options) and then builds the target of interest, so no `docker` command of its own is ever issued. The `docker-single-run` Meson target depends on the `docker-single-build` one, which means the [single-run.sh](/scripts/docker/single-run.sh) script builds the image as well and the [single-build.sh](/scripts/docker/single-build.sh) one is only needed to build the image without starting a container.

Every extra parameter of the scripts reaches the `meson setup` step of the `build/release` directory. The image configures the project inside of it with the default options, so they don't reach the binary the container runs.

Keep in mind that the `ENABLE_DOCKER` option makes the configure step require the `docker` executable to be present in the system, so the scripts fail the configure step on a machine with no Docker installed (see the [Optional for the Docker container runs](/doc/sections/en_US/3-10-optional-for-docker-container-runs.md) requirements section).
