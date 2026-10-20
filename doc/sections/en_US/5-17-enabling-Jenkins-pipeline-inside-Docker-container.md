## Enabling Jenkins pipeline inside Docker container

In order to enable the [Jenkins](https://www.jenkins.io/) pipeline execution inside the Docker container build and start the appropriate container with image by building the `jenkins-pipeline-docker-run` target:

```
# inside the project root directory

# Configuring the project to support Docker with Jenkins targets
meson setup build -DENABLE_DOCKER=true -DENABLE_JENKINS_DOCKER_PIPELINE=true

# Building and starting Jenkins' pipeline Docker container
# or restarting it
meson compile -C build jenkins-pipeline-docker-run
```

Locate and save the new generated password for the [Jenkins](https://www.jenkins.io/) Web GUI in the log output that may look like next:

```
# ...

*************************************************************
*************************************************************
*************************************************************

Jenkins initial setup is required. An admin user has been created and a password generated.
Please use the following password to proceed to installation:

aefdc6a4a2214c298c821236c739165c

This may also be found at: /var/jenkins_home/secrets/initialAdminPassword

*************************************************************
*************************************************************
*************************************************************

# ...
```

Go to the `http://127.0.0.1:8080` address (the port may change) with the help of the preferred Web browser and finalize the installation of the [Jenkins](https://www.jenkins.io/) system with the help of its GUI.

After the successful installation and configuration of the [Jenkins](https://www.jenkins.io/) create a *Pipeline* job inside its Web GUI panel with the *Pipeline script from SCM* definition, point it at the repository and the branch of the project and set its *Script Path* to `misc/Jenkinsfile`.

All the [Jenkins](https://www.jenkins.io/) pipeline Meson build scripts are located at the [meson/enablers/dockerers/template-project-docker-Jenkins-pipeline-runner-target/meson.build](/meson/enablers/dockerers/template-project-docker-Jenkins-pipeline-runner-target/meson.build) file. The [Jenkins](https://www.jenkins.io/) Web GUI port of the container may be changed by specifying a new value for the `JENKINS_PIPELINES_PANEL_HTTP_PORT` Meson option.

The targets look the image and the container up each time they run, so a repeated build of the `jenkins-pipeline-docker-run` target reuses the already built image and restarts the previously created container.

### Starter scripts

The [scripts/docker](/scripts/docker) directory holds the shortcuts which perform both commands above, so the whole run takes a single command:

| Script | Starts the Meson target |
| --- | --- |
| [jenkins-run.sh](/scripts/docker/jenkins-run.sh) | `jenkins-pipeline-docker-run` |
| [jenkins-build.sh](/scripts/docker/jenkins-build.sh) | `jenkins-pipeline-docker-build` |

```
# inside the project root directory

scripts/docker/jenkins-run.sh
```

Each of them configures the `build/release` directory with both the `ENABLE_DOCKER` and the `ENABLE_JENKINS_DOCKER_PIPELINE` options set to `true` and then builds the target of interest, so no `docker` command of its own is ever issued. The `jenkins-pipeline-docker-run` Meson target depends on the `jenkins-pipeline-docker-build` one, which means the [jenkins-run.sh](/scripts/docker/jenkins-run.sh) script builds the image as well and the [jenkins-build.sh](/scripts/docker/jenkins-build.sh) one is only needed to build the image without starting the interactive container.

Every extra parameter of the scripts reaches the `meson setup` step, while their `--rebuild` flag sets the `JENKINS_PIPELINE_FORCE_REBUILD` Meson option, which erases the container and the image and builds the image anew with the base image of the Dockerfile pulled again and no builder cache reused, so nothing of the previous image survives:

```
# inside the project root directory

scripts/docker/jenkins-run.sh --rebuild
```

The container publishes its Web GUI port when it is created, so a new `JENKINS_PIPELINES_PANEL_HTTP_PORT` value reaches an already created container along with the `--rebuild` flag only:

```
# inside the project root directory

# changes the Jenkins Web GUI port of the container
scripts/docker/jenkins-run.sh --rebuild -DJENKINS_PIPELINES_PANEL_HTTP_PORT=9090
```

### Tools of the container

The [misc/Dockerfile.Jenkins.pipeline.meson](/misc/Dockerfile.Jenkins.pipeline.meson) image carries the tools the stages of the [misc/Jenkinsfile](/misc/Jenkinsfile) call: `git`, `meson` with `ninja-build`, `g++`, `pkg-config`, the GoogleTest / GoogleMock development packages, `clang-format`, `clang-tidy` and `cppcheck`, plus the tools of the optional packager stages which its Debian base distributes: `rpm` for the `RUN_RPM_PACKAGER` stage (the `RUN_DEB_PACKAGER` one needs the `dpkg-deb` every Debian based system has) and `doxygen` with `graphviz` for the documentation build. The `RUN_FREEBSD_PACKAGER` and the `RUN_WIX_PACKAGER` stages are FreeBSD and MS Windows only.

The very same job runs on a [Jenkins](https://www.jenkins.io/) instance of your own as well, as long as its agent carries the tools above - the [scripts/packages](/scripts/packages) install scripts install the ones of the build, the test and the code check stages.
