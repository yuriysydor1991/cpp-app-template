# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [appPlotGenCpp0.11.0] - 2026-11-08

- 85d0f0a Removing the destination OS from the AppImage package name
- c55d430 Introducing the STT branches info into the READMEs
- 74a953b Replacing the CMAKE_SOURCE_DIR/CMAKE_BINARY_DIR by the PROJECT_SOURCE_DIR/PROJECT_BINARY_DIR
- 822c96f Introducing the appWebAssembly branch info into the READMEs
- fefbc09 Introducing the appLlamaCPP branch info into the READMEs
- a0f1694 Introducing the TTS branches info into the READMEs
- 16abf6c Introducing the destination OS into the package names
- a129298 Fixing the branch name of the cloning commands in the docs
- 58768dd Synchronizing the template flavors list of the READMEs
- 1a404c9 Converting the flavor link calls of the project binary to the keyword signature
- e83d51b Documenting the SFML 2 source build of the Ubuntu 26.04 packages script
- f1dddb6 Refreshing the shared library cache after the from-source installs
- 268f9c6 Fixing the cppcheck findings of the new signals handler, tests and log mock
- 77eee00 Updating the app component diagram to the signals handlers design
- d7813c2 Renumbering the custom command line parameters section numbered 4-6 twice
- 011882b Documenting the built in command line options and the usage errors
- 71d4e27 Testing the application with the real command line arguments
- c14a7e6 Parsing the command line before the log file initialization
- 4a36d83 Exiting with a failure status on the command line usage errors
- 41ad205 Fixing the missing option value raising the version flag instead of the help one
- ca3e292 Fixing the CommandLineParser test assertions which could not fail
- f11ea41 Fixing the log mock LOG_INIT forwarding into the LOG_INIT_DEFAULTS mock
- ce5af96 Restoring the previous signal dispositions on the signals handler uninstall
- 5d08aca Leaving the SIGTTIN and SIGTTOU signals to the shell job control
- 5b8a648 Removing the nonexistent module path directories and cppcheck suppression
- d7fb1c0 Fixing the zlib gzip file example ignoring the read and close errors
- 0d942d3 Fixing the flatpak requirements section naming an outdated SDK version
- f2c3599 Documenting the ENABLE_COMPONENT_TESTS option of the test builds
- 0a3acf5 Listing every linked doc section in the requirements and build index pages
- 29ce06b Fixing the documentation links pointing into the other language
- 422317e Fixing the stale file paths named in the documentation
- 94f152e Fixing the flatpak target failing on its repeated build
- 9d3cba0 Fixing the snap command path ignoring the install prefix
- 1ffd1f1 Fixing the documentation install which needed a manual Doxygen-doc build
- edaff41 Skipping the Doxygen and callgrind targets when their tools are missing
- 30c39f7 Installing the packager tools into the Jenkins pipeline image
- 7b2d3c1 Replacing the libjpeg-turbo download fallback with a clear configure error
- b6d3a6c Fixing the libavif download fallback stopping without the system libyuv
- a2169db Pinning the third-party download fallbacks to their release tags
- 9b70d7e Failing the CI test stages which match no tests
- 5e41b5d Fixing the Jenkins doc sections linked check skipping the section directories
- 1a05cea Replacing the broken OpenSSL download fallback with a clear configure error
- ff86987 Fixing the mixed target_link_libraries signatures on the project binary
- 9af7c07 Fixing the MAX_LOG_LEVEL option help text error level value
- 35808b3 Fixing the logger level filter tests which could not fail
- f18a3dd Fixing the log macros to expand into single statements
- 5780e2a Fixing the logger data races on the log file reopening and the level
- 9cede8c Fixing the log file open failure aborting the process
- 18af5e7 Splitting the CTEST_DefaultLogger helper classes into own files
- 01b5735 Splitting the packages install scripts per OS release
- 2c4aac7 Fixing the cppcheck target findings of the PlotGenCpp controller and mock
- ee02545 Synchronizing the get_stop assertions and the CommandLineParser doc comment with app
- 5ecda63 Documenting the PlotGenCpp and SFML enablers
- d9d4c29 Stopping the configure with a clear message when PlotGenCpp or SFML is disabled
- 2c56260 Skipping the system SFML 3 that aborts the configure
- 0b33508 Introducing the VERSION argument into the 3rd party enabler function
- 785539d Removing the redundant log mock of the plotgencpp tests
- a3b96e5 Fixing the PlotGenCppController header guard, size comment and includes
- 740a7c8 Fixing the installed binary not finding the PlotGenCpp and SFML libraries
- 10fbdc1 Renaming the MatPlotCpp enabler into the PlotGenCpp one
- 9ca8813 Replacing the unreachable GNU gettext site link with its Savannah page
- abd1290 Introducing the destination CPU architecture into the package names
- 26d8346 Introducing the appGettext branch info into the READMEs
- 667a918 Introducing the appDarknetXX branch info into the READMEs
- a17174e Introducing the RedHat packages install script
- 5d47e3a Introducing the appWhisperCPP branch info into the READMEs
- be902ef Introducing the FreeBSD packages install script
- 8349b4a Introducing the appV8 branch info into the READMEs
- ab0e0d2 Erasing the build sources and trees of the docker images
- 6a16dae Introducing the debug clang-format script
- 1d7c43f Resetting the inherited signals dispositions in the signals handlers tests
- 3a3f057 Introducing the binary hardening options section into the READMEs
- a3259b4 Introducing the binary hardening compile and link options
- 179f1ab Introducing the GitLab CI/CD pipeline section into the READMEs
- e2b480c Introducing the GitLab CI/CD pipeline mirroring the Jenkinsfile
- 66a2cbb Introducing the GitHub Actions CI pipeline section into the READMEs
- 20636b2 Introducing the GitHub Actions CI pipeline mirroring the Jenkinsfile
- 2fb1e1a Excluding the fetched SFML and PlotGenCpp code from the clang-tidy checks
- 92e44d5 Skipping the pkg-config files install of the fetched SFML
- 1d4135e Correcting the appQt6QtDBusClient branch description in the READMEs
- 0161be8 Introducing the desktop application packaging switch
- 2390243 Limiting the documentation checks to the repository own markdown files
- e8a2ed4 Excluding the GCC own include directories from the clang-tidy search path
- 25462b7 Accepting the 405 documentation URLs
- c469ddf Spacing out the branch entries in the READMEs
- 27cfb70 Rewording the DOCKER_HOST environment requirement in the docker docs
- e0f67db Removing the DOCKER_HOST variables from the docker enablers
- 0e8e5db Excluding the build trees from the Docker build context
- d1d31ba Retrying the unreachable documentation URLs and accepting the 403 ones
- 380b0b3 Introducing the --rebuild flag into the Jenkins docker scripts
- 247f32f Rebuilding the image from its base on the Jenkins pipeline force rebuild
- 1c48eaa Introducing the audio assets branches info into the READMEs
- 282ee19 Splitting the signals handlers per category and covering the pause, reload, user defined and ignored signals
- dfd7bf1 Introducing the app signals handlers subcomponent
- f183526 Declaring the main function argv parameter as an array
- d54c455 Moving the packagers templates into the per-packager directories
- ec5dd7a Dropping the packagers and the development tools from the packages install list
- d0b2aa8 The destination CPU architecture of the AppImage package name
- 180f815 Picking the CPack AppImage enabler since the CMake 4.2 and dropping the debug banners
- 91b1894 Extracting the AppImage enabler pick into its own general enabler
- 6a14284 Selecting the AppImage packager enabler by the CMake version
- d551339 Introducing the CPack based AppImage packager enabler
- 44058f8 Introducing the AppImage packager
- 53ebb97 Introducing the --install flag into the packager build scripts
- aa2dcb7 Renaming the packages install script and adding the Ubuntu one
- 1164220 Introducing the target architecture into the flatpak package name
- bf199ac Introducing the AppStream metainfo file into the flatpak package
- 5362686 Consuming the install directory variables the flatpak-builder passes
- d6e7758 Fixing the flatpak PlotGenCpp module missing cstdint include
- 75bd2b8 Fixing the SFML and PlotGenCpp FetchContent fallback build
- 6a740f9 Introducing the required packages install script
- d39c7f1 Installing the flatpak build dependencies from the flathub remote
- 2345e12 Dropping the redundant build step from the packager scripts
- 4bcb1b4 Introducing the per packager build scripts
- 86980f3 Introducing the appCFITSIO branch info into the READMEs
- 27a96f5 Make the compile time log level gate really gate
- 98d5cd3 Introducing the appGtkmm4Libadwaita branch info into the READMEs
- d9637ce Pinning the log message stream to the classic locale
- b76eaad Decomposing the IApplication descendants into the applications subcomponent
- d566cd0 Introducing the appFontAwesome branch info into the READMEs
- 79a70ec Introducing the debug test script and its --test parameter
- a3667f0 Introducing the InsertNewlineAtEOF clang-format option
- 27c224d Removing the trailing empty lines at the end of the project files
- 101028e Adding the missing newlines at the end of the project files
- ef1885a Removing the trailing whitespaces from the project files
- a3175ff Introducing the appCURLChatGPT branch info into the READMEs
- a8490c4 Hiding the ApplicationContext fields and adding the atomic stop flag
- 6948603 Moving the linker hardening options out of the compile options
- de05afc Fixing the SFML fallback clone tag and the PlotGenCpp Dockerfile commands
- 102103f Split the DefaultLogger into a static proxy and a real logger instance
- a10935a Introducing the appCURLClaude branch info into the READMEs
- 4395938 Introducing the external documentation URLs check into the Jenkins pipeline
- 6567cfb Correcting the docker modules path of the documentation
- 889e126 Introducing the quick build and the docker starter scripts
- 75ee682 Introducing the quick build and the docker starter scripts
- 49eca31 Making the docker containers run under unprivileged users
- 23e0f8e Formatting the sources with the clang-format
- 27058c2 Repairing the pipeline code check stages
- 9c2a726 Introducing the appPGPLOT branch info into the READMEs
- bbfb7e0 Fixing the Jenkinsfile
- 3b708ce Fix broken cppcheck link in section 5 index
- 6df5a5d Fix Groovy escape sequences in markdown link checker stage
- f5dfe31 Rework markdown link checker stage to pure bash
- 61ef108 Add Jenkinsfile stage to detect broken markdown links; fix pre-existing broken links
- 47a4312 Reorganize doc/sections into section dirs with category grouping
- f15988c Add an OpenSSL cmake enabler module with SHA-256, HMAC-SHA256 and HTTPS/TLS client code samples
- f38f335 Group the enabler documentation under subsections in the READMEs
- 4ce30c3 Group the compression branches under a dedicated README section
- 2b0773b Fix the misc/Jenkinsfile checkout branch to the appPlotGenCpp branch name
- 269b0df Introducing the appLZMA branch info into the READMEs
- 126e616 Add a liblzma (XZ Utils) compression library enabler module
- e0e7bef Introducing the appZlib branch info into the READMEs
- f5fddea Add zlib compression usage examples to its enabler documentation
- e4413bf Replace the redundant PROJECT_NAME CMake variable with CMAKE_PROJECT_NAME
- 7b3df09 Introducing the appGtkmm4Vulkan branch info into the READMEs
- 5df76b7 Removing the appGtkmm4Vulkan branch info from the READMEs
- f39c6a0 Introducing the appQt6Vulkan and appGtkmm4Vulkan branches info into the READMEs
- f61c7ce Simplifying root CMakeLists.txt
- 2ad9dc9 Introducing the appFirebird branch info into the READMEs
- 22988d1 Introducing the appGtkmm4GDBusClient branch info into the READMEs
- da9e39f Introducing the appQt6GLArea branch info into the READMEs
- eb46f43 Introducing the appGtkmm4GLArea branch info into the READMEs
- 888d7ec Splitting the Data Visualization README category into Plots/Graphs and Maps
- 3962190 Introducing the applibMeson branch info into the READMEs
- a8e201d Introducing the zlib and image format cmake enablers with docs
- 032b662 Introducing the appSFML branch info into the READMEs
- 908c937 Introducing the appwxWidgets branch info into the READMEs
- 85d71f6 Introducing the appQt6QtDBusClient branch info into the READMEs
- 965cfba Introducing the appQt6QtLocation branch info into the READMEs
- e2f5314 Introducing the appQt6ChartView branch into the READMEs
- 2e82afa Introducing the appGtkmm4LeafLet and appQt6LeafLet branches info into the READMEs
- a0c13a8 Fixing SFML repo link
- 11a06ba Introducing the PlotGenCppController mock and the plotgencpp tests
- c0a1d02 Introducing the components for the SFML library enabler
- 0f08b5c Introducing the COMPONENTS arg for template_project_default_3rdparty_enabler
- 9be6fa5 Migrating PlotGen and SFML to template_project_default_3rdparty_enabler
- ca49be6 Migrating to template_project_default_3rdparty_enabler
- f0cd33f Removing the SDL3 current marking
- 196aa14 Introducing information about the SDL3 branch in the READMEs
- a76e6a4 Replacing faulty SimpleLogger mention with the DefaultLogger
- f01e4d3 Rename the simple logger to DefaultLogger and add top-level log.h tests
- 3c115e1 Removing faulty simple_logger mention in the log.h
- 4236fe6 Add template-specific packager, documentation and registration checks
- 84181ea Introducing the appSDBusCxxClient and appSDBusCxxServer branches info into the READMEs
- 07e2dfc Moving Dockerfiles and packagers files into separate subdirs in the misc
- 32a8b29 Adding .claude dir to .gitignore
- a328614 Introducing project structure section Будь ласка, зверніться до адміністратора subsection
- bbb010f Introducing the libMeson branch info into the READMEs
- 107bc32 Introducing info about newly created branch appOpenCV into READMEs with it's cmake enabler.
- 1ccc614 Introducing the CPack's RPM package generator integration
- b6611c6 Removing unmerged lines in the doc/README.uk_UA.md
- 51b13ba Introducing the MS Windows WIX package generation through CPack integration
- b5b4aad Introducing the project's FreeBSD pkg package generation support through CPack. Works only on FreeBSD.
- 1f3f133 Deleting REQUIRED marking from the snapcraft's find_program
- 3d6e669 By default disabling the snap package manager
- 0ac33b9 Introducing the snap packager integration with documentation
- d7a2ce8 Introducing and migrating to the template_project_default_3rdparty_enabler cmake function. Making enablers git sources variables modifiable.
- d7ab3e2 Integrating and implementing the basic PlotGenCpp library example
- f28c334 Moving all CMake variables declarations into their respectful enablers.
- ace9351 Moving Doxygen related CMake variables into doc/CMakeLists.txt file
- 0d38e5b Introducing the libxml2 enabler cmake module
- 0d8c898 Enhancing the cmake files fs structure
- 3ec8d38 Making docker base image configurable through CMake variables
- 43763b8 Introducing the appPLplot branch info into the READMEs
- 938e0a1 Introducing the MatPlot++ appMatPlotxx branch into the READMEs
- a7bbedd Fixing clang-tidy conf misspell
- 80d533c Switching off the clang-tydy's unrecognizable AnalyzeTemporaryDtors config param
- 052cebf Making the cppcheck stage optional due to unstable results
- f849981 Supressing the cppcheck's missingIncludeSystem and unusedStructMember warnings.
- 9eb94c6 Loggging README's misspell refine
- accda7f Missing newlines in the READMEs
- ab6f8b1 Grouping and categorising available template flavors links in the READMEs
- 9aa88c6 Renaming properly Nlohmann JSON library CMake enabler file
- c6c323d Introducing the forgottent Nlohmann JSON library enabler info into the READMEs
- c958ff8 Refining branch name in the READMEs project cloning commands.
- d6bc1a8 Decomposing READMEs
- 893a961 Introducing the ENABLE_LOGS_MICROSECONDS_TIME CMake option in order to be able to disable microseconds in the log messages.
- 1cefe87 Introducing the --branch cmd line flag for git clone command in the READMEs
- 2e81c79 Introducing explicit template altering notice in the READMEs headers
- 07c06d3 Optimizing some CMake commands in the README.md
- 83d424b Introducing the appGtkmm4 branch info into the READMEs
- f819f25 Introducing the PlantUML app component diagram into the READMEs
- ccac56a Enabling GTest during for CTs
- 8d7481c Pointing Jenkins configurable port into standart in-container 8080
- 385398a Making the Jenkins pipeline container and image names configurable
- 7c1ee70 Including lost SimpleLogger CTs
- e209c5b Introducing basic app CTs samples
- 86d9278 Introducing basic SimpleLogger CTs with CMake and Jenkins integration
- 7ab160b Refining the branches link in the READMEs, introducing gitlab links also
- eb731ef Specifying the Jenkins container run target in the READMEs
- e6e6e61 Erasing redundant project copy for Jenkins pipeline docker, renaming jenkins CMake file
- 1b1ddc2 Refining clang-format stage
- 3c652ba Introducing the release install try Jenkins pipeline stage
- c4f0c77 Erasing redundant clang-tidy enable from tests pipeline stages
- 9bf1c0d Splitting debug tests and cppcheck from clang-tidy build
- 3b6a5f0 Introducing the Jenkins pipeline docker force rebuild option
- 98ce4a0 Returning a Jenkins Docker file configure, erasing redundant Jenkinsfile configuration
- 6ac3d4f Refining Jenkins pipeline target
- 836d98d Introducing basic Jenkins pipeline CMake target and Jenkinsfile conf
- 51fe32f Incrementing version to 0.11.0
- bd88653 Release app0.10.0 at 2025-09-08

## [app0.10.0] - 2025-09-08

- 5e10927 Fixing typo in the README.md
- 0da5064 Introducing the valgrind callgrind profiler target for the project
- d3ba131 Introducing the gprof profiling target
- fbdfd47 Adding money emoji to donation notice in the READMEs
- 5dcb1f1 Introducing the appCURL branch info into the READMEs
- 7e33a20 Introducing the enabling libcurl section into the READMEs
- 147234a Introducing the libcurl cmake enabler script
- e1ac2ac Moving the DEFAULT_LOG_FILE_PATH macro declaration into severity-macro-consts.h
- 1fc850b Refining unit tests to match the new log code
- f064fde Introducing a custom log file cmd param for the executable
- f6b7215 Introducing the DEFAULT_LOG_FILE_PATH cmake var and cpp macro to specify default dst log file location
- 71a0a63 Introducing the CMDParamNames class to encapsulate CMD params names
- 6b9081b Introducing some marketing sentences in the README's goal section
- dac69a9 Introducing the cmake/enablers subdirectory to locate the 3rd-party dependencies
- 681f38d Renaming emplate-project-make-GTest-available - template-project-GTest-enabler
- 32b00b0 Introducing the NLohmann JSON library enabler cmake module
- 7d49b4b Fixing the sanitizers cmake file in the READMEs
- b1a8c17 Avoiding unnecessary badly portable localtime_r usage
- b614baa Introducing the thread id into simple logger
- 97479eb Avoiding backward time in the simple logs
- 1247fd5 Avoiding final log multiple str fetches
- 114b6c2 Refining the log current timestamp method, increasing thread safety
- a9ac8d5 Introducing the CMake configurable log severity messages compilation switch
- 298e520 Introducing the appBoostLog branch info into the READMEs
- 36b5486 Hiding the compile options cmake files under separate directory
- a5db6a0 Enhancing sanitizers combinations and new cmake dir for ones
- 7584764 Refined issues in the Docker READMEs doc
- 16f294d Introducing the sanitizers enabling info into the READMEs
- 5dc066f Removing redundant cmake traces messages
- 4025b46 Introducing the GCC compiler sanitizers
- 5c3b37b Inserting release 0.9.0 to releases lists in CHANGELOG.md
- 65b051d Incrementing version to 0.10.0

## [app0.9.0] - 2025-03-20

- 8f5fc89 Release 0.9.0 2025-06-06
- cb89b27 Erasing redundant suppression that causes cppcheck to fail
- ea1edbd Separating the Docker single container build and run targets
- b861a6a Erasing UTs build and ctest call inside the Dockerfile
- edc8eae Introducing the Docker single run container target.
- 0579df0 Adding project neatness to the READMEs
- 269534d Introducing the appLog4Cpp5 branch info into the READMEs
- d61ded5 Implementing the logging macros and a simple logger to perform log messaging
- 2877c54 Introducing the appMongoDBCpp4 branch info into the READMEs
- 5552fb9 Making the flatpak source json conf file configurable during cmake conf stage
- aee1900 Refining the deb cmake info for cpack
- f4d0708 Introducing the appSQLiteCpp3 branch info into the READMEs
- 5bd9fbf Refining the ApplicationContext mock
- d4d25cb Introducing the gitlab mirror into the READMEs
- 27154f8 Introducing the appMySQLCppConn branch info into the READMEs
- 05dd8ff Introducing the donation notice into the READMEs
- 8e577ce Introducing the appBoostBeast branch info into the READMEs
- 7ec125a Explicitly specifying the combining of the template branches
- c793831 introducing the appPgSQLxx branch into the READMEs
- 59a3f26 Introducing a new appWt4 branch info into the READMEs
- ae60d2a Introducing the error exit code for a cppcheck target
- 38256c1 Refinining the cppcheck target
- 9bf6620 Introducing the appMeson branch info into the READMEs
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

[appPlotGenCpp0.11.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/appPlotGenCpp0.11.0)
[app0.10.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.10.0)
[app0.9.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.9.0)
[app0.8.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.8.0)
[app0.7.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.7.0)
[app0.6.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.6.0)
[app0.5.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.5.0)
[app0.4.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.4.0)
[app0.3.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.3.0)
[app0.2.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.2.0)
[v0.1.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/v0.1.0)
