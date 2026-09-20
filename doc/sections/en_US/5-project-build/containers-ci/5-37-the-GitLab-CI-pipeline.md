## The GitLab CI/CD pipeline

The [.gitlab-ci.yml](/.gitlab-ci.yml) pipeline repeats the build, the test and the code check stages of the [misc/Jenkinsfile](/misc/Jenkinsfile) pipeline at the [GitLab CI/CD](https://docs.gitlab.com/ci/), so a fork of the project at [GitLab](https://gitlab.com/) gets the very same checks with no [Jenkins](https://www.jenkins.io/) instance of its own. Nothing has to be enabled for that: the pipeline starts on every push and on every merge request, and by hand at the *Pipelines* page of the project. Its `workflow` rules keep a single push at a single pipeline - a merge request one while a merge request is open, a branch one otherwise.

Its jobs share the single `check` stage, so they all run in parallel, each one inside a container of its own:

| Job | What it does |
| --- | --- |
| `code-format` | configures with `-DENABLE_CLANGFORMAT=ON`, builds the `clang-format` target and fails when the formatter has changed a tracked file |
| `build-and-test` | configures the Debug build with the sanitizers, the unit and the component tests, builds it and runs the `UTEST_` and the `CTEST_` `ctest` suites |
| `clang-tidy` | configures with `-DENABLE_CLANG_TIDY=ON` and builds, so the checks run during the compilation |
| `release` | builds the Release configuration and installs it into a prefix inside the build directory |

Every `ctest` run writes a JUnit XML report, which the job hands to GitLab as its test report, so a failed test case is readable at the *Tests* tab of the pipeline page with no digging through the logs. The jobs are `interruptible`, so a new push to a branch cancels the still running pipeline of its previous commit as long as the *Auto-cancel redundant pipelines* setting of the project stays on.

### The image and the branch dependencies

The jobs run inside the [ubuntu:26.04](https://hub.docker.com/_/ubuntu) image - the release the [GitHub Actions workflow](/doc/sections/en_US/5-project-build/containers-ci/5-36-the-GitHub-Actions-CI-pipeline.md) pins its runner to, so both pipelines take the very same packages. The image carries a bare system, so a job installs its whole tool chain itself with the single `apt-get install` line of the `before_script`: the `TOOLS` every job needs, the `JOB_TOOLS` of the job itself and the `DEPENDENCIES` of the branch:

```
variables:
  BUILDDIR: build
  BDJUNITOUT: junit-out
  # The tools every job needs on top of the bare image.
  TOOLS: build-essential cmake g++ git ca-certificates pkg-config
  # The development packages of the branch specific libraries.
  DEPENDENCIES: ''
```

That last variable is the single line the branches of the template differ by, so a project which links a library of its own appends the development package of the library there. This branch asks for no package besides the common tools, so its own line stays empty.

### The manual parameters

The *Run pipeline* page of the project starts the pipeline with the prefilled variables mirroring the [misc/Jenkinsfile](/misc/Jenkinsfile) parameters:

| Variable | The Jenkins counterpart | What it starts |
| --- | --- | --- |
| `RUN_CPPCHECK` | `RUN_CPPCHECK` | the build of the `cppcheck` target inside the `build-and-test` job |

It stays `false` by default, since the check costs minutes of the runner time which every push would pay for.

### What stays at the Jenkins pipeline

The template self-checks of the [misc/Jenkinsfile](/misc/Jenkinsfile) - the doc sections and their README links, the markdown links, the external documentation URLs, the registered enablers and the registered tests - have no counterpart here, and neither have its packager checks: the pipeline keeps to the stages a plain container covers, while the packagers ask for the runtimes and the tools the Jenkins pipeline container carries.
