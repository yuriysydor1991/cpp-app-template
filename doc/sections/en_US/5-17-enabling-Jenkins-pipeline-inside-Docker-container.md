## Enabling Jenkins pipeline inside Docker container

**Currently the Jenkins pipeline Docker target is not integrated into the `appMeson` branch.** The CMake-driven `jenkins-pipeline-docker-run` target ships with the `app` branch only. The notes below describe the intended workflow once the equivalent Meson target lands; for now the [misc/Jenkinsfile](/misc/Jenkinsfile) pipeline script can still be wired into a Jenkins instance hosted independently.

In order to enable the [Jenkins](https://www.jenkins.io/) pipeline execution inside the Docker container, build and start the appropriate container with image by building the `jenkins-pipeline-docker-run` target:

```
# Inside the source root directory

# Configuring the project to support Docker with Jenkins targets
meson setup build --buildtype=debug -DENABLE_DOCKER=true -DENABLE_JENKINS_DOCKER_PIPELINE=true

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

Go to `http://127.0.0.1:8080` (port may change) address with the help of preferred Web browser. Process to finalize the installation of the [Jenkins](https://www.jenkins.io/) system with the help of it's GUI.

After successful installation and configuration of the [Jenkins](https://www.jenkins.io/) create appropriate pipeline for the project inside the [Jenkins](https://www.jenkins.io/) Web GUI panel.

Once landed, the [Jenkins](https://www.jenkins.io/) pipeline Meson build scripts would live next to the other Docker target scripts under `meson/template-project-dockerers/`. The pipeline script located at [misc/Jenkinsfile](/misc/Jenkinsfile) which should be specified in the pipeline source script at the [Jenkins](https://www.jenkins.io/) Web GUI pipelines configuration page. The [Jenkins](https://www.jenkins.io/) Web GUI Docker container port may then be changed by specifying a new value for the `JENKINS_PIPELINES_PANEL_HTTP_PORT` Meson option.

The Meson scripts for the template project [Jenkins](https://www.jenkins.io/) pipeline Docker container builder are expected to restart the previously built container if the target build is launched repeatedly - matching the behaviour of the CMake-based implementation on the `app` branch.
