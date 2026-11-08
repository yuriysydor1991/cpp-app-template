# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [appPLplot0.12.0] - 2026-11-08

- e1f8daf Removing the destination OS from the AppImage package name
- 492631e Introducing the STT branches info into the READMEs
- e598d2b Replacing the CMAKE_SOURCE_DIR/CMAKE_BINARY_DIR by the PROJECT_SOURCE_DIR/PROJECT_BINARY_DIR
- 20b04b7 Introducing the appWebAssembly branch info into the READMEs
- a81cf57 Introducing the appLlamaCPP branch info into the READMEs
- ef62432 Introducing the TTS branches info into the READMEs
- 4fe3577 Introducing the destination OS into the package names
- 329df0d Fixing the branch name of the cloning commands in the docs
- ea9ce67 Synchronizing the template flavors list of the READMEs
- 95e5f2b Including the log header which the merged CTEST_app uses
- 8ea3cb0 Failing the flavor CI test stages which match no tests
- 515c138 Converting the flavor link calls of the project binary to the keyword signature
- ed72f51 Refreshing the shared library cache after the from-source installs
- 4037953 Fixing the cppcheck findings of the new signals handler, tests and log mock
- 5b02d78 Updating the app component diagram to the signals handlers design
- 2191846 Renumbering the custom command line parameters section numbered 4-6 twice
- 7a4cb9f Documenting the built in command line options and the usage errors
- 0ef7434 Testing the application with the real command line arguments
- d8a159c Parsing the command line before the log file initialization
- a66134d Exiting with a failure status on the command line usage errors
- 23459fa Fixing the missing option value raising the version flag instead of the help one
- 41cd220 Fixing the CommandLineParser test assertions which could not fail
- 00829ac Fixing the log mock LOG_INIT forwarding into the LOG_INIT_DEFAULTS mock
- a64789a Restoring the previous signal dispositions on the signals handler uninstall
- 8bf8fa7 Leaving the SIGTTIN and SIGTTOU signals to the shell job control
- 60c55da Removing the nonexistent module path directories and cppcheck suppression
- ceff4bc Fixing the zlib gzip file example ignoring the read and close errors
- 4194cc7 Fixing the flatpak requirements section naming an outdated SDK version
- b54eee4 Documenting the ENABLE_COMPONENT_TESTS option of the test builds
- f4f53d2 Listing every linked doc section in the requirements and build index pages
- 9dca860 Fixing the documentation links pointing into the other language
- c6c841d Fixing the stale file paths named in the documentation
- afe6c73 Fixing the flatpak target failing on its repeated build
- f16dc77 Fixing the snap command path ignoring the install prefix
- dc7dcd7 Fixing the documentation install which needed a manual Doxygen-doc build
- 7aad1e0 Skipping the Doxygen and callgrind targets when their tools are missing
- 63785f8 Installing the packager tools into the Jenkins pipeline image
- 7825485 Replacing the libjpeg-turbo download fallback with a clear configure error
- 94c32b9 Fixing the libavif download fallback stopping without the system libyuv
- 45cf58a Pinning the third-party download fallbacks to their release tags
- 91f374b Failing the CI test stages which match no tests
- c870780 Fixing the Jenkins doc sections linked check skipping the section directories
- 1cbec68 Replacing the broken OpenSSL download fallback with a clear configure error
- ed3e58d Fixing the mixed target_link_libraries signatures on the project binary
- 913abcd Fixing the MAX_LOG_LEVEL option help text error level value
- 77f1321 Fixing the logger level filter tests which could not fail
- 1468c1c Fixing the log macros to expand into single statements
- 0a4b9d6 Fixing the logger data races on the log file reopening and the level
- 48e4aac Fixing the log file open failure aborting the process
- bb318a8 Splitting the CTEST_DefaultLogger helper classes into own files
- ef3258c Splitting the packages install scripts per OS release
- 592fbe4 Fixing the sign conversion of the PLplot installed devices listing
- 673fa5a Applying the clang-format to the PLplot device picking
- 9ee5f7d Declaring the runtime dependencies of the DEB package
- e402909 Failing the configuration clearly when the branch library is turned off
- 3504249 Installing a PLplot device driver along with the library
- 8b81096 Pinning the PLplot sources to a reviewed master commit
- 5ae6fae Fixing the logarithmic Y axis of the PLplot example plot
- 88417dd Picking an installed interactive PLplot device instead of the qtwidget one
- c739ab6 Synchronizing the stop flag test assertions and the CommandLineParser doc comment with app
- 6e4ec5b Removing the duplicate PLplot entry from the en requirements index
- fb85c0c Renumbering the branch requirements section after the app ones
- a329431 Replacing the unreachable GNU gettext site link with its Savannah page
- 255c33f Introducing the destination CPU architecture into the package names
- f0e6061 Introducing the appGettext branch info into the READMEs
- 34a3b5e Introducing the appDarknetXX branch info into the READMEs
- 6c16e38 Introducing the RedHat packages install script
- 276577a Introducing the appWhisperCPP branch info into the READMEs
- f55a118 Introducing the FreeBSD packages install script
- 4fe6ae3 Introducing the appV8 branch info into the READMEs
- c1a2892 Erasing the build sources and trees of the docker images
- 48c548c Introducing the debug clang-format script
- c205322 Resetting the inherited signals dispositions in the signals handlers tests
- 833e5db Introducing the binary hardening options section into the READMEs
- bcdcaa1 Introducing the binary hardening compile and link options
- d4d6762 Introducing the GitLab CI/CD pipeline section into the READMEs
- 792c5d5 Introducing the GitLab CI/CD pipeline mirroring the Jenkinsfile
- 0e82502 Introducing the GitHub Actions CI pipeline section into the READMEs
- a07dbc6 Introducing the GitHub Actions CI pipeline mirroring the Jenkinsfile
- 956a1c8 Correcting the appQt6QtDBusClient branch description in the READMEs
- 184dcf1 Introducing the desktop application packaging switch
- ef5cda8 Limiting the documentation checks to the repository own markdown files
- 189d885 Excluding the GCC own include directories from the clang-tidy search path
- 3fef3c5 Accepting the 405 documentation URLs
- a914fc4 Spacing out the branch entries in the READMEs
- c3331c2 Rewording the DOCKER_HOST environment requirement in the docker docs
- 3519b8e Removing the DOCKER_HOST variables from the docker enablers
- bbf5af3 Excluding the build trees from the Docker build context
- 6cc41a1 Retrying the unreachable documentation URLs and accepting the 403 ones
- 158ac2b Introducing the --rebuild flag into the Jenkins docker scripts
- 4f3ac2c Rebuilding the image from its base on the Jenkins pipeline force rebuild
- c4c39ac Introducing the audio assets branches info into the READMEs
- d9943a7 Splitting the signals handlers per category and covering the pause, reload, user defined and ignored signals
- 69c5356 Introducing the app signals handlers subcomponent
- ec3a1b2 Declaring the main function argv parameter as an array
- ac10665 Moving the packagers templates into the per-packager directories
- 7a05fc8 Dropping the packagers and the development tools from the packages install list
- 47b9b4a The destination CPU architecture of the AppImage package name
- 97946e8 Picking the CPack AppImage enabler since the CMake 4.2 and dropping the debug banners
- 51d4350 Extracting the AppImage enabler pick into its own general enabler
- de2f832 Selecting the AppImage packager enabler by the CMake version
- bae2696 Introducing the CPack based AppImage packager enabler
- 1a7f002 Introducing the AppImage packager
- 85c6996 Introducing the --install flag into the packager build scripts
- 0ba585d Renaming the packages install script and adding the Ubuntu one
- 2adc6ed Introducing the target architecture into the flatpak package name
- a881641 Keeping the find_package flags out of the PLplot search
- 04c19f3 Introducing the AppStream metainfo file into the flatpak package
- 7603296 Consuming the install directory variables the flatpak-builder passes
- e6545b6 Switching the flatpak packager to the KDE 5.15-25.08 runtime
- 396a29f Introducing the standalone 3rdparty build for the PLplot
- f5a9158 Introducing the required packages install script
- 46cf8b6 Installing the flatpak build dependencies from the flathub remote
- 92edff8 Dropping the redundant build step from the packager scripts
- 5b0dc81 Introducing the per packager build scripts
- afada64 Introducing the appCFITSIO branch info into the READMEs
- 8b8099b Make the compile time log level gate really gate
- c502881 Introducing the appGtkmm4Libadwaita branch info into the READMEs
- 511b66e Pinning the log message stream to the classic locale
- def6490 Decomposing the IApplication descendants into the applications subcomponent
- 28ff32f Introducing the appFontAwesome branch info into the READMEs
- 2960bec Introducing the debug test script and its --test parameter
- d5a2b3e Incrementing version to appPLplot0.12.0
- c89f374 Release appPLplot0.11.0 at 2026-08-17

## [appPLplot0.11.0] - 2026-08-17

- 1496498 Introducing the InsertNewlineAtEOF clang-format option
- 1f1c117 Introducing the appCURLChatGPT branch info into the READMEs
- 3336971 Hiding the ApplicationContext fields and adding the atomic stop flag
- f206a45 Moving the linker hardening options out of the compile options
- 34976a5 Accepting a git remote URL in the pipeline external documentation URLs check
- 74d4076 Split the DefaultLogger into a static proxy and a real logger instance
- 6929e96 Introducing the appCURLClaude branch info into the READMEs
- 721e10f Introducing the external documentation URLs check into the Jenkins pipeline
- 9d08c78 Correcting the docker modules path of the documentation
- 07e9611 Introducing the quick build and the docker starter scripts
- 02f14f3 Introducing the quick build and the docker starter scripts
- 65ebfa3 Making the docker containers run under unprivileged users
- 30951e1 Formatting the sources with the clang-format
- a3e1d98 Repairing the pipeline code check stages
- 29e7af4 Introducing the appPGPLOT branch info into the READMEs
- 5c1c03b Fixing the Jenkinsfile
- 18f15c2 Fix broken cppcheck link in section 5 index
- a6565ec Fix Groovy escape sequences in markdown link checker stage
- dd2604a Rework markdown link checker stage to pure bash
- b51d9e6 Add Jenkinsfile stage to detect broken markdown links; fix pre-existing broken links
- a678aca Reorganize doc/sections into section dirs with category grouping
- c7c4c6a Add an OpenSSL cmake enabler module with SHA-256, HMAC-SHA256 and HTTPS/TLS client code samples
- a3c40ea Group the enabler documentation under subsections in the READMEs
- cd8f676 Group the compression branches under a dedicated README section
- ad29713 Introducing the appLZMA branch info into the READMEs
- 719ab96 Add a liblzma (XZ Utils) compression library enabler module
- 463cf4b Introducing the appZlib branch info into the READMEs
- b17e995 Add zlib compression usage examples to its enabler documentation
- 452741d Replace the redundant PROJECT_NAME CMake variable with CMAKE_PROJECT_NAME
- d21d0c2 Introducing the appGtkmm4Vulkan branch info into the READMEs
- 74aaa8d Removing the appGtkmm4Vulkan branch info from the READMEs
- 099d560 Introducing the appQt6Vulkan and appGtkmm4Vulkan branches info into the READMEs
- 738fb99 Simplifying root CMakeLists.txt
- 3227501 Introducing the PLplot cmake enabler module and dropping the src/plplot integration
- f07a376 Introducing the appFirebird branch info into the READMEs
- b50223a Introducing the appGtkmm4GDBusClient branch info into the READMEs
- ed47462 Introducing the appQt6GLArea branch info into the READMEs
- 03c2ca4 Introducing the appGtkmm4GLArea branch info into the READMEs
- da4c8ce Splitting the Data Visualization README category into Plots/Graphs and Maps
- 205e627 Introducing the applibMeson branch info into the READMEs
- f37f055 Introducing the zlib and image format cmake enablers with docs
- e29a6f9 Introducing the appSFML branch info into the READMEs
- 3dd736c Introducing the appwxWidgets branch info into the READMEs
- 7f0d692 Introducing the appQt6QtDBusClient branch info into the READMEs
- ee0fd8c Introducing the appQt6QtLocation branch info into the READMEs
- c92cd87 Introducing the appQt6ChartView branch into the READMEs
- a12148b Introducing the appGtkmm4LeafLet and appQt6LeafLet branches info into the READMEs
- 6066601 Introducing the COMPONENTS arg for template_project_default_3rdparty_enabler
- 810ca7b Removing the SDL3 current marking
- b7dc86f Introducing information about the SDL3 branch in the READMEs
- 016f884 Replacing faulty SimpleLogger mention with the DefaultLogger
- 53a33ff Rename the simple logger to DefaultLogger and add top-level log.h tests
- 9118be4 Removing faulty simple_logger mention in the log.h
- da38ca2 Add template-specific packager, documentation and registration checks
- 8888525 Introducing the appSDBusCxxClient and appSDBusCxxServer branches info into the READMEs
- 349883a Moving Dockerfiles and packagers files into separate subdirs in the misc
- cfd2308 Adding .claude dir to .gitignore
- de9e7bf Introducing project structure section Будь ласка, зверніться до адміністратора subsection
- 4f45546 Introducing the libMeson branch info into the READMEs
- 3f01b42 Introducing info about newly created branch appOpenCV into READMEs with it's cmake enabler.
- 8e6a2aa Introducing the CPack's RPM package generator integration
- ff5d86b Removing unmerged lines in the doc/README.uk_UA.md
- 22eb56c Introducing the MS Windows WIX package generation through CPack integration
- 6708211 Introducing the project's FreeBSD pkg package generation support through CPack. Works only on FreeBSD.
- ac8b4fe Deleting REQUIRED marking from the snapcraft's find_program
- d159f14 By default disabling the snap package manager
- cbf4a46 Introducing the snap packager integration with documentation
- 0a279b1 Introducing and migrating to the template_project_default_3rdparty_enabler cmake function. Making enablers git sources variables modifiable.
- 1c0a8d5 Moving all CMake variables declarations into their respectful enablers.
- d4b9d0e Moving Doxygen related CMake variables into doc/CMakeLists.txt file
- cdd448f Introducing the libxml2 enabler cmake module
- dc7695c Enhancing the cmake files fs structure
- 00b3f4d Making docker base image configurable through CMake variables
- 7d692b9 Marking current appPLplot branch
- 3040eba Introducing the appPLplot branch info into the READMEs
- 12a2f46 Introducing the required PLplot packages sections into the READMEs
- c1e5a44 Introducing the PLplot basic integration with a sample plot code.
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

[appPLplot0.12.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/appPLplot0.12.0)
[appPLplot0.11.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/appPLplot0.11.0)
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
