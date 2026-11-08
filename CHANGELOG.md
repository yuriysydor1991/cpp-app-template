# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [applib0.12.0] - 2026-11-08

- 1364d3d Removing the destination OS from the AppImage package name
- 9d88c06 Introducing the LIB_TYPE option for the shared or the static library
- e310561 Introducing the STT branches info into the READMEs
- d78b5b2 Replacing the CMAKE_SOURCE_DIR/CMAKE_BINARY_DIR by the PROJECT_SOURCE_DIR/PROJECT_BINARY_DIR
- acce451 Introducing the appWebAssembly branch info into the READMEs
- 2315576 Introducing the appLlamaCPP branch info into the READMEs
- 5ea148a Introducing the TTS branches info into the READMEs
- bc8f826 Introducing the destination OS into the package names
- c0ddc51 Synchronizing the template flavors list of the READMEs
- ca98cb0 Refreshing the shared library cache after the from-source installs
- a7e50f9 Fixing the AppImage section link of the applib build index pages
- 9483acf Fixing the applib application tests after the stored context errors
- c9ec663 Adapting the test loggers of applib to the bool returning ILogger
- b3aff29 Fixing the cppcheck findings of the new signals handler, tests and log mock
- 945f949 Updating the app component diagram to the signals handlers design
- 5423d81 Renumbering the custom command line parameters section numbered 4-6 twice
- 18eceff Documenting the built in command line options and the usage errors
- acf74b1 Testing the application with the real command line arguments
- 7754c41 Parsing the command line before the log file initialization
- 2afdf3c Exiting with a failure status on the command line usage errors
- 5f55807 Fixing the missing option value raising the version flag instead of the help one
- 55e76a9 Fixing the CommandLineParser test assertions which could not fail
- e9ba0f1 Fixing the log mock LOG_INIT forwarding into the LOG_INIT_DEFAULTS mock
- 40c7acf Restoring the previous signal dispositions on the signals handler uninstall
- f1c52f1 Leaving the SIGTTIN and SIGTTOU signals to the shell job control
- 93ac4a2 Removing the nonexistent module path directories and cppcheck suppression
- f825de0 Fixing the zlib gzip file example ignoring the read and close errors
- a17cf3c Fixing the flatpak requirements section naming an outdated SDK version
- b2f0d0c Documenting the ENABLE_COMPONENT_TESTS option of the test builds
- bfa8b90 Listing every linked doc section in the requirements and build index pages
- 0bddd83 Fixing the documentation links pointing into the other language
- f457172 Fixing the stale file paths named in the documentation
- 96f99d0 Fixing the flatpak target failing on its repeated build
- c5eade2 Fixing the snap command path ignoring the install prefix
- 7b61af7 Fixing the documentation install which needed a manual Doxygen-doc build
- f7f4dcb Skipping the Doxygen and callgrind targets when their tools are missing
- 148531a Installing the packager tools into the Jenkins pipeline image
- 772754a Replacing the libjpeg-turbo download fallback with a clear configure error
- 4708f8e Fixing the libavif download fallback stopping without the system libyuv
- e2e5069 Pinning the third-party download fallbacks to their release tags
- 8470bac Failing the CI test stages which match no tests
- 095ecfa Fixing the Jenkins doc sections linked check skipping the section directories
- 8662113 Replacing the broken OpenSSL download fallback with a clear configure error
- fab3b91 Fixing the mixed target_link_libraries signatures on the project binary
- 0739b35 Fixing the MAX_LOG_LEVEL option help text error level value
- aac003c Fixing the logger level filter tests which could not fail
- 06c74dd Fixing the log macros to expand into single statements
- e3574ba Fixing the logger data races on the log file reopening and the level
- 81aee91 Fixing the log file open failure aborting the process
- 7315886 Splitting the CTEST_DefaultLogger helper classes into own files
- 5f897e3 Splitting the packages install scripts per OS release
- 28a64c2 Fixing the enablers to link the dependencies to the library target
- 47df193 Fixing the duplicate 4-8 and the colliding 5-23 library doc numbers
- c816230 Introducing the RUNPATH of the executable to the installed library
- 2382591 Fixing the library install directory to follow the CMAKE_INSTALL_LIBDIR
- dba4282 Fixing the installed CMake package of the library
- dba7899 Fixing the UTEST_LibraryFacade test names and returned value checks
- 1541638 Fixing the thread unsafe logger initialization of the LibMain
- 650de56 Fixing the unchecked library instance of the Application
- 55ac8da Removing the misspelled RPIVATE include directories of the executable
- 71b491e Fixing the cppcheck target findings of the library sources
- 7a1a05d Merging the duplicate log and LibMain mocks into the general mocks
- 8cf1a5d Removing the duplicate ApplicationVersionPrinter source of the CTEST_app
- 211d45a Synchronizing the get_stop assertions of the application tests with app
- a2e5d74 Synchronizing the CommandLineParser::parse_args doc comment with the app branch
- 1971074 Replacing int flag with a bool for the CommandLineParser
- fe3aaa1 Supressing the cppcheck's missingIncludeSystem and unusedStructMember warnings.
- 9fc2e50 Erasing redundant suppression that causes cppcheck to fail
- 2f7d690 Introducing the desktop application packaging switch
- d936453 Moving the packagers templates into the per-packager directories
- 5ab4fcb Moving Dockerfiles and packagers files into separate subdirs in the misc
- 5622d68 Replacing the unreachable GNU gettext site link with its Savannah page
- 8bbc762 Introducing the destination CPU architecture into the package names
- 1491510 Introducing the appGettext branch info into the READMEs
- 1a1bba5 Introducing the appDarknetXX branch info into the READMEs
- b49a7a9 Introducing the RedHat packages install script
- d09d3be Introducing the appWhisperCPP branch info into the READMEs
- 2f4161d Introducing the FreeBSD packages install script
- 4966dec Introducing the appV8 branch info into the READMEs
- c379b7e Erasing the build sources and trees of the docker images
- d834e2f Introducing the debug clang-format script
- 05c93a0 Resetting the inherited signals dispositions in the signals handlers tests
- 420ed87 Introducing the binary hardening options section into the READMEs
- 14df412 Introducing the binary hardening compile and link options
- 371d587 Introducing the GitLab CI/CD pipeline section into the READMEs
- bc2989d Introducing the GitLab CI/CD pipeline mirroring the Jenkinsfile
- 3b59b9d Introducing the GitHub Actions CI pipeline section into the READMEs
- 3b6ae3c Introducing the GitHub Actions CI pipeline mirroring the Jenkinsfile
- e1b40df Correcting the appQt6QtDBusClient branch description in the READMEs
- 54da0f3 Limiting the documentation checks to the repository own markdown files
- 8710a50 Excluding the GCC own include directories from the clang-tidy search path
- b36559b Accepting the 405 documentation URLs
- 7db3cc3 Applying the clang-format to the test sources
- 475e5cf Spacing out the branch entries in the READMEs
- 3717d22 Rewording the DOCKER_HOST environment requirement in the docker docs
- 7ef4f58 Removing the DOCKER_HOST variables from the docker enablers
- 30e16ab Excluding the build trees from the Docker build context
- dc53c75 Retrying the unreachable documentation URLs and accepting the 403 ones
- baf105d Introducing the --rebuild flag into the Jenkins docker scripts
- 4a249ba Rebuilding the image from its base on the Jenkins pipeline force rebuild
- e079d9a Introducing the audio assets branches info into the READMEs
- 220a0d1 Splitting the signals handlers per category and covering the pause, reload, user defined and ignored signals
- eb2104d Introducing the app signals handlers subcomponent
- c6e79b4 Declaring the main function argv parameter as an array
- 1c3b9e5 Moving the packagers templates into the per-packager directories
- f3fe66e Dropping the packagers and the development tools from the packages install list
- 9ece39d The destination CPU architecture of the AppImage package name
- 148f0b2 Picking the CPack AppImage enabler since the CMake 4.2 and dropping the debug banners
- 6b83610 Extracting the AppImage enabler pick into its own general enabler
- ea277c6 Selecting the AppImage packager enabler by the CMake version
- 7db5904 Introducing the CPack based AppImage packager enabler
- 19e7168 Introducing the AppImage packager
- 45a0a70 Introducing the --install flag into the packager build scripts
- d33a205 Renaming the packages install script and adding the Ubuntu one
- b9e951e Introducing the target architecture into the flatpak package name
- 84c5027 Introducing the AppStream metainfo file into the flatpak package
- 3419bb7 Consuming the install directory variables the flatpak-builder passes
- 0ad7b88 Introducing the required packages install script
- 961c9d0 Installing the flatpak build dependencies from the flathub remote
- 28a6010 Dropping the redundant build step from the packager scripts
- 0e56251 Introducing the per packager build scripts
- 705e70e Moving the logger interface into the installable public headers
- f5d29e6 Hiding the library implementation symbols and versioning the public namespace
- 618c7e9 Introducing the appCFITSIO branch info into the READMEs
- ceaba64 Make the compile time log level gate really gate
- 550e2a0 Introducing the appGtkmm4Libadwaita branch info into the READMEs
- 1d1d9f8 Pinning the log message stream to the classic locale
- 98928b7 Introducing the LIB_INSTALL_DEV_FILES install option
- a66aea6 Decomposing the IApplication descendants into the applications subcomponent
- 1710f35 Introducing the appFontAwesome branch info into the READMEs
- 97caf5e Introducing the debug test script and its --test parameter
- bd2c6d9 Incrementing version to applib0.12.0
- 0466bbe Release applib0.11.0 at 2026-08-17

## [applib0.11.0] - 2026-08-17

- 2e77835 Introducing the InsertNewlineAtEOF clang-format option
- 1c59365 Introducing the appCURLChatGPT branch info into the READMEs
- 556fd8f Hiding the ApplicationContext fields and adding the atomic stop flag
- 556ea5d Moving the linker hardening options out of the compile options
- ca4a450 Initializing the library part logging with the application logger instance
- 07ea8a1 Split the DefaultLogger into a static proxy and a real logger instance
- ea33eee Introducing the appCURLClaude branch info into the READMEs
- 2ef6417 Introducing the external documentation URLs check into the Jenkins pipeline
- 2de4d96 Correcting the docker modules path of the documentation
- cb9740d Introducing the quick build and the docker starter scripts
- 0a3ba2e Making the docker containers run under unprivileged users
- 76b307d Formatting the sources with the clang-format
- 2e0b877 Repairing the pipeline code check stages
- 19f609e Accept directory targets in the markdown link checker
- e6b5a9a Introducing the appPGPLOT branch info into the READMEs
- d6f9385 Fixing the Jenkisfile
- cb0e1b6 Fix broken cppcheck link in section 5 index
- 7c2778d Fix Groovy escape sequences in markdown link checker stage
- 0fbc7d1 Rework markdown link checker stage to pure bash
- f05c67d Add Jenkinsfile stage to detect broken markdown links; fix pre-existing broken links
- 19da755 Reorganize doc/sections into section dirs with category grouping
- 88c66cc Add an OpenSSL cmake enabler module with SHA-256, HMAC-SHA256 and HTTPS/TLS client code samples
- 1f4fdfb Group the enabler documentation under subsections in the READMEs
- 779dee4 Group the compression branches under a dedicated README section
- 982f722 Introducing the appLZMA branch info into the READMEs
- 3403095 Add a liblzma (XZ Utils) compression library enabler module
- 94d40c5 Introducing the appZlib branch info into the READMEs
- 03bd4fc Add zlib compression usage examples to its enabler documentation
- a935a59 Replace the redundant PROJECT_NAME CMake variable with CMAKE_PROJECT_NAME
- 5273bb4 Introducing the appGtkmm4Vulkan branch info into the READMEs
- 2f57041 Removing the appGtkmm4Vulkan branch info from the READMEs
- 23c439c Introducing the appQt6Vulkan and appGtkmm4Vulkan branches info into the READMEs
- 90f73b9 Simplifying root CMakeLists.txt
- df6f663 Introducing the appFirebird branch info into the READMEs
- b937c50 Introducing the appGtkmm4GDBusClient branch info into the READMEs
- dfae678 Introducing the appQt6GLArea branch info into the READMEs
- 7f3edf4 Introducing the appGtkmm4GLArea branch info into the READMEs
- c812e01 Splitting the Data Visualization README category into Plots/Graphs and Maps
- 4dfaebb Introducing the applibMeson branch info into the READMEs
- 225737a Introducing the zlib and image format cmake enablers with docs
- f61b219 Introducing the appSFML branch info into the READMEs
- 480faa2 Introducing the appwxWidgets branch info into the READMEs
- 336fadc Introducing the appQt6QtDBusClient branch info into the READMEs
- 349c69a Introducing the appQt6QtLocation branch info into the READMEs
- b19cd06 Introducing the appQt6ChartView branch into the READMEs
- 97ecc14 Introducing the appGtkmm4LeafLet and appQt6LeafLet branches info into the READMEs
- 10f5d1b Introducing the COMPONENTS arg for template_project_default_3rdparty_enabler
- 0fc9d91 Removing the SDL3 current marking
- 53a8bfb Introducing information about the SDL3 branch in the READMEs
- 0b53d93 Merging README.uk_UA.md
- 2755140 Replacing faulty SimpleLogger mention with the DefaultLogger
- 3487e88 Rename the simple logger to DefaultLogger and add top-level log.h tests
- 64b0962 Removing faulty simple_logger mention in the log.h
- bd0a69a Add template-specific packager, documentation and registration checks
- 990c469 Introducing the appSDBusCxxClient and appSDBusCxxServer branches info into the READMEs
- 53cdf93 Adding .claude dir to .gitignore
- 93cb334 Introducing project structure section Будь ласка, зверніться до адміністратора subsection
- 6eafcfc Documenting the optional library-name segments options
- eca6b06 Introducing optional minor/micro/suffix segments into the installable library name
- 8d77f5f Introducing the libMeson branch info into the READMEs
- b6485b9 Introducing info about newly created branch appOpenCV into READMEs with it's cmake enabler.
- 3de6ef2 Introducing the CPack's RPM package generator integration
- bf4ca22 Removing unmerged lines in the doc/README.uk_UA.md
- f8058b3 Introducing the MS Windows WIX package generation through CPack integration
- e52ff1d Introducing the project's FreeBSD pkg package generation support through CPack. Works only on FreeBSD.
- 753fbd2 Deleting REQUIRED marking from the snapcraft's find_program
- 624c83d By default disabling the snap package manager
- 79eece8 Introducing the snap packager integration with documentation
- eefb35c Introducing and migrating to the template_project_default_3rdparty_enabler cmake function. Making enablers git sources variables modifiable.
- 4838576 Moving all CMake variables declarations into their respectful enablers.
- 7124dc9 Moving Doxygen related CMake variables into doc/CMakeLists.txt file
- 10ce69a Introducing the libxml2 enabler cmake module
- 07916c0 Enhancing the cmake files fs structure
- cef4ead Making docker base image configurable through CMake variables
- 064a1c4 Introducing the appPLplot branch info into the READMEs
- 59e3b7b Introducing the MatPlot++ appMatPlotxx branch into the READMEs
- 6205197 Making the cppcheck stage optional due to unstable results
- 249b28d Fixing clang-tidy conf misspell
- 16d53d4 Switching off the clang-tydy's unrecognizable AnalyzeTemporaryDtors config param
- 253c73a Loggging README's misspell refine
- af4d7a0 Grouping and categorising available template flavors links in the READMEs
- 95ee4d6 Renaming properly Nlohmann JSON library CMake enabler file
- 538abea Introducing the forgottent Nlohmann JSON library enabler info into the READMEs
- 397d076 Decomposing READMEs
- 5b9837b Introducing the ENABLE_LOGS_MICROSECONDS_TIME CMake option in order to be able to disable microseconds in the log messages.
- ee48825  Introducing the --branch cmd line flag for git clone command in the READMEs
- a582b1a Introducing the lib component diagram into the READMEs
- a0dfaf1 Introducing explicit template altering notice in the READMEs headers
- 58ec624 Optimizing some CMake commands in the README.md
- 5ce4b57 Introducing the appGtkmm4 branch info into the READMEs
- b6e2747 Introducing the PlantUML app component diagram into the READMEs
- f1ac20c Fixing links for public headers section in translated README
- 407dff1 Introducing the library's public installable header files info into the READMEs
- f730c1f Applied code formatting
- 17b285f Enabling GTest during for CTs
- 9fc0849 Pointing Jenkins configurable port into standart in-container 8080
- da2bb5b Making the Jenkins pipeline container and image names configurable
- 0a0aa9f Refining app component CTs
- 49a067c Repairing the CTEST_app
- 48a43f9 Introducing basic app CTs samples
- 8354d2b Introducing basic SimpleLogger CTs with CMake and Jenkins integration
- e614813 Refining the branches link in the READMEs, introducing gitlab links also
- 5c008e3 Specifying the Jenkins container run target in the READMEs
- 3c4b427 Introducing basic Jenkins pipeline CMake target and Jenkinsfile conf
- 2c5121b Incrementing version to 0.11.0
- f3f0e70 Release 0.10.0 at 2025-09-08

## [applib0.10.0] - 2025-09-08

- 6290c4e Repairing segflt on the App's UTs
- 8eb03ba Refining Application's UTs
- 1c4a74e Including the main Config.cmake file into installation candidates
- 8758a28 Library infrastructure reorg. Introducing basic installable CMake module.
- cae6ce6 Fixing typo in the README.md
- 9be1e05 Introducing the valgrind callgrind profiler target for the project
- 363dd55 Introducing the gprof profiling target
- 2ede6fa Adding money emoji to donation notice in the READMEs
- 29b35a6 Introducing the appCURL branch info into the READMEs
- b5a186d Introducing the enabling libcurl section into the READMEs
- 72c984e Introducing the libcurl cmake enabler script
- 09a78df Moving the DEFAULT_LOG_FILE_PATH macro declaration into severity-macro-consts.h
- 37d345c Refining unit tests to match the new log code
- 3d7add8 Introducing a custom log file cmd param for the executable
- d470e5c Introducing the DEFAULT_LOG_FILE_PATH cmake var and cpp macro to specify default dst log file location
- 5a38cf0 Introducing the CMDParamNames class to encapsulate CMD params names
- b454c72 Introducing some marketing sentences in the README's goal section
- aa05140 Introducing the cmake/enablers subdirectory to locate the 3rd-party dependencies
- ceb5b6e Renaming emplate-project-make-GTest-available - template-project-GTest-enabler
- e4227d0 Introducing the NLohmann JSON library enabler cmake module
- fc07827 Fixing the sanitizers cmake file in the READMEs
- 88ddbf2 Avoiding unnecessary badly portable localtime_r usage
- 5ca30e4 Introducing the thread id into simple logger
- 1afa9bb Avoiding backward time in the simple logs
- edf6d90 Avoiding final log multiple str fetches
- 33b6962 Refining the log current timestamp method, increasing thread safety
- 9e8999d Introducing the CMake configurable log severity messages compilation switch
- 038e9c9 Introducing the appBoostLog branch info into the READMEs
- 7ec2633 Hiding the compile options cmake files under separate directory
- 2166e5a Enhancing sanitizers combinations and new cmake dir for ones
- 6485392 Introducing the sanitizers enabling info into the READMEs
- 2190f74 Removing redundant cmake traces messages
- a8833e9 Introducing the GCC compiler sanitizers
- f2f2653 Release applib0.9.0 2025-06-06

## [applib0.9.0] - 2025-06-06

- 8c15c24 Incrementing version to 0.9.0
- 2bf709a Refined issues in the Docker READMEs doc
- b8fc7d2 Separating the Docker single container build and run targets
- 40c7eb0 Introducing the Docker single run container target.
- c1eb4e4 Adding project neatness to the READMEs
- da45334 Introducing the appLog4Cpp5 branch info into the READMEs
- 62f169f Implementing the logging macros and a simple logger to perform log messaging
- 70d9c05 Introducing the appMongoDBCpp4 branch info into the READMEs
- 93b7563 Making the flatpak source json conf file configurable during cmake conf stage
- 448ed29 Refining the deb cmake info for cpack
- 619ccc8 Introducing the appSQLiteCpp3 branch info into the READMEs
- bf40e16 Refining the ApplicationContext mock
- fff404c Introducing the gitlab mirror into the READMEs
- 9d9904c Introducing the appMySQLCppConn branch info into the READMEs
- 369ff0f Introducing the appBoostBeast branch info into the READMEs
- 7cfd03c Explicitly specifying the combining of the template branches
- bbb5879 introducing the appPgSQLxx branch into the READMEs
- ced3566 Introducing a new appWt4 branch info into the READMEs
- fbd0a34 Introducing the error exit code for a cppcheck target
- 1a30076 Refining the cppcheck target
- d74a56a Introducing the donation notice into the READMEs
- 0ed43d8 Introducing the flatpak sections into the READMEs
- 78c1bfc Introducing the flatpak package creation from the template source.
- 837f4e1 Introducing the appMeson branch info into the READMEs
- da1bcfc Refining branch info
- ac72506 Erasing the /analyze from the default MSVC compile options
- 48d4668 Introducing the DEB package gen info in the READMEs
- 2735d3e Introducing the cpack configuration for the deb package generation
- c5c9978 Introducing the LICENSE file with free of use license and notice
- 9a3cb05 Introducing the appSDL2 branch into the READMEs
- f9ff528 Introducing clang-tidy
- b6a5c7b Erasing redundant libraries installation info
- afd6b57 Introducing the FreeGlut/OpenGL appFreeGlut branch info into READMEs
- 0fa45ef Release applib0.8.0 2025-03-17

## [applib0.8.0] - 2025-03-17

- d8149e0 Introducing MSVC extra compile options for warnings
- ffaeb75 Adding MSVC settings file to the .gitignore
- 543a7fa Avoiding the compilation warnings at the UTEST_CommandLineParser
- 94c12a5 Introducing MS Windows tools install description into READMEs
- 8ca7ba4 Adding the out directory for MSVC into .gitignore
- 35e34fd Specifying the appGtkmm3Glade branch in the READMEs
- 55c4a42 Introducing the appGtkmm3 branch info into the READMEs
- 4062f58 Replacing the /usr/bin prefix parameter with right /usr in installation section
- eb1a749 Introducing the lib branch info into the READMEs
- 7e8d539 Introducing the appQt6 branch in READMEs
- a6d72dc Introducing Doxygen doc with translated README as main page facility
- 73e5d0d Introducing COMPILE_WARNINGS_AS_ERRORS and ENABLE_COMPILER_CODE_ANALYZER CMake vars.
- d4c6dc1 Incrementing version to 0.8.0
- ead330e Inserting forgoten realease link in the CHANGELOG

## [applib0.7.0] - 2025-03-14

- f5b1d13 Release applib0.7.0 2025-03-17
- 473bb31 Refining typos in uk_UA README
- ab45738 Refining all the READMEs
- cfa03d8 Introducing the sample LibMain UTs
- c019bd3 Refining lib UTs
- 2230643 refining LibraryFacade tests
- 5b23447 Introducing LibFactory UTs
- f67a3ca Specifying the library targets and formatting the code.
- 11f5b6d Introducing LibraryFacade UTs.
- 95092ff Moving ILib to the facade folder.
- d02674e Incrementing version to 0.7.0 and changing description

## [applib0.6.0] - 2025-03-13

- 3b43b68 Release applib0.6.0 2025-03-13 21:54
- 8635ccb Release applib0.6.0 2025-03-13
- d0a0eed Introducing explanatory comments for new LibraryContext class fields.
- 34988bb Introducing ApplicationContext2LibraryContext UTs with moved general mocks
- f83084b Removing forgotten debug #error
- d978ec1 Specifying translation documents for the root README under the doc
- c41e944 Specifying the source file for the PROJECT_BINARY_NAME CMake variable
- 78e90c7 Some README.md refinements
- 1f46f37 Refining SOLID comment for Implement code straight away
- 89de1b3 Introducing the ApplicationContext2LibraryContext class with mocks and refined Application UTs
- 492817a Introducing additional library related info into README.md
- 6f48e44 Marking applib branch as current in the README.md
- 522ccfc Introducing multibranch info into the root README.md
- 3f11e47 Marking LibraryContext destructure as virtual to allow subclassing
- 5a8b53b Renaming library facade namespace to templatelib0
- 27bc62a Fixing wrong article.
- 96e24aa Applying clang-format
- 71c3c6d Refining UTEST_Application unit test to pass.
- c223375 Introducing library mocks for the app component
- 45cb5fb Refining library classes explanatory comments.
- 2d2c974 Marking library facade cpp file as private.
- 8cac51b Introducing library component facade and default implementation.
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

[applib0.12.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/applib0.12.0)
[applib0.11.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/applib0.11.0)
[applib0.10.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/applib0.10.0)
[applib0.9.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/applib0.9.0)
[applib0.8.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/applib0.8.0)
[applib0.7.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/applib0.7.0)
[applib0.6.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/applib0.6.0)
[app0.5.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.5.0)
[app0.4.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.4.0)
[app0.3.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.3.0)
[app0.2.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.2.0)
[v0.1.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/v0.1.0)

