# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [appMeson0.11.0] - 2026-11-08

- 49bcf4e Removing the destination OS from the AppImage package name
- 002b345 Introducing the STT branches info into the READMEs
- 74164be Introducing the appWebAssembly branch info into the READMEs
- aeaa19f Introducing the docker starter scripts and the Jenkins container targets
- 87f047a Grouping the meson directory modules as the cmake ones
- 226b55c Introducing the appLlamaCPP branch info into the READMEs
- fc60c88 Introducing the TTS branches info into the READMEs
- 3c4f0c9 Introducing the destination OS into the package names
- 7e1287a Synchronizing the template flavors list of the READMEs
- 62660ac Refreshing the shared library cache after the from-source installs
- f94afae Failing the CI test stages which match no tests
- 1f9d025 Fixing the nesting of the binary hardening entry of the build index pages
- 1982e79 Fixing the flatpak requirements section naming an outdated SDK version
- da921f4 Listing every linked doc section in the requirements and build index pages
- 162a717 Fixing the documentation links pointing into the other language
- 7ad10b0 Fixing the flatpak target failing on its repeated build
- b687d97 Fixing the cppcheck findings of the new signals handler, tests and log mock
- ec6256d Updating the app component diagram to the signals handlers design
- a818b65 Renumbering the custom command line parameters section numbered 4-6 twice
- 7c91b1d Documenting the built in command line options and the usage errors
- 57e548c Testing the application with the real command line arguments
- 73c190a Parsing the command line before the log file initialization
- fff8a23 Exiting with a failure status on the command line usage errors
- f4b15e0 Fixing the missing option value raising the version flag instead of the help one
- eba0d66 Fixing the CommandLineParser test assertions which could not fail
- c281374 Fixing the log mock LOG_INIT forwarding into the LOG_INIT_DEFAULTS mock
- f8fe43e Restoring the previous signal dispositions on the signals handler uninstall
- 41c227c Leaving the SIGTTIN and SIGTTOU signals to the shell job control
- 619200c Adding the missing semicolon of the Application log macro call
- fc4c6bb Fixing the logger level filter tests which could not fail
- 5db9e62 Fixing the log macros to expand into single statements
- 014553a Fixing the logger data races on the log file reopening and the level
- ff1566b Fixing the log file open failure aborting the process
- 5db0795 Splitting the CTEST_DefaultLogger helper classes into own files
- ed3c3dd Splitting the packages install scripts per OS release
- c479ed8 Removing the CMake leftovers of the Meson flavor
- 9445258 Introducing the markdown links and the AppImage stages into the Meson pipeline
- 90bac66 Replacing the placeholder Jenkins container docs of the Meson flavor
- 08353f9 Fixing the Meson option values and the stale names of the docs
- 27626ce Synchronizing the CommandLineParser parse doc comment with app
- 3561202 Synchronizing the ApplicationContext unit tests with app
- 1b501f4 Synchronizing the get_stop assertions of the application tests with app
- 3ef6790 Synchronizing the logger subsystem with the app branch
- 14e9715 Fixing the custom installation path docs of the Meson install
- fbeb9b2 Removing the docs of the nonexistent GTEST_TRY_SYSTEM_PROBE Meson option
- 60b4b53 Installing the GTest development packages the Meson tests probe for
- 64a3dd5 Fixing the snap command path of the Meson packager
- a91b980 Producing a real AppImage with the appimagetool in the Meson packager
- 15cce91 Fixing the gmon.out path of the Meson gprof-analyze target
- 0d148d7 Passing the Meson sanitizers flags through a dependency object
- e9d01f2 Adding the check kwarg to the Meson run_command calls
- d6c42a6 Fixing the Doxygen documentation build of the Meson projects
- 010a72e Fixing the deb package ownership and install prefix of the Meson packager
- 2468b3a Fixing the RPM package target of the Meson packager
- 5e086af Applying the Meson sanitizers flags to every target
- 59f0fac Enabling the inline suppressions in the Meson cppcheck target
- 69cf340 Replacing the unreachable GNU gettext site link with its Savannah page
- 504966b Fixing the WIX installer architecture of the Meson packager
- 5e3a019 Fixing the FreeBSD pkg manifest and file list of the Meson packager
- c07b7fd Introducing the destination CPU architecture into the package names
- e270506 Introducing the appGettext branch info into the READMEs
- 913961a Introducing the appDarknetXX branch info into the READMEs
- 19c5da7 Introducing the RedHat packages install script
- 819b2f0 Introducing the appWhisperCPP branch info into the READMEs
- 393b36e Introducing the FreeBSD packages install script
- 8d5982a Fixing the absent common.sh of the packages install scripts
- 3c89420 Introducing the appV8 branch info into the READMEs
- eb7d431 Erasing the build sources and trees of the docker images
- e5676c3 Resetting the inherited signals dispositions in the signals handlers tests
- 144f3fa Introducing the binary hardening options section into the READMEs
- b83272f Introducing the binary hardening compile and link options
- 4a32bcc Introducing the GitLab CI/CD pipeline section into the READMEs
- 221a53a Introducing the GitLab CI/CD pipeline mirroring the Jenkinsfile
- ae38a54 Introducing the GitHub Actions CI pipeline section into the READMEs
- 27cf776 Introducing the GitHub Actions CI pipeline mirroring the Jenkinsfile
- 8a98bfc Correcting the appQt6QtDBusClient branch description in the READMEs
- 5dce722 Limiting the documentation checks to the repository own markdown files
- 72fc8c4 Excluding the GCC own include directories from the clang-tidy search path
- cb070b5 Accepting the 405 documentation URLs
- d478ea2 Spacing out the branch entries in the READMEs
- ff58f89 Rewording the DOCKER_HOST environment requirement in the docker docs
- eb74316 Removing the DOCKER_HOST variables from the docker enablers
- ed5096b Excluding the build trees from the Docker build context
- 3d608e3 Retrying the unreachable documentation URLs and accepting the 403 ones
- 62d748a Introducing the audio assets branches info into the READMEs
- 59707c8 Introducing the app signals handlers subcomponent
- a745415 Adding the build artifacts directory into the ignore list
- f461e7b Declaring the main function argv parameter as an array
- 95a2e75 Dropping the packagers and the development tools from the packages install list
- b12afba Introducing the --install flag into the packager build scripts
- 1d47e04 Renaming the packages install script and adding the Ubuntu one
- 4fdfd71 Introducing the required packages install script
- 3142f41 Installing the flatpak build dependencies from the flathub remote
- 169bbf8 Dropping the redundant build step from the packager scripts
- cb47d09 Introducing the per packager build scripts
- c97e6c2 Introducing the appCFITSIO branch info into the READMEs
- 6ffc536 Introducing the appGtkmm4Libadwaita branch info into the READMEs
- f2e923f Pinning the log message stream to the classic locale
- 4e573c5 Decomposing the IApplication descendants into the applications subcomponent
- ce09ee7 Introducing the appFontAwesome branch info into the READMEs
- 71e81ab Incrementing version to appMeson0.11.0
- 47fc928 Release appMeson0.10.0 at 2026-08-17

## [appMeson0.10.0] - 2026-08-17

- 91198d9 Introducing the InsertNewlineAtEOF clang-format option
- 0b8c7a5 Repairing the dead snapcraft installation documentation URL
- 30b9b72 Introducing the appCURLChatGPT branch info into the READMEs
- b3d9a90 Hiding the ApplicationContext fields and adding the atomic stop flag
- 80cf589 Introducing the appCURLClaude branch info into the READMEs
- f88cf2b Introducing the external documentation URLs check into the Jenkins pipeline
- 811f8e7 Making the docker containers run under unprivileged users
- 43a6ace Renaming the SimpleLogger component into the DefaultLogger
- f2b7fd8 Build the test argv array after the argument string is assigned
- ab6d94f Mark the application destructors with the override specifier
- 79a7dbb Give cppcheck the project header directories
- 23b0fd8 Suppress the cppcheck missingIncludeSystem and unusedStructMember warnings
- 2ae2dd0 Fix the clang-tidy pipeline stage of the Meson build
- b1fd790 Resolve the leftover .gitignore merge conflict markers
- 1fe1b2c Introducing the appPGPLOT branch info into the READMEs
- e99b693 Group the enabler documentation under subsections in the READMEs
- e2e9102 Group the compression branches under a dedicated README section
- 799ba1b Introducing the appLZMA branch info into the READMEs
- 3da1200 Introducing the appZlib branch info into the READMEs
- abdf034 Introducing the appGtkmm4Vulkan branch info into the READMEs
- 6848c83 Removing the appGtkmm4Vulkan branch info from the READMEs
- faa7073 Introducing the appQt6Vulkan and appGtkmm4Vulkan branches info into the READMEs
- 6af30ed Introducing the appFirebird branch info into the READMEs
- 748e6d0 Introducing the appGtkmm4GDBusClient branch info into the READMEs
- 9ef3b5d Introducing the appQt6GLArea branch info into the READMEs
- 250fe09 Introducing the appGtkmm4GLArea branch info into the READMEs
- 1cc14f7 Splitting the Data Visualization README category into Plots/Graphs and Maps
- a64e517 Introducing the applibMeson branch info into the READMEs
- b89b900 Introducing the appSFML branch info into the READMEs
- 5de7fe9 Introducing the appwxWidgets branch info into the READMEs
- 52e7257 Introducing the appQt6QtDBusClient branch info into the READMEs
- 4ba9097 Introducing the appQt6QtLocation branch info into the READMEs
- 6e70019 Introducing the appQt6ChartView branch into the READMEs
- 9899417 Introducing the appGtkmm4LeafLet and appQt6LeafLet branches info into the READMEs
- 932e098 Introducing the Meson-based Jenkins pipeline for the appMeson branch
- 5dca5e7 Introducing the appSDBusCxxClient and appSDBusCxxServer branches info into the READMEs
- 297fb27 Adding .claude dir to .gitignore
- 7238278 Introducing project structure section Будь ласка, зверніться до адміністратора subsection
- 3398bdc Introducing the libMeson branch info into the READMEs
- 29370ad Decomposing the Meson extra features doc and migrating CMake commands to Meson
- 5b1fc2a Bringing the appMeson branch up to date with the app branch integrations
- c58909c Introducing info about newly created branch appOpenCV into READMEs.
- 1a46864 Introducing the appPLplot branch info into the READMEs
- 32393dc Introducing the MatPlot++ appMatPlotxx branch into the READMEs
- 241cabc Switching off the clang-tydy's unrecognizable AnalyzeTemporaryDtors config param
- 49c44a3 Loggging README's misspell refine
- 174891a Grouping and categorising available template flavors links in the READMEs
- 18f9987 Decomposing READMEs
- f6e77d5  Introducing the --branch cmd line flag for git clone command in the READMEs
- 2ded3d8 Introducing explicit template altering notice in the READMEs headers
- 170855c Introducing the appGtkmm4 branch info into the READMEs
- 0e5821f Introducing the PlantUML app component diagram into the READMEs
- cf92227 Refining the branches link in the READMEs, introducing gitlab links also
- 63cb3d3 Adding money emoji to donation notice in the READMEs
- 4f8b42b Introducing the appCURL branch info into the READMEs
- 25e6149 Removing redundant cpp-check suppression
- 3d4ec3f Refining unit tests to match the new log code
- b1e8b09 Introducing a custom log file cmd param for the executable
- 3a12a53 Introducing the CMDParamNames class to encapsulate CMD params names
- 3c9819d Introducing some marketing sentences in the README's goal section
- 071fc8e Avoiding unnecessary badly portable localtime_r usage
- ebb48c7 Introducing the thread id into simple logger
- c4d82e5 Avoiding backward time in the simple logs
- cbc3044 Avoiding final log multiple str fetches
- 095957b Refining the log current timestamp method, increasing thread safety
- fab155f Adding *.log files to the .gitignore file
- f92f9a5 Incrementing version to 0.10.0
- f3f688c Release appMeson0.9.0 2025-06-06

## [appMeson0.9.0] - 2025-06-06

- d7e1b19 Introducing the Docker optional packages into the READMEs
- 95f90b3 introducing the suppression list for the cppcheck false positives
- 79bc9bb Implementing docker container build and start target in the Meson
- c15ad1c Transferring the Dockerfile
- f8cda8d Adding project neatness to the READMEs
- 94205e5 Refining the flatpak setup and build info in the READMEs
- f2e3e4b avoided redundant path computing
- 101c8f7 Introducing the flatpak target for the Meson
- 8af17ed Refining UTs with new mock for introduced log subsystem
- a11cef4 Introducing the appLog4Cpp5 branch info into the READMEs
- 5386eae Implementing the logging macros and a simple logger to perform log messaging
- 7d09cd8 Introducing the appMongoDBCpp4 branch info into the READMEs
- 595a5f2 Specifying the Meson build system in the flatpak json conf
- a82c5a2 Introducing the appSQLiteCpp3 branch info into the READMEs
- c17ca9b Refining the ApplicationContext mock
- b134ae6 Introducing the gitlab mirror into the READMEs
- 20dee48 Introducing the appMySQLCppConn branch info into the READMEs
- fcb6a4c Introducing the appBoostBeast branch info into the READMEs
- bccbea8 Explicitly specifying the combining of the template branches
- b733c7c introducing the appPgSQLxx branch into the READMEs
- 518e7d8 Introducing a new appWt4 branch info into the READMEs
- e83065e Introducing the error exit code for a cppcheck target
- bde939d Refining the cppcheck target description in the READMEs
- 9c2de4e Style refining of meson/meson.build
- 82b4fb1 Introducing the cppcheck target
- 0edf8be Decomposing the projects source configure into separate meson file
- d59e8d4 Decomposing the sources variable into separate meson file
- 6e479f4 Introducing the builddir to the .gitignore
- c7d425c Replacing English current in the uk_UA README
- 740c8e4 Introducing the donation notice into the READMEs
- 6582494 Refining the clang-format target info in the READMEs
- db5f6c0 Reintroducing the clang-format target for all available sources
- 2d0ea01 Introducing the appMeson branch info into the READMEs
- 2532aec Refining tests enabling sections in the READMEs
- dc4f5f4 Introducing suits for the test declarations in meson files
- 11cd8b2 Introducing meson configuration for the CommandLineParser UTs
- 4d3e183 Introducing meson configuration for the ApplicationVersionPrinter UT
- d30293a Introducing meson configuration for the ApplicationHelpPrinter UT
- b0f3bb4 Introducing meson configuration for the ApplicationFactory UT
- 0d8e0ce Introducing meson configuration for the ApplicationContext UT
- c5a9728 Introducing first unit test for the Application class
- 75b3294 Converting some commands to meson in READMEs
- d85e62d Adjusting the Doxygen-doc target
- bd0753f Adjusting Doxygen-doc target and making main executable installable
- c0b4d12 Adding the Doxygen target with some meson decomposition
- 9f97db6 Refining install commands for the READMEs
- a6cea5d Increasing the warning level
- e5371da Introducing the basic meson file for the main.cpp
- c7c55ee Erasing all the CMakeLists.txt files
- 97a6442 Refining READMEs
- 05af0e5 Refining branches info
- c8de777 Introducing the flatpak sections into the READMEs
- 69ffe40 Introducing the flatpak package creation from the template source.
- 4b00b9f Inserting the release tag link
- 8bd91be Incrementing version to 0.8.0

## [app0.8.0] - 2025-03-20

- dfff631 Release app0.8.0 2025-03-20
- c2d08e9 Replacing int flag with a bool for the CommandLineParser
- 5adff97 Erasing the /analyze from the default MSVC compile options
- 3a70693 Introducing the DEB package gen info in the READMEs
- a408273 Introducing the cpack configuration for the deb package generation
- e9d052e Introducing the LICENSE file with free of use license and notice
- f42d640 Fixing typo in the README
- 3f3d38e Introducing the clang-tidy info into the READMEs
- dfc52ec Introducing clang-tidy
- 3bb98fb Introducing the appSDL2 branch into the READMEs
- 29532bc Erasing redundant libraries installation info
- 41450f5 Introducing the FreeGlut/OpenGL appFreeGlut branch info into READMEs
- 6cdefed Incrementing version to 0.8.0

## [app0.7.0] - 2025-03-17

- b2ae262 Release app0.7.0 2025-03-17
- 4f45e8d Introducing MS Windows tools install description into READMEs
- 7d7defd Avoiding the compilation warnings at the UTEST_CommandLineParser
- 39d9486 Adding MSVC settings file to the .gitignore
- b04d376 Introducing MSVC extra compile options for warnings
- 5f18f5a Adding the out directory for MSVC into .gitignore
- b7e960b Specifying the appGtkmm3Glade branch in the READMEs
- ef33819 Introducing the appGtkmm3 branch info into the READMEs
- 68a1efa Revert "Introducing the GTKmm-3.0 window infrastructure."
- 6adae7b Revert "Adding gtkmm-3.0 to required packages in READMEs"
- e19f268 Adding gtkmm-3.0 to required packages in READMEs
- eedd7ac Introducing the GTKmm-3.0 window infrastructure.
- 1da93db Replacing the /usr/bin prefix parameter with right /usr in installation section
- adc02d6 Introducing the lib branch info into the READMEs
- 6230596 Introducing the appQt6 branch in READMEs
- d044fe4 Incrementing version to 0.7.0

## [app0.6.0] - 2025-03-14

- 9bd89d8 Release app0.6.0 2025-03-14
- 1192ec5 Introducing branch info and README translations into uk_UA README
- 14da387 Introducing Doxygen doc with translated README as main page facility
- 074df94 Introducing COMPILE_WARNINGS_AS_ERRORS and ENABLE_COMPILER_CODE_ANALYZER CMake vars.
- 88156b6 Specifying translation documents for the root README under the doc
- 8b10176 Specifying the source file for the PROJECT_BINARY_NAME CMake variable
- 3920a3a Introducing multibranch info into the root README.md
- e19aef1 README.uk_UA.md links refinement
- ec31437 The root README.md file translation to uk_UA workflow final
- be2dd4d The root README.md file translation to uk_UA workflow (pre Installing executable)
- 421f046 The root README.md file translation to uk_UA workflow (pre Run section)
- 86ac202 The root README.md file translation to uk_UA workflow (pre clang-format)
- a443a83 The root README.md file translation to uk_UA workflow (pre enabling testing)
- 8da8536 The root README.md file translation to uk_UA workflow.
- cadecf3 Introducing translated root README in uk_UA.
- a5f282c Incrementing version to 0.6.0

## [app0.5.0] - 2025-03-12

- c60779c Release app0.5.0 2025-03-12
- edad5ce Specifying the cmake modules for the valgrind and cppcheck targets
- cc7c0e7 Specifying particular test run with ctest
- 2fe49df Introducing the Valgrind target doc for root README.md
- ee75ed3 Introducing the cppcheck doc into root README.md
- 2edc812 Fixing cppcheck target exec doc in the README.md
- 2058fe2 Introducing the Valgrind memory check target
- 37b2e48 Decomposing feature enabling if statements into separate file
- 5f96b82 Integrating the cppcheck code checking tool.
- c6aca03 Incrementing version to 0.5.0

## [app0.4.0] - 2025-03-10

- b15973a Release app0.4.0 2025-03-10
- 6329ab2 Sections reorder
- 40b7fdc Introducing clang-format doc into the root README.md
- 6dc997d Setting default OFF value for the clang-format target
- 4d9d227 Fixing absent cmake-modules search path from root
- 38f0c43 Decomposing root CMakeLists.txt var declares into separate module.
- ce9cd15 Adding the clang-format target
- c3aea63 Applied clang-format code formatter
- 6ec1125 Incrementing version to 0.4.0
- c3511ae Introducing Google-based .clang-format file.

## [app0.3.0] - 2025-03-08

- 7dacafc Release app0.3.0 2025-03-08
- e673166 Removing Doxygen mention from the extensions and it's refine.
- 21599fa Specifying optional packaged in the README.md file
- d301440 Introducing the Doxygen doc install feature with custom html name.
- a46f413 Adding README.md to the Doxygen documentation.
- 5de5b7a Adding description for the app namespace
- 1d60e08 Erasing %Z term for the PROJECT_CONFIGURE_DATE variable value format.
- b9b05ba CMake batch replace to a minimum version downgrade.
- 77d99d5 Making Doxygen output directory customizable
- ff46570 Refining README.md
- b5777ed Introducing the Doxygen subsection in the README.md
- 8665554 Refining some classes comments.
- f53a237 Refining Doxygen target
- 500ccf0 Introducing the Doxygen documentation creation target.
- 37ed418 Refining tests run section in the README.md
- bfd7e38 Fixing README.md type
- e0e7225 Fixing type in the CHANGELOG.md
- dfbf4ac Moving ENABLE_UNIT_TEST check to toplevel app UTs
- 21335bf Introducing a new PROJECT_BINARY_NAME CMake-var and CMake files little reorg
- d1f5ead Incrementing version to a 0.3.0

## [app0.2.0] - 2025-03-07

- 74a55dc Release app0.2.0
- 150537c Fixing annoying -fanalyzer caused prolonged build
- 84d7c95 Fixing flags skipping in the CommandLineParser
- 57f0cef Causing to print help if missing command line parameter data.
- c7714dc A bit of a code formatting
- 72fed6d Newline in the project-global-decls.h.in
- dd6dccc Erasing the INVALID static field from App Factory and reusing one from the IApplication
- f2bd6f6 Introducing correct brief comment for the CommandLineParser class
- 905d423 Introducing return value explanation for an abstract run method
- 01e3f80 Fixing main.cpp comment mistake.
- 8f8bb4c Introducing comment to a IApplication INVALID static field
- 30aead4 Introducing comprehensive help message in the ApplicationHelpPrinter
- 19891ac Introducing sample ApplicationFactory UTs.
- 5401442 Introducing a sample CommandLineParser UTs.
- 5c77ee5 Introducing ApplicationVersionPrinter UTs.
- 848bea1 Adding ApplicationHelpPrinter sample UTs.
- eef8dd4 Adding ApplicationContext UTs.
- ff2adf4 Fixing absent includes for ApplicationContext mock
- 8096646 Fixing double Cpp in the binary name for README.md
- 7de3038 Introducing test run commands to the README.md
- e6a30c6 Enabling system GTest probe by the default
- 5967b0b Mentioning GTEST_TRY_SYSTEM_PROBE in the README.md
- 285b387 Adding GTest system probe code to CMakeLists.txt files.
- eebc595 Disabling the UTs by default.
- 458c11f Specifying command execution dir in README.md
- b749982 Refining README.md
- 487748a Integrating GTest and implementing a simple Application test.
- 1515ece Fixing gtest package requirement
- a46c1ba Fixed ApplicationFactory indentation issue.
- 833bc70 Specifying install commands directory in README.md
- e9b4d47 Adding installation section in the README.md
- a216d70 Adjusting execute_process command indentation.
- f4eb95e Adding binary install command.
- 6ead0f8 Refining set origin section in README.md
- 1cc9166 Introducing new info into the README.md
- a3ca641 Incrementing version to 0.2.0

## [v0.1.0] - 2025-03-04

- feded33 Refining CHANGELOG.md
- eaaee95 0.1.0 release
- 522b6b3 Adding changelog
- 5c75937 Refining the README.md file
- f8df49b Introducing additional info into the root README.md file
- a76890a Decomposing the compile options
- d5da609 Adding some comments.
- 28772c6 Introducing h-configure file for version printer
- b5fceb1 Introducing version printing application ApplicationVersionPrinter
- 6d4b9a0 Adding some comments to parser and applications
- ba2bf07 Introducing and integrating a CommandLineParser.
- 720500f Adding a basic help printer application class.
- 7429e21 Adding if-guards for created app instances.
- e2be348 Adding main application function explanatory comment.
- 8b6f9ef Adding ApplicationFactory class and integrating into main.cpp
- 6bbff32 Adding the default application's class Application
- c0debf2 Adding ApplicationContext and IApplication.
- 5a2fb71 Adding basic CMakeLists.txt files structure.
- f770df2 Adding a basic main.cpp
- 5876319 Adding the initial README.md
- 3f53c17 Adding .gitignore

# Releases

[unreleased](https://github.com/yuriysydor1991/cpp-app-template)

[appMeson0.11.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/appMeson0.11.0)
[appMeson0.10.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/appMeson0.10.0)
[appMeson0.9.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/appMeson0.9.0)
[app0.8.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.8.0)
[app0.7.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.7.0)
[app0.6.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.6.0)
[app0.5.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.5.0)
[app0.4.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.4.0)
[app0.3.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.3.0)
[app0.2.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.2.0)
[v0.1.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/v0.1.0)
