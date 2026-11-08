# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [appBoostBeast0.11.0] - 2026-11-08

- 2156404 Removing the destination OS from the AppImage package name
- 00af828 Introducing the STT branches info into the READMEs
- 6545a47 Replacing the CMAKE_SOURCE_DIR/CMAKE_BINARY_DIR by the PROJECT_SOURCE_DIR/PROJECT_BINARY_DIR
- 4ab3e8e Introducing the appWebAssembly branch info into the READMEs
- ccfc323 Introducing the appLlamaCPP branch info into the READMEs
- b2b026e Introducing the inja HTML templates library cmake enabler
- 95a6eca Introducing the TTS branches info into the READMEs
- 0616026 Introducing the destination OS into the package names
- b05202f Fixing the branch name of the cloning commands in the docs
- 8f05c25 Synchronizing the template flavors list of the READMEs
- 860ad49 Refreshing the shared library cache after the from-source installs
- 8857a9e Failing the flavor CI test stages which match no tests
- 931c201 Converting the flavor link calls of the project binary to the keyword signature
- c941ddd Fixing the cppcheck findings of the new signals handler, tests and log mock
- 66d33a5 Updating the app component diagram to the signals handlers design
- e35596c Renumbering the custom command line parameters section numbered 4-6 twice
- 162ef6f Documenting the built in command line options and the usage errors
- cec0f48 Testing the application with the real command line arguments
- a39895d Parsing the command line before the log file initialization
- aed81e4 Exiting with a failure status on the command line usage errors
- a1c5846 Fixing the missing option value raising the version flag instead of the help one
- 229c956 Fixing the CommandLineParser test assertions which could not fail
- dcd43dd Fixing the log mock LOG_INIT forwarding into the LOG_INIT_DEFAULTS mock
- 3941517 Restoring the previous signal dispositions on the signals handler uninstall
- ff9693e Leaving the SIGTTIN and SIGTTOU signals to the shell job control
- b63715a Removing the nonexistent module path directories and cppcheck suppression
- a01184f Fixing the zlib gzip file example ignoring the read and close errors
- 3eafb81 Fixing the flatpak requirements section naming an outdated SDK version
- 77e9f50 Documenting the ENABLE_COMPONENT_TESTS option of the test builds
- 7274e4a Listing every linked doc section in the requirements and build index pages
- a474618 Fixing the documentation links pointing into the other language
- 0d7e416 Fixing the stale file paths named in the documentation
- 471da4c Fixing the flatpak target failing on its repeated build
- 407d0a3 Fixing the snap command path ignoring the install prefix
- 5e2745a Fixing the documentation install which needed a manual Doxygen-doc build
- f84a90c Skipping the Doxygen and callgrind targets when their tools are missing
- a92828b Installing the packager tools into the Jenkins pipeline image
- 5053bd9 Replacing the libjpeg-turbo download fallback with a clear configure error
- 9ca8f29 Fixing the libavif download fallback stopping without the system libyuv
- 30ecb96 Pinning the third-party download fallbacks to their release tags
- 3d2bf90 Failing the CI test stages which match no tests
- 01d0450 Fixing the Jenkins doc sections linked check skipping the section directories
- 5e9e433 Replacing the broken OpenSSL download fallback with a clear configure error
- 286ecfd Fixing the mixed target_link_libraries signatures on the project binary
- 3d946c7 Fixing the MAX_LOG_LEVEL option help text error level value
- b789e51 Fixing the logger level filter tests which could not fail
- 63857e0 Fixing the log macros to expand into single statements
- 4f2824c Fixing the logger data races on the log file reopening and the level
- 7580656 Fixing the log file open failure aborting the process
- 8071da5 Splitting the CTEST_DefaultLogger helper classes into own files
- 3babe55 Splitting the packages install scripts per OS release
- a435a9a Documenting the Boost.Beast server listen settings and served requests
- 4659b24 Replacing the hard-coded deb dependency with the dpkg-shlibdeps detection
- be2dd30 Fixing the cppcheck findings in the branch code
- c2b509a Removing the undefined perform_http_request declaration from the HTTPHelper
- c7ccbaa Fixing the swapped description and keywords meta tags of the default page
- 40c81f4 Answering the unsupported HTTP methods and paths with the 405 and 404 statuses
- ee14658 Applying the clang-format to the Beast HTTP controller
- f20281b Removing the unused Boost.Thread link from the Beast targets
- 4ca84b4 Linking the Boost.Beast requirements doc from the en requirements index
- f079191 Renumbering the branch requirements doc into the free 3-13 section
- 3d51955 Synchronizing the get_stop assertions and the CommandLineParser doc comment with app
- cac74c1 Bounding the test HTTP clients count by the server connections limit
- a64fb44 Fixing the HTTP server stop while it waits for a connection
- 390aa1c Moving the LimitedController test helper into its own file
- 4972f8d Moving the test mocks back to the app's mocks location
- 6549da7 Supressing the cppcheck's missingIncludeSystem and unusedStructMember warnings.
- cdb4aa4 Replacing the unreachable GNU gettext site link with its Savannah page
- b012462 Introducing the destination CPU architecture into the package names
- 2f1432c Introducing the appGettext branch info into the READMEs
- c9674c8 Handing the Boost headers over to the Boost.Beast object libraries
- 7db50e2 Introducing the appDarknetXX branch info into the READMEs
- 4f41aed Introducing the RedHat packages install script
- 15c1506 Introducing the appWhisperCPP branch info into the READMEs
- d10621a Introducing the FreeBSD packages install script
- 9377234 Introducing the appV8 branch info into the READMEs
- f937351 Erasing the build sources and trees of the docker images
- a181e4d Introducing the debug clang-format script
- ae9f6a9 Setting the security header fields by name for Boost older than 1.90
- e1c5dd8 Resetting the inherited signals dispositions in the signals handlers tests
- d14aa67 Introducing the HTTP server hardening constraints section into the READMEs
- ce40c2a Introducing the HTTP server hardening constraints
- a6b5320 Introducing the binary hardening options section into the READMEs
- c00ef87 Introducing the binary hardening compile and link options
- a17fa04 Introducing the GitLab CI/CD pipeline section into the READMEs
- 720bb20 Introducing the GitLab CI/CD pipeline mirroring the Jenkinsfile
- 3f4807a Introducing the GitHub Actions CI pipeline section into the READMEs
- beb308d Introducing the GitHub Actions CI pipeline mirroring the Jenkinsfile
- 6c80756 Deleting garbage _gen directory
- f399193 Correcting the appQt6QtDBusClient branch description in the READMEs
- 2fc1892 Introducing the desktop application packaging switch
- b1f197f Limiting the documentation checks to the repository own markdown files
- f2794a2 Excluding the GCC own include directories from the clang-tidy search path
- 3eea48a Accepting the 405 documentation URLs
- e005b58 Sequencing the stop expectations of the multithread beasthttp CT
- 08b227a Storing the flags values in the ApplicationContext tests mock
- ddcdff1 Applying the clang-format to the test sources
- 6d16b9c Spacing out the branch entries in the READMEs
- 249bffb Rewording the DOCKER_HOST environment requirement in the docker docs
- 05d4c76 Removing the DOCKER_HOST variables from the docker enablers
- 0327ffe Excluding the build trees from the Docker build context
- 728fa84 Retrying the unreachable documentation URLs and accepting the 403 ones
- 49364f5 Introducing the --rebuild flag into the Jenkins docker scripts
- 282eb02 Rebuilding the image from its base on the Jenkins pipeline force rebuild
- f6cf1f1 Introducing the audio assets branches info into the READMEs
- aa3c107 Splitting the signals handlers per category and covering the pause, reload, user defined and ignored signals
- b429f94 Introducing the app signals handlers subcomponent
- c056213 Declaring the main function argv parameter as an array
- eb87dbf Moving the packagers templates into the per-packager directories
- e0b8535 Dropping the packagers and the development tools from the packages install list
- cb65057 The destination CPU architecture of the AppImage package name
- 96e278d Picking the CPack AppImage enabler since the CMake 4.2 and dropping the debug banners
- ccb6b75 Extracting the AppImage enabler pick into its own general enabler
- 5c8de64 Selecting the AppImage packager enabler by the CMake version
- 6645f63 Introducing the CPack based AppImage packager enabler
- fcd63b5 Introducing the AppImage packager
- 5b2606a Introducing the --install flag into the packager build scripts
- 353ba06 Renaming the packages install script and adding the Ubuntu one
- b110ee5 Introducing the target architecture into the flatpak package name
- f9e8e7c Introducing the AppStream metainfo file into the flatpak package
- f26f744 Consuming the install directory variables the flatpak-builder passes
- 9fae54c Introducing the required packages install script
- cda87d4 Installing the flatpak build dependencies from the flathub remote
- 428fde0 Dropping the redundant build step from the packager scripts
- 57fe977 Introducing the per packager build scripts
- d015482 Introducing the appCFITSIO branch info into the READMEs
- d336ccf Make the compile time log level gate really gate
- 6b5fc26 Introducing the appGtkmm4Libadwaita branch info into the READMEs
- 856f171 Pinning the log message stream to the classic locale
- 24820cc Decomposing the IApplication descendants into the applications subcomponent
- 455bec0 Introducing the appFontAwesome branch info into the READMEs
- 4450268 Introducing the debug test script and its --test parameter
- 8138c40 Incrementing version to appBoostBeast0.11.0
- b0fdfd7 Release appBoostBeast0.10.0 at 2026-08-17

## [appBoostBeast0.10.0] - 2026-08-17

- 53a3871 Introducing the InsertNewlineAtEOF clang-format option
- e52f53f Erasing the duplicated log mock of the application tests
- 272c1cf Restoring the mocked stop flag of the ApplicationContext tests mock
- f3f9f5b Requesting the Boost.System component only when the Boost build provides it
- 913cfd2 Introducing the appCURLChatGPT branch info into the READMEs
- 47e8072 Hiding the ApplicationContext fields and adding the atomic stop flag
- 8c85e3d Moving the linker hardening options out of the compile options
- 427e293 Split the DefaultLogger into a static proxy and a real logger instance
- 8a25568 Introducing the appCURLClaude branch info into the READMEs
- 7439404 Introducing the external documentation URLs check into the Jenkins pipeline
- 41ada69 Correcting the docker modules path of the documentation
- c0b3923 Introducing the quick build and the docker starter scripts
- c27d99b Introducing the quick build and the docker starter scripts
- b767cc4 Making the docker containers run under unprivileged users
- 69e6f12 Formatting the sources with the clang-format
- 3c6d636 Repairing the pipeline code check stages
- b3e9269 Introducing the appPGPLOT branch info into the READMEs
- 71dbab1 Fixing the Jenkinsfile
- 3bfc8da Fix broken cppcheck link in section 5 index
- 4a22cd9 Fix Groovy escape sequences in markdown link checker stage
- c7be186 Rework markdown link checker stage to pure bash
- 58e62e5 Add Jenkinsfile stage to detect broken markdown links; fix pre-existing broken links
- e62b3d6 Reorganize doc/sections into section dirs with category grouping
- 6271404 Add an OpenSSL cmake enabler module with SHA-256, HMAC-SHA256 and HTTPS/TLS client code samples
- 3eb8309 Group the enabler documentation under subsections in the READMEs
- fa2d508 Group the compression branches under a dedicated README section
- a9f3779 Introducing the appLZMA branch info into the READMEs
- 3c8cb69 Add a liblzma (XZ Utils) compression library enabler module
- c56f95a Introducing the appZlib branch info into the READMEs
- 9f6fdf9 Add zlib compression usage examples to its enabler documentation
- 6e9807b Replace the redundant PROJECT_NAME CMake variable with CMAKE_PROJECT_NAME
- bb03c61 Introducing the appGtkmm4Vulkan branch info into the READMEs
- 244408f Removing the appGtkmm4Vulkan branch info from the READMEs
- e0825ae Introducing the appQt6Vulkan and appGtkmm4Vulkan branches info into the READMEs
- 3c7dcf3 Simplifying root CMakeLists.txt
- 9a979be Introducing the appFirebird branch info into the READMEs
- bba6ba3 Introducing the appGtkmm4GDBusClient branch info into the READMEs
- 2b1186e Introducing the appQt6GLArea branch info into the READMEs
- dc9793b Introducing the appGtkmm4GLArea branch info into the READMEs
- 00c3039 Splitting the Data Visualization README category into Plots/Graphs and Maps
- 2c302df Introducing the applibMeson branch info into the READMEs
- 09ef5a7 Introducing the zlib and image format cmake enablers with docs
- 845dbaa Introducing the appSFML branch info into the READMEs
- 8e4342a Introducing the appwxWidgets branch info into the READMEs
- d9cb576 Introducing the appQt6QtDBusClient branch info into the READMEs
- 16a3c3d Introducing the appQt6QtLocation branch info into the READMEs
- e319ee2 Introducing the appQt6ChartView branch into the READMEs
- a927fcd Introducing the appGtkmm4LeafLet and appQt6LeafLet branches info into the READMEs
- adc4a42 Introducing the COMPONENTS arg for template_project_default_3rdparty_enabler
- 2f961c6 Removing the SDL3 current marking
- f996243 Introducing information about the SDL3 branch in the READMEs
- 68597a4 Registering missing CTEST_beasthttp in the Jenkinsfile
- cb6a3f5 Fixing en_US section link in the translation README.uk_UA.md
- a9ef916 Fixing component test for boosthttp
- 2d1793f Replacing faulty SimpleLogger mention with the DefaultLogger
- 1d51f47 Removing faulty simple_logger mention in the log.h
- 498591f Add template-specific packager, documentation and registration checks
- f8e0c89 Rename the simple logger to DefaultLogger and add top-level log.h tests
- 423e08d Introducing the appSDBusCxxClient and appSDBusCxxServer branches info into the READMEs
- 73c74ef Moving Dockerfiles and packagers files into separate subdirs in the misc
- faec6c8 Adding .claude dir to .gitignore
- c3bab5e Introducing project structure section Будь ласка, зверніться до адміністратора subsection
- 5611fac Introducing the libMeson branch info into the READMEs
- 75133ca Introducing info about newly created branch appOpenCV into READMEs with it's cmake enabler.
- 99a3df4 Introducing the CPack's RPM package generator integration
- 8748cab Removing unmerged lines in the doc/README.uk_UA.md
- 848b2a2 Introducing the MS Windows WIX package generation through CPack integration
- 886887d Introducing the project's FreeBSD pkg package generation support through CPack. Works only on FreeBSD.
- 5da3a99 Deleting REQUIRED marking from the snapcraft's find_program
- 5e84b08 By default disabling the snap package manager
- 85ea05d Introducing the snap packager integration with documentation
- 1eb85d6 Introducing and migrating to the template_project_default_3rdparty_enabler cmake function. Making enablers git sources variables modifiable.
- 4457a0c Moving all CMake variables declarations into their respectful enablers.
- 0842871 Moving Doxygen related CMake variables into doc/CMakeLists.txt file
- 813ddf1 Introducing the libxml2 enabler cmake module
- 33ac7ac Enhancing the cmake files fs structure
- 1464532 Making docker base image configurable through CMake variables
- cb6b3cb Introducing the appPLplot branch info into the READMEs
- 82d9c1e Introducing the MatPlot++ appMatPlotxx branch into the READMEs
- f732d08 Making the cppcheck stage optional due to unstable results
- 5cd992c Fixing clang-tidy conf misspell
- fe5e6f7 Switching off the clang-tydy's unrecognizable AnalyzeTemporaryDtors config param
- 089f054 Loggging README's misspell refine
- 81a216f Grouping and categorising available template flavors links in the READMEs
- 2bf859f Renaming properly Nlohmann JSON library CMake enabler file
- 8bd9db8 Introducing the forgottent Nlohmann JSON library enabler info into the READMEs
- 60292ea Decomposing READMEs
- 4b820ae Introducing the ENABLE_LOGS_MICROSECONDS_TIME CMake option in order to be able to disable microseconds in the log messages.
- 99b2b29  Introducing the --branch cmd line flag for git clone command in the READMEs
- 4d5b87b Introducing explicit template altering notice in the READMEs headers
- 9bfd4c0 Optimizing some CMake commands in the README.md
- fe3abda Introducing the appGtkmm4 branch info into the READMEs
- 53b6630 Incrementing version to 0.10.0
- 3714b97 Release appBoostBeast0.9.0 at 2025-09-27

## [appBoostBeast0.9.0] - 2025-09-27

- 03843ac Introducing some load CTs for the beasthttp component
- b08c075 Introducing basic beasthttp CT infrastructure
- 7997a68 Using wait_threads, fixing cppcheck warnings
- 1a78d8c Introducing the logs into the beasthttp component
- f2b2699 Refining handler threads in the HttpController
- 0358e46 Introducing the PlantUML app component diagram into the READMEs
- d7fef68 Applied code formatting
- c49f0e1 Fixing app CTs
- 6776a19 Enabling GTest during for CTs
- f77b3c2 Pointing Jenkins configurable port into standart in-container 8080
- 4a24e40 Making the Jenkins pipeline container and image names configurable
- 69ecc5d Introducing basic app CTs samples
- b897797 Introducing basic SimpleLogger CTs with CMake and Jenkins integration
- a9ac652 Refining the branches link in the READMEs, introducing gitlab links also
- 49120f9 Specifying the Jenkins container run target in the READMEs
- 1a60566 Refining Jenkinsfile branch name on checkout
- 31619a4 Introducing basic Jenkins pipeline CMake target and Jenkinsfile conf
- 4e3e1e6 Fixing typo in the README.md
- 2935bfe Introducing the valgrind callgrind profiler target for the project
- 60c7d30 Introducing the gprof profiling target
- 4607be4 Adding money emoji to donation notice in the READMEs
- bed21cc Introducing the appCURL branch info into the READMEs
- 17b0131 Introducing the enabling libcurl section into the READMEs
- dee2e38 Introducing the libcurl cmake enabler script
- c99801f Moving the DEFAULT_LOG_FILE_PATH macro declaration into severity-macro-consts.h
- 55fde5b Refining unit tests to match the new log code
- a0093f3 Introducing a custom log file cmd param for the executable
- 1cea3d1 Introducing the DEFAULT_LOG_FILE_PATH cmake var and cpp macro to specify default dst log file location
- 9d74f26 Introducing the CMDParamNames class to encapsulate CMD params names
- 31fb5aa Introducing some marketing sentences in the README's goal section
- fa474f2 Introducing the cmake/enablers subdirectory to locate the 3rd-party dependencies
- da9f1dc Renaming template-project-make-GTest-available - template-project-GTest-enabler
- a8c5787 Introducing the NLohmann JSON library enabler cmake module
- d8e0ada Fixing the sanitizers cmake file in the READMEs
- 45133e5 Avoiding unnecessary badly portable localtime_r usage
- ac4e831 Introducing the thread id into simple logger
- 3dbdb91 Avoiding backward time in the simple logs
- 6a3bba8 Avoiding final log multiple str fetches
- b7de59d Refining the log current timestamp method, increasing thread safety
- dc9ca3c Introducing the CMake configurable log severity messages compilation switch
- 7ee9080 Introducing the appBoostLog branch info into the READMEs
- 63dd2d6 Hiding the compile options cmake files under separate directory
- db1a50f Enhancing sanitizers combinations and new cmake dir for ones
- 02147b5 Introducing the sanitizers enabling info into the READMEs
- b8f0384 Removing redundant cmake traces messages
- a4236a0 Introducing the GCC compiler sanitizers
- f8b4c16 Applied code formatting
- 2c1d94a Making the listen port confugurable through the CMake
- a7b21ab Refined issues in the Docker READMEs doc
- 3d79462 Separating the Docker single container build and run targets
- 75c7da9 Refining the Docker target for boost.beast with UTs
- 9024b40 Introducing the boost libs dependency for the Dockerfile
- 4407ba3 Introducing the Docker single run container target.
- 275b683 Adding project neatness to the READMEs
- 96e861d Introducing the appLog4Cpp5 branch info into the READMEs
- 26bcb53 Enabling multithreading in the flatpak boost build
- 18fe6c2 Implementing the logging macros and a simple logger to perform log messaging
- 61be0ad Introducing the appMongoDBCpp4 branch info into the READMEs
- ca65084 Specifying libboost-all-dev as dependency for the deb package
- ba54418 Making the flatpak source json conf file configurable during cmake conf stage
- 648f432 Refining the platform and SDK versions for the flatpak in the READMEs install sections
- 03eacee Allowing the network share for the dst flatpak package
- fcb0697 Refining the deb cmake info for cpack
- 3858373 Introducing the appSQLiteCpp3 branch info into the READMEs
- a25512d Refining the ApplicationContext mock
- 66a0c3a Refining flatpak url starter in the READMEs
- c985232 Introducing the gitlab mirror into the READMEs
- 51b0d95 Refining the flatpak target
- cb4c5bb cppcheck warnings code refine
- 2cc8a70 Introducing misc/.cppcheck-suppress file to list cppcheck suppressions of the false positives
- cddbb06 Refining the Application class UTs.
- b5ba157 Introducing the HttpController mock for the Application class UTs
- 90cb7d9 Introducing the documentation comments into beasthttp component's code.
- cc75dbb Introducing boost libs into the requirements
- 354f372 Extending the PageBuilder for the default page building routines
- 4403a10 Introducing the appMySQLCppConn branch info into the READMEs
- eae75cc Introducing the donation notice into the READMEs
- d1dd4d5 Introducing new component for request response builder
- 1376a1e Moving the request reading routines to the DefaultHandler class
- ce0aeda Moving the socket shutdown command to HTTPSessionContext class destructor
- af54b5b Introducing the guarding if statements into ResponseWriter
- afcb916 Extracting and introducing the ResponseWriter class
- 07d9bfb Extracting and introducing the ResponseBuilder class
- 3213101 Wrapping the request read call into try-catch
- 056ab0a Extracting the HTTP request reading class into RequestReader
- 0b719aa Extracting the http session context creation routine
- c4e7ef5 Declaring and decomposing the http request handling into a new separate component
- b0de856 Erasing redundant CMake include variable
- 1c246f1 Marking the connection as close
- cf9471a Marking appBoostBeast branch as a current one
- 1e49937 Introducing the appBoostBeast branch info into the READMEs
- fc09df7 introducing the basic http listener infrastructure with HttpController
- 7ec125a Explicitly specifying the combining of the template branches
- c793831 introducing the appPgSQLxx branch into the READMEs
- 59a3f26 Introducing a new appWt4 branch info into the READMEs
- ae60d2a Introducing the error exit code for a cppcheck target
- 38256c1 Refining the cppcheck target
- 9bf6620 Introducing the appMeson branch info into the READMEs
- 97a6442 Refining READMEs
- 05af0e5 Refining branches info
- c8de777 Introducing the flatpak sections into the READMEs
- 69ffe40 Introducing the flatpak package creation from the template source.
- 4b00b9f Inserting the release tag link
- 8bd91be Incrementing version to 0.9.0

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

[appBoostBeast0.11.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/appBoostBeast0.11.0)
[appBoostBeast0.10.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/appBoostBeast0.10.0)
[appBoostBeast0.9.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/appBoostBeast0.9.0)
[app0.8.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.8.0)
[app0.7.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.7.0)
[app0.6.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.6.0)
[app0.5.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.5.0)
[app0.4.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.4.0)
[app0.3.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.3.0)
[app0.2.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.2.0)
[v0.1.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/v0.1.0)
