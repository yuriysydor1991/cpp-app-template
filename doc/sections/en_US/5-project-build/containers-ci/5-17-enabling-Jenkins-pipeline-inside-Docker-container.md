
## Enabling Jenkins pipeline inside Docker container

In order to enable the [Jenkins](https://www.jenkins.io/) pipeline execution inside the Docker container build and start the appropriate container with image by building the `jenkins-pipeline-docker-run` target:

```
# Inside the source root directory

# Configuring the project to support Docker with Jenkins targets
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DENABLE_DOCKER=ON -DENABLE_JENKINS_DOCKER_PIPELINE=ON

# Building and starting Jenkins' pipeline Docker container
# or restarting it
cmake --build build --target jenkins-pipeline-docker-run
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

Go to `http://127.0.0.1:8080` (port may change) address with the help of prefered Web browser. Process to finilize the installation of the [Jenkins](https://www.jenkins.io/) system with the help of it's GUI.

After successfull installation and configuration of the [Jenkins](https://www.jenkins.io/) create appropriate pipeline for the project inside the [Jenkins](https://www.jenkins.io/) Web GUI panel.

All the [Jenkins](https://www.jenkins.io/) pipeline CMake build scripts are located at [cmake/enablers/dockerers/template-project-docker-Jenkins-pipeline-runner-target.cmake](/cmake/enablers/dockerers/template-project-docker-Jenkins-pipeline-runner-target.cmake) file. The pipeline script located at [misc/Jenkinsfile](/misc/Jenkinsfile) which should be specified in the pipeline source script at the [Jenkins](https://www.jenkins.io/) Web GUI pipelines configuration page. The [Jenkins](https://www.jenkins.io/) Web GUI Docker container port may be changed by specifying a new value for the `JENKINS_PIPELINES_PANEL_HTTP_PORT` CMake variable.

The [cmake/enablers/dockerers/template-project-docker-Jenkins-pipeline-runner-target.cmake](/cmake/enablers/dockerers/template-project-docker-Jenkins-pipeline-runner-target.cmake) CMake script for the template project [Jenkins](https://www.jenkins.io/) pipeline Docker container builder by default will restart previously built contianer if target build launched repeatedly.

### What the image carries

The image extends the `jenkins/jenkins:lts` one with everything the pipelines of every branch of the template ask for, so a single container serves them all:

- the toolchain and the analyzers: `build-essential`, `cmake`, `meson` with `ninja-build`, `clang-format`, `clang-tidy`, `cppcheck`, `valgrind`, `doxygen` with `graphviz` and the GoogleTest / GoogleMock development packages;
- the development packages of every library a branch links - Qt6 with the QML, the QtCharts, the Qt Location and the WebView / WebEngine modules, Gtkmm-3 and Gtkmm-4 with the libadwaita and the WebKitGTK, SDL2, SDL3, SFML, FreeGLUT, Vulkan, OpenCV, CFITSIO with WCSLIB, PLplot, giza, Boost, libcurl, the nlohmann JSON, PostgreSQL, MySQL, Firebird and the rest of them;
- the libraries the distribution ships no package of, built from their upstream sources: wxWidgets, Wt, SQLiteCpp, the MongoDB C and C++ drivers, MatPlot++ and sdbus-c++;
- the packagers: the `flatpak` with the `flatpak-builder`, the `appimagetool`, the `rpm` and the `dpkg-dev` of the `build-essential`.

The snap, the FreeBSD pkg and the WIX MSI packagers stay out of the image: the first one demands a systemd and a LXD of its own, the second one a `cpack` built against the `libpkg` and the third one a MS Windows host.

### The packager checks

The `RUN_FLATPAK_PACKAGER`, `RUN_APPIMAGE_PACKAGER`, `RUN_DEB_PACKAGER` and `RUN_RPM_PACKAGER` build parameters of the [misc/Jenkinsfile](/misc/Jenkinsfile) pipeline build the package and fail the build when no package file appears, so the container verifies the packagers of a branch the same way it verifies its tests. All of them are off by default - turn the needed ones on at the *Build with Parameters* page of the job.

The `flatpak-builder` builds inside a [bubblewrap](https://github.com/containers/bubblewrap) sandbox and the AppImage runtime mounts itself through FUSE, which the default container profiles forbid, so the `jenkins-pipeline-docker-run` target starts the container with the `/dev/fuse` device, the `SYS_ADMIN` capability and the unconfined seccomp and AppArmor profiles.

Every runtime and SDK pair the flatpak manifests of the branches name is installed into the image, so no pipeline run downloads them again. The list is the `JENKINS_PIPELINE_FLATPAK_RUNTIMES` CMake variable and each pair costs the image gigabytes, so trim it down to the branches of interest:

```
# inside the project root directory

scripts/docker/jenkins-run.sh \
  -DJENKINS_PIPELINE_FLATPAK_RUNTIMES="org.freedesktop.Platform//24.08 org.freedesktop.Sdk//24.08"
```

They land in the per user installation of the `jenkins` user, the one the `flatpak` target of every branch builds against, which the `FLATPAK_USER_DIR` environment variable of the image keeps at the `/var/flatpak` path, out of the `/var/jenkins_home` volume that would drop it on every container start.

### The image build and the pipeline speed

- the whole package set installs in a single `apt` transaction and the BuildKit caches keep the archives and the package lists, so a repeated image build re-installs without re-downloading;
- every library built from the sources is cloned shallow, built and erased inside a single layer, so neither the sources nor the build trees reach the image;
- the image carries the `ccache` and points the `CMAKE_C_COMPILER_LAUNCHER` and the `CMAKE_CXX_COMPILER_LAUNCHER` environment variables at it, so the configure step of every branch picks it up and the repeated pipeline builds turn into cache hits;
- the built-in node keeps two executors, so the parallel test stages of the pipeline really run in parallel while the builds of the two of them still leave the host machine usable;
- the image build gets an empty directory as its context and takes the exported jobs from the tree being configured, so neither the binary tree travels to the Docker daemon nor a clone of the published branch is needed.

### Starter scripts

The [scripts/docker](/scripts/docker) directory holds the shortcuts which perform both commands above, so the whole run takes a single command:

| Script | Starts the CMake target |
| --- | --- |
| [jenkins-run.sh](/scripts/docker/jenkins-run.sh) | `jenkins-pipeline-docker-run` |
| [jenkins-build.sh](/scripts/docker/jenkins-build.sh) | `jenkins-pipeline-docker-build` |

```
# inside the project root directory

scripts/docker/jenkins-run.sh
```

Each of them configures the `build/release` directory with both the `ENABLE_DOCKER` and the `ENABLE_JENKINS_DOCKER_PIPELINE` options set to `ON` and then builds the target of interest, so no `docker` command of its own is ever issued. The `jenkins-pipeline-docker-run` CMake target depends on the `jenkins-pipeline-docker-build` one, which means the [jenkins-run.sh](/scripts/docker/jenkins-run.sh) script builds the image as well and the [jenkins-build.sh](/scripts/docker/jenkins-build.sh) one is only needed to build the image without starting the interactive container.

The scripts accept the very same parameters as the [Quick build scripts](/doc/sections/en_US/5-project-build/5-36-quick-build-scripts.md) ones, since they are their callers:

```
# inside the project root directory

# changes the Jenkins Web GUI port of the container
scripts/docker/jenkins-run.sh -DJENKINS_PIPELINES_PANEL_HTTP_PORT=9090
```

Whether the already built image and the already created container are reused or rebuilt is decided by the CMake script at the configure step, so the `--no-reconfigure` parameter keeps the decision of the previous configure run.

The `--rebuild` flag of both scripts sets the `JENKINS_PIPELINE_FORCE_REBUILD` CMake variable, which erases the container and the image and builds the image anew with the base image of the Dockerfile pulled again and no builder cache reused, so nothing of the previous image survives:

```
# inside the project root directory

scripts/docker/jenkins-run.sh --rebuild
```
