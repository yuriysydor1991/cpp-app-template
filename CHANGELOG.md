# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [appSDBusCxxClient0.12.0] - 2026-11-08

- e216c17 Removing the destination OS from the AppImage package name
- 1c59332 Introducing the STT branches info into the READMEs
- a793616 Replacing the CMAKE_SOURCE_DIR/CMAKE_BINARY_DIR by the PROJECT_SOURCE_DIR/PROJECT_BINARY_DIR
- fd5d4b0 Introducing the appWebAssembly branch info into the READMEs
- ca2b849 Introducing the appLlamaCPP branch info into the READMEs
- dd45687 Introducing the TTS branches info into the READMEs
- 50968bd Introducing the destination OS into the package names
- 5bd6ea1 Fixing the branch name of the cloning commands in the docs
- 6f9176a Synchronizing the template flavors list of the READMEs
- f497511 Documenting the sdbus-c++ source build of the Ubuntu 24.04 packages script
- 2ffdc09 Failing the flavor CI test stages which match no tests
- 42907c0 Converting the flavor link calls of the project binary to the keyword signature
- 4753482 Refreshing the shared library cache after the from-source installs
- 7cea126 Fixing the cppcheck findings of the new signals handler, tests and log mock
- d16ef14 Updating the app component diagram to the signals handlers design
- 8c77a60 Renumbering the custom command line parameters section numbered 4-6 twice
- e0e8117 Documenting the built in command line options and the usage errors
- b71cb75 Testing the application with the real command line arguments
- 93dac5d Parsing the command line before the log file initialization
- 53e86e0 Exiting with a failure status on the command line usage errors
- 24c89b5 Fixing the missing option value raising the version flag instead of the help one
- 73ec479 Fixing the CommandLineParser test assertions which could not fail
- 933176b Fixing the log mock LOG_INIT forwarding into the LOG_INIT_DEFAULTS mock
- c0e5b7e Restoring the previous signal dispositions on the signals handler uninstall
- 1d9d2a7 Leaving the SIGTTIN and SIGTTOU signals to the shell job control
- 67e69b1 Removing the nonexistent module path directories and cppcheck suppression
- 77123c3 Fixing the zlib gzip file example ignoring the read and close errors
- 69a20f6 Fixing the flatpak requirements section naming an outdated SDK version
- 29587af Documenting the ENABLE_COMPONENT_TESTS option of the test builds
- a476006 Listing every linked doc section in the requirements and build index pages
- e1513ce Fixing the documentation links pointing into the other language
- b0fdb19 Fixing the stale file paths named in the documentation
- 38d63c2 Fixing the flatpak target failing on its repeated build
- ea98bdd Fixing the snap command path ignoring the install prefix
- 90e4007 Fixing the documentation install which needed a manual Doxygen-doc build
- ab9e157 Skipping the Doxygen and callgrind targets when their tools are missing
- 6ce8007 Installing the packager tools into the Jenkins pipeline image
- 3451f99 Replacing the libjpeg-turbo download fallback with a clear configure error
- af14ec3 Fixing the libavif download fallback stopping without the system libyuv
- d58cc71 Pinning the third-party download fallbacks to their release tags
- 1aea4ee Failing the CI test stages which match no tests
- 8b427be Fixing the Jenkins doc sections linked check skipping the section directories
- 22cae46 Replacing the broken OpenSSL download fallback with a clear configure error
- 4dde212 Fixing the mixed target_link_libraries signatures on the project binary
- f3faf4f Fixing the MAX_LOG_LEVEL option help text error level value
- 6fccc98 Fixing the logger level filter tests which could not fail
- 215e4a9 Fixing the log macros to expand into single statements
- c85897f Fixing the logger data races on the log file reopening and the level
- c3f394f Fixing the log file open failure aborting the process
- d6ff99c Splitting the CTEST_DefaultLogger helper classes into own files
- 0626b10 Splitting the packages install scripts per OS release
- 86a9f0b Removing the CTEST cases repeating the query handler factory unit tests
- 2024d11 Granting the flatpak and the snap the hostname1 system bus access
- 7051049 Documenting the sdbus-c++ requirements, option and hostname1 call
- 82fbbba Stopping the configure with a clear error when the flavor library is OFF
- b9b44d9 Fixing the cppcheck findings in the branch code
- c525b9d Fixing the stale sdbus-c++ link comments of the component tests CMake
- f89aed2 Skipping the live D-Bus tests on a bus without the hostname1 service
- a40c9bb Keeping the fetched sdbus-c++ files out of the project installation
- 7a013f1 Requiring the sdbus-c++ 2 API the code is written for
- b9b60b5 Moving the Hostname1Properties out of the Hostname1QueryHandler class
- f1705f0 Returning the invalid status instead of asserting on an unreachable D-Bus
- 4b4469d Fixing the malformed GCC diagnostic pragma in the includes header
- af455d4 Synchronizing the CommandLineParser parse doc comment with app
- fb8bad5 Synchronizing the get_stop assertions of the application tests with app
- bc98ee4 Replacing the unreachable GNU gettext site link with its Savannah page
- 844a977 Introducing the destination CPU architecture into the package names
- 45efc55 Introducing the appGettext branch info into the READMEs
- 34343fc Introducing the appDarknetXX branch info into the READMEs
- 8f267ff Introducing the RedHat packages install script
- e93f666 Introducing the appWhisperCPP branch info into the READMEs
- 7168505 Introducing the FreeBSD packages install script
- 9154130 Introducing the appV8 branch info into the READMEs
- 06b8b19 Erasing the build sources and trees of the docker images
- c05321d Introducing the debug clang-format script
- b232b9d Resetting the inherited signals dispositions in the signals handlers tests
- beb8dde Introducing the binary hardening options section into the READMEs
- 55c6506 Introducing the binary hardening compile and link options
- de41bd4 Introducing the GitLab CI/CD pipeline section into the READMEs
- 5d6e77f Introducing the GitLab CI/CD pipeline mirroring the Jenkinsfile
- 8ca7f26 Introducing the GitHub Actions CI pipeline section into the READMEs
- a4bc6af Moving the GitHub Actions CI pipeline to the Ubuntu 26.04 runner with the branch dependencies
- 1cd806a Correcting the appQt6QtDBusClient branch description in the READMEs
- a4e393b Introducing the desktop application packaging switch
- 4150b5a Limiting the documentation checks to the repository own markdown files
- a8593bf Excluding the GCC own include directories from the clang-tidy search path
- 87b75eb Accepting the 405 documentation URLs
- ba68d73 Applying the clang-format to the test sources
- 8de77de Spacing out the branch entries in the READMEs
- df828a5 Rewording the DOCKER_HOST environment requirement in the docker docs
- c90340b Removing the DOCKER_HOST variables from the docker enablers
- adfea27 Excluding the build trees from the Docker build context
- 47219d1 Retrying the unreachable documentation URLs and accepting the 403 ones
- 009caf0 Introducing the --rebuild flag into the Jenkins docker scripts
- 642801c Rebuilding the image from its base on the Jenkins pipeline force rebuild
- 4cdf360 Introducing the audio assets branches info into the READMEs
- 2ad63de Splitting the signals handlers per category and covering the pause, reload, user defined and ignored signals
- 77267f1 Introducing the app signals handlers subcomponent
- 9b62259 Declaring the main function argv parameter as an array
- 75031bf Moving the packagers templates into the per-packager directories
- 150571c Dropping the packagers and the development tools from the packages install list
- b6b1247 The destination CPU architecture of the AppImage package name
- 6d668a0 Picking the CPack AppImage enabler since the CMake 4.2 and dropping the debug banners
- eaf006a Extracting the AppImage enabler pick into its own general enabler
- 145be43 Selecting the AppImage packager enabler by the CMake version
- ee4af3b Introducing the CPack based AppImage packager enabler
- e055261 Introducing the AppImage packager
- cc6268e Introducing the --install flag into the packager build scripts
- 149c70d Renaming the packages install script and adding the Ubuntu one
- df09833 Introducing the target architecture into the flatpak package name
- 49261b1 Introducing the AppStream metainfo file into the flatpak package
- e3f9ef2 Consuming the install directory variables the flatpak-builder passes
- 7a24138 Introducing the required packages install script
- 914951e Installing the flatpak build dependencies from the flathub remote
- 50ca96e Dropping the redundant build step from the packager scripts
- db06040 Introducing the per packager build scripts
- 17f3473 Introducing the appCFITSIO branch info into the READMEs
- 8e04508 Make the compile time log level gate really gate
- 378316a Introducing the appGtkmm4Libadwaita branch info into the READMEs
- 5abb92b Pinning the log message stream to the classic locale
- 5267c0c Decomposing the IApplication descendants into the applications subcomponent
- 3cf584b Introducing the appFontAwesome branch info into the READMEs
- 7a32fa5 Introducing the sdbus-c++ includes wrapper to silence its headers warnings
- 3647ba7 Introducing the debug test script and its --test parameter
- 0d11e5d Incrementing version to appSDBusCxxClient0.12.0
- 00604f2 Release appSDBusCxxClient0.11.0 at 2026-08-17

## [appSDBusCxxClient0.11.0] - 2026-08-17

- 7c9037a Introducing the InsertNewlineAtEOF clang-format option
- be25e80 Introducing the appCURLChatGPT branch info into the READMEs
- 65edda0 Hiding the ApplicationContext fields and adding the atomic stop flag
- 7c49263 Moving the linker hardening options out of the compile options
- 15ec542 Split the DefaultLogger into a static proxy and a real logger instance
- 9657994 Introducing the appCURLClaude branch info into the READMEs
- 9c07bba Introducing the external documentation URLs check into the Jenkins pipeline
- 7b593cc Correcting the docker modules path of the documentation
- 672f71d Introducing the quick build and the docker starter scripts
- 7749b32 Introducing the quick build and the docker starter scripts
- 30e698e Making the docker containers run under unprivileged users
- cf02c24 Formatting the sources with the clang-format
- 0cbe604 Repairing the pipeline code check stages
- ed7e3c1 Introducing the appPGPLOT branch info into the READMEs
- 6171ea3 Fixing the Jenkinsfile
- 2fc3a13 Fix broken cppcheck link in section 5 index
- 1fcad8f Fix Groovy escape sequences in markdown link checker stage
- 0789030 Rework markdown link checker stage to pure bash
- 24512db Add Jenkinsfile stage to detect broken markdown links; fix pre-existing broken links
- 5395a54 Reorganize doc/sections into section dirs with category grouping
- 5aadcc4 Add an OpenSSL cmake enabler module with SHA-256, HMAC-SHA256 and HTTPS/TLS client code samples
- 69de348 Group the enabler documentation under subsections in the READMEs
- 0966bef Group the compression branches under a dedicated README section
- e348c6d Fix the misc/Jenkinsfile checkout branch to the appSDBusCxxClient branch name
- 876fa9f Introducing the appLZMA branch info into the READMEs
- 7140805 Add a liblzma (XZ Utils) compression library enabler module
- e5193ad Introducing the appZlib branch info into the READMEs
- 4d99535 Add zlib compression usage examples to its enabler documentation
- 353c82c Replace the redundant PROJECT_NAME CMake variable with CMAKE_PROJECT_NAME
- 9cfd0b5 Introducing the appGtkmm4Vulkan branch info into the READMEs
- cd914c4 Removing the appGtkmm4Vulkan branch info from the READMEs
- ad674ae Introducing the appQt6Vulkan and appGtkmm4Vulkan branches info into the READMEs
- 1ef5ae8 Simplifying root CMakeLists.txt
- 3393149 Introducing the appFirebird branch info into the READMEs
- f56f9fc Introducing the appGtkmm4GDBusClient branch info into the READMEs
- 9735280 Introducing the appQt6GLArea branch info into the READMEs
- b7bd7d8 Introducing the appGtkmm4GLArea branch info into the READMEs
- debb2c5 Splitting the Data Visualization README category into Plots/Graphs and Maps
- 47de793 Introducing the applibMeson branch info into the READMEs
- db18345 Introducing the zlib and image format cmake enablers with docs
- 6db4c29 Introducing the appSFML branch info into the READMEs
- 4391160 Introducing the appwxWidgets branch info into the READMEs
- 9cd6bfb Introducing the appQt6QtDBusClient branch info into the READMEs
- aa2d7ea Introducing the appQt6QtLocation branch info into the READMEs
- 99cbf84 Introducing the appQt6ChartView branch into the READMEs
- 4959cc6 Introducing the appGtkmm4LeafLet and appQt6LeafLet branches info into the READMEs
- 17a969e Introducing the COMPONENTS arg for template_project_default_3rdparty_enabler
- d4ab288 Registering missing tests in the Jenkinsfile
- a3918a2 Removing the SDL3 current marking
- 5983e4a Introducing information about the SDL3 branch in the READMEs
- db9a280 Replacing faulty SimpleLogger mention with the DefaultLogger
- b5f06c1 Rename the simple logger to DefaultLogger and add top-level log.h tests
- 77f7429 Removing faulty simple_logger mention in the log.h
- 5285df5 Add template-specific packager, documentation and registration checks
- a564049 Refining sdbus-c++ cmake enabler module and dependent targets
- cef7d07 Move test mocks to the general-mock style and mock sdbus-c++ in unit tests
- 6f87b17 Introducing the SDBusCxxController unit and component tests
- dca580b Introducing the SDBusCxxController GMock mock for the app tests
- c07391a Declaring the sdbus-c++ flatpak source module before the project one
- 0d6b786 Marcking appSDBusCxxClient as a current branch
- 07855a9 Introducing the appSDBusCxxClient and appSDBusCxxServer branches info into the READMEs
- a26c43f Moving Dockerfiles and packagers files into separate subdirs in the misc
- f4e645e Including missing enabler into post enabler
- 5e89fe1 Adding .claude dir to .gitignore
- 2ef2fb8 Implementing basic libsdbusc++ integration with simple example.
- 422ca40 Introducing the GitHub Actions CI pipeline mirroring the Jenkinsfile
- 1505bb3 Introducing project structure section Будь ласка, зверніться до адміністратора subsection
- bd89e4d Introducing the libMeson branch info into the READMEs
- 6e8584a Introducing info about newly created branch appOpenCV into READMEs with it's cmake enabler.
- cfa55af Introducing the CPack's RPM package generator integration
- 860c012 Removing unmerged lines in the doc/README.uk_UA.md
- 0cb37b3 Introducing the MS Windows WIX package generation through CPack integration
- 16bff16 Introducing the project's FreeBSD pkg package generation support through CPack. Works only on FreeBSD.
- cdad20f Deleting REQUIRED marking from the snapcraft's find_program
- e42f7a3 By default disabling the snap package manager
- cede1e2 Introducing the snap packager integration with documentation
- 5c2fa86 Introducing and migrating to the template_project_default_3rdparty_enabler cmake function. Making enablers git sources variables modifiable.
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

[appSDBusCxxClient0.12.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/appSDBusCxxClient0.12.0)
[appSDBusCxxClient0.11.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/appSDBusCxxClient0.11.0)
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
