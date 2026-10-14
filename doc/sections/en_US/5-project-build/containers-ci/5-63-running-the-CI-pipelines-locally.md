## Running the CI pipelines locally

The [GitHub Actions](/doc/sections/en_US/5-project-build/containers-ci/5-47-the-GitHub-Actions-CI-pipeline.md) and the [GitLab CI/CD](/doc/sections/en_US/5-project-build/containers-ci/5-48-the-GitLab-CI-pipeline.md) pipelines start on every push, so a push to a remote which mirrors the project to both of them starts both at once - and a pipeline the push breaks stays red at both remotes until the next push repairs it. The local pipeline targets run the very same pipeline files once on the local machine, each job inside a Docker container of its own, so a broken pipeline shows up before the push does:

| Pipeline | Runner tool | CMake option | CMake target |
| --- | --- | --- | --- |
| [.github/workflows/ci.yml](/.github/workflows/ci.yml) | [act](https://github.com/nektos/act) | `ENABLE_GITHUB_ACTIONS_DOCKER_PIPELINE` | `github-actions-pipeline-docker-run` |
| [.gitlab-ci.yml](/.gitlab-ci.yml) | [gitlab-ci-local](https://github.com/firecow/gitlab-ci-local) | `ENABLE_GITLAB_CI_DOCKER_PIPELINE` | `gitlab-ci-pipeline-docker-run` |

Both tools read the pipeline files themselves, so there is no second copy of the stages to keep in sync, and a change of the pipeline file itself gets checked as well:

```
# Inside the source root directory

# Configuring the project to support Docker with both local pipeline targets
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DENABLE_DOCKER=ON \
  -DENABLE_GITHUB_ACTIONS_DOCKER_PIPELINE=ON -DENABLE_GITLAB_CI_DOCKER_PIPELINE=ON

# A single run of each pipeline
cmake --build build --target github-actions-pipeline-docker-run
cmake --build build --target gitlab-ci-pipeline-docker-run
```

A target fails when a job of its pipeline fails, the same way the pipeline turns red at the remote.

### Requirements

- the [Docker](/doc/sections/en_US/3-requirements/3-10-optional-for-docker-container-runs.md) the jobs run inside;
- the [act](https://github.com/nektos/act) executable for the GitHub Actions pipeline;
- the [gitlab-ci-local](https://github.com/firecow/gitlab-ci-local) executable together with the `rsync` it copies the project into the job containers with for the GitLab CI/CD pipeline;
- the network access, since the jobs download their images, their `apt` packages and the actions of the workflow.

The configure step stops with a message naming the missing tool, so nothing is started half way.

### The committed branch tip is what is checked

Every run clones the committed tip of the checked out branch into a workspace of its own inside the build directory - the `github-actions-pipeline-workspace` and the `gitlab-ci-pipeline-workspace` ones - and runs the pipeline there, so it checks exactly what a push publishes:

- the uncommitted changes are left out - the run lists them in a warning - so commit them before the run;
- the untracked files and the build trees of the source tree never reach the job containers;
- the state, the logs and the artifacts the runner tools leave behind stay out of the source tree.

The clone is taken at the build step, so the commits made after the configure step are in as well. The `LOCAL_PIPELINE_BRANCH` CMake variable picks another local branch, so a single checkout runs the pipelines of any branch of the template with no branch switch of its own - a detached HEAD has to name its branch that way, too:

```
# inside the project root directory

scripts/docker/pipelines-run.sh -DLOCAL_PIPELINE_BRANCH=appQt6
```

The pipeline files come from the cloned branch as well, so the run takes the `DEPENDENCIES` line of that very branch.

### The GitHub Actions runner image

The `act` tool runs every job inside a container of the image mapped to the `runs-on` label of the job. The label is read out of the workflows of the branch, and the `github-actions-pipeline-docker-build` target builds the [misc/Dockerfiles/Dockerfile.GitHub.Actions.pipeline.in](/misc/Dockerfiles/Dockerfile.GitHub.Actions.pipeline.in) image on top of the `ubuntu` image of the very same release - the `ubuntu:26.04` one for the `ubuntu-26.04` runner, the same image the GitLab CI/CD pipeline runs inside.

The hosted runner image comes with hundreds of preinstalled tools, while the jobs of the template install their tool chain themselves, so the local image carries only what the workflow takes for granted: the `sudo` the jobs call `apt-get` through, the `git` of the clang-format check and the Node.js 24 runtime of the JavaScript actions. A job which leans on a tool the hosted runner happens to preinstall fails locally, so the local run is the stricter one of the two.

Every layer of the image is cached, so the build costs seconds after the first run. The `GITHUB_ACTIONS_PIPELINE_FORCE_REBUILD` CMake variable builds it anew with the base image pulled again and no cache reused.

The JUnit reports the `Debug build & tests` job uploads land inside the `github-actions-pipeline-artifacts` directory of the build directory, the storage of the artifact server of `act`.

### The GitLab CI/CD run

The `gitlab-ci-local` tool takes the job image straight from the [.gitlab-ci.yml](/.gitlab-ci.yml), so no image of its own is built. The pipeline runs as a branch pipeline, since the `workflow` rules see the branch the workspace holds.

The JUnit `reports` of the `build-and-test` job have no local counterpart, since the tool brings back the `artifacts:paths` of a job alone - a failed test case is printed into the job log by the `ctest --output-on-failure` call instead.

### The parameters

| CMake variable | Default | What it does |
| --- | --- | --- |
| `LOCAL_PIPELINE_BRANCH` | the checked out branch | the local branch whose committed tip both pipelines check |
| `LOCAL_PIPELINE_RUN_CPPCHECK` | `OFF` | sets the `run_cppcheck` input of the GitHub Actions pipeline and the `RUN_CPPCHECK` variable of the GitLab CI/CD one, which start their `cppcheck` stage |
| `LOCAL_PIPELINE_MAX_PARALLEL_JOBS` | every job at once | the number of the jobs a run starts at once - each job builds with all the host cores on its own, so the four jobs of a pipeline load the host four times over |
| `GITHUB_ACTIONS_PIPELINE_JOB` | every job | the single job ID the GitHub Actions run is limited to, e.g. `code-format` |
| `GITLAB_CI_PIPELINE_JOBS` | every job | the space separated job names the GitLab CI/CD run is limited to, e.g. `code-format release` |
| `GITHUB_ACTIONS_PIPELINE_FORCE_REBUILD` | `OFF` | builds the runner image anew, see above |
| `GITHUB_ACTIONS_PIPELINE_RUNNER_LABEL` | the one the workflows name | the `runs-on` label the runner image stands in for, required when the workflows of a branch name more than one |
| `GITHUB_ACTIONS_PIPELINE_NODE_MAJOR` | `24` | the Node.js release line of the runner image |

### Starter scripts

The [scripts/docker](/scripts/docker) directory holds the shortcuts which perform both the configure and the build steps above, so a run takes a single command:

| Script | Starts the CMake target |
| --- | --- |
| [pipelines-run.sh](/scripts/docker/pipelines-run.sh) | `github-actions-pipeline-docker-run`, then `gitlab-ci-pipeline-docker-run` |
| [github-actions-run.sh](/scripts/docker/github-actions-run.sh) | `github-actions-pipeline-docker-run` |
| [github-actions-build.sh](/scripts/docker/github-actions-build.sh) | `github-actions-pipeline-docker-build` |
| [gitlab-ci-run.sh](/scripts/docker/gitlab-ci-run.sh) | `gitlab-ci-pipeline-docker-run` |

```
# inside the project root directory

# both pipelines - the check before a push
scripts/docker/pipelines-run.sh

# the clang-format check of the GitHub Actions pipeline alone
scripts/docker/github-actions-run.sh -DGITHUB_ACTIONS_PIPELINE_JOB=code-format

# the GitLab CI/CD pipeline with its optional cppcheck stage
scripts/docker/gitlab-ci-run.sh -DLOCAL_PIPELINE_RUN_CPPCHECK=ON
```

Each of them configures the `build/release` directory with the `ENABLE_DOCKER` option and the option of its pipeline set to `ON` and then builds the target of interest, so no `docker`, `act` or `gitlab-ci-local` command of its own is ever issued. The scripts accept the very same parameters as the [Quick build scripts](/doc/sections/en_US/5-project-build/5-36-quick-build-scripts.md) ones, since they are their callers. The [pipelines-run.sh](/scripts/docker/pipelines-run.sh) script stops at the first failed pipeline, and the `--rebuild` flag of the scripts which start the GitHub Actions pipeline sets the `GITHUB_ACTIONS_PIPELINE_FORCE_REBUILD` CMake variable:

```
# inside the project root directory

scripts/docker/github-actions-run.sh --rebuild
```

### What differs from the remote run

- `act` runs the jobs as the `root` user, while the hosted runner runs them as an unprivileged user with `sudo`, so a test which counts on a denied file permission behaves differently;
- a run is a single one, so the cancellation of the superseded pipelines - the `concurrency` group of the workflow and the `interruptible` jobs of the GitLab CI/CD pipeline - has nothing to cancel;
- the template self-checks and the packager checks of the [misc/Jenkinsfile](/misc/Jenkinsfile) stay at the [Jenkins pipeline container](/doc/sections/en_US/5-project-build/containers-ci/5-17-enabling-Jenkins-pipeline-inside-Docker-container.md), just as they do at the remotes.
