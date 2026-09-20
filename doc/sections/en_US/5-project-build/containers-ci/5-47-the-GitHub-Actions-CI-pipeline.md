## The GitHub Actions CI pipeline

The [.github/workflows/ci.yml](/.github/workflows/ci.yml) workflow repeats the build, the test and the code check stages of the [misc/Jenkinsfile](/misc/Jenkinsfile) pipeline at the [GitHub Actions](https://docs.github.com/en/actions), so a fork of the project gets the very same checks with no [Jenkins](https://www.jenkins.io/) instance of its own. Nothing has to be enabled for that: the workflow starts on every push and on every pull request, and by hand at the *Actions* page of the repository.

Its jobs run in parallel, each one on a runner of its own:

| Job | What it does |
| --- | --- |
| `Code format (clang-format)` | configures with `-DENABLE_CLANGFORMAT=ON`, builds the `clang-format` target and fails when the formatter has changed a tracked file |
| `Debug build & tests` | configures the Debug build with the sanitizers, the unit and the component tests, builds it and runs the `UTEST_` and the `CTEST_` `ctest` suites |
| `clang-tidy` | configures with `-DENABLE_CLANG_TIDY=ON` and builds, so the checks run during the compilation |
| `Release build & install` | builds the Release configuration and installs it into a prefix inside the build directory |

Every `ctest` run writes a JUnit XML report, which the job uploads as the `junit-results` artifact of the run, so a failed test case is readable at the run page with no digging through the logs. A new push to a branch cancels the still running pipeline of its previous commit - the `concurrency` group of the workflow takes care of that.

### The runner and the branch dependencies

The jobs run on the pinned `ubuntu-26.04` runner instead of the moving `ubuntu-latest` one, which switches to the next LTS release on its own while the packages a branch asks for differ between the releases. The [runner image](https://github.com/actions/runner-images/blob/main/images/ubuntu/Ubuntu2604-Readme.md) preinstalls the compilers and the clang tools, so a job adds the rest with a single `apt-get install` line, the `DEPENDENCIES` variable of the workflow among them:

```
env:
  BUILDDIR: build
  BDJUNITOUT: junit-out
  # The development packages of the branch specific libraries.
  DEPENDENCIES: ''
```

That variable is the single line the branches of the template differ by, so a project which links a library of its own appends the development package of the library there. This branch asks for no package the runner image misses, so its own line stays empty.

### The manual parameters

The *Run workflow* button of the *Actions* page starts the pipeline with the parameters mirroring the [misc/Jenkinsfile](/misc/Jenkinsfile) ones:

| Parameter | The Jenkins counterpart | What it starts |
| --- | --- | --- |
| `run_cppcheck` | `RUN_CPPCHECK` | the build of the `cppcheck` target inside the Debug job |

It stays off by default, since the check costs minutes of the runner time which every push would pay for.

### What stays at the Jenkins pipeline

The template self-checks of the [misc/Jenkinsfile](/misc/Jenkinsfile) - the doc sections and their README links, the markdown links, the external documentation URLs, the registered enablers and the registered tests - have no counterpart here, and neither have its packager checks: the workflow keeps to the stages a plain runner covers, while the packagers ask for the runtimes and the tools the [Jenkins pipeline container](/doc/sections/en_US/5-project-build/containers-ci/5-17-enabling-Jenkins-pipeline-inside-Docker-container.md) carries.
