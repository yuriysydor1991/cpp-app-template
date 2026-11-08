# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [appGtkmm4LeafLet0.12.0] - 2026-11-08

- 87e5a55 Removing the destination OS from the AppImage package name
- df53e03 Introducing the STT branches info into the READMEs
- 8efdda7 Replacing the CMAKE_SOURCE_DIR/CMAKE_BINARY_DIR by the PROJECT_SOURCE_DIR/PROJECT_BINARY_DIR
- 4730d67 Introducing the appWebAssembly branch info into the READMEs
- 1a0fb74 Introducing the appLlamaCPP branch info into the READMEs
- 4285490 Introducing the TTS branches info into the READMEs
- 8443a9c Introducing the destination OS into the package names
- 96611df Fixing the branch name of the cloning commands in the docs
- 062038b Synchronizing the template flavors list of the READMEs
- 2b95267 Refreshing the shared library cache after the from-source installs
- d6a661a Failing the flavor CI test stages which match no tests
- c0995d2 Converting the flavor link calls of the project binary to the keyword signature
- a992c4c Fixing the cppcheck findings of the new signals handler, tests and log mock
- 12f962f Updating the app component diagram to the signals handlers design
- b2292ee Renumbering the custom command line parameters section numbered 4-6 twice
- 820a157 Documenting the built in command line options and the usage errors
- bdcf5e0 Testing the application with the real command line arguments
- 47111e9 Parsing the command line before the log file initialization
- a68628f Exiting with a failure status on the command line usage errors
- 70757a1 Fixing the missing option value raising the version flag instead of the help one
- e376cb9 Fixing the CommandLineParser test assertions which could not fail
- 7d57351 Fixing the log mock LOG_INIT forwarding into the LOG_INIT_DEFAULTS mock
- 04f5d26 Restoring the previous signal dispositions on the signals handler uninstall
- b9e7b53 Leaving the SIGTTIN and SIGTTOU signals to the shell job control
- 6fef59c Removing the nonexistent module path directories and cppcheck suppression
- d36baef Fixing the zlib gzip file example ignoring the read and close errors
- e3d6e22 Fixing the flatpak requirements section naming an outdated SDK version
- 7ccc589 Documenting the ENABLE_COMPONENT_TESTS option of the test builds
- bc03d85 Listing every linked doc section in the requirements and build index pages
- c72099f Fixing the documentation links pointing into the other language
- 95c466f Fixing the stale file paths named in the documentation
- db4bfb4 Fixing the snap command path ignoring the install prefix
- 4e63796 Fixing the documentation install which needed a manual Doxygen-doc build
- 6b2f896 Skipping the Doxygen and callgrind targets when their tools are missing
- a39e9d9 Installing the packager tools into the Jenkins pipeline image
- 7b903a1 Replacing the libjpeg-turbo download fallback with a clear configure error
- 3920d9a Fixing the libavif download fallback stopping without the system libyuv
- ae0d8c3 Pinning the third-party download fallbacks to their release tags
- f0ac479 Failing the CI test stages which match no tests
- a025b59 Fixing the Jenkins doc sections linked check skipping the section directories
- 093e97f Replacing the broken OpenSSL download fallback with a clear configure error
- f251597 Fixing the mixed target_link_libraries signatures on the project binary
- 55b66bb Fixing the MAX_LOG_LEVEL option help text error level value
- 95a4317 Fixing the logger level filter tests which could not fail
- dd612af Fixing the log macros to expand into single statements
- 1c5cd52 Fixing the logger data races on the log file reopening and the level
- f710728 Fixing the log file open failure aborting the process
- 7cdaedd Splitting the CTEST_DefaultLogger helper classes into own files
- abe4338 Splitting the packages install scripts per OS release
- 79eca96 Introducing the Map component test of the bundled Leaflet page
- b1740a5 Removing the unused logo and stylesheet from the map branch GResource bundle
- ce9262a Pinning the Leaflet CDN files of the map page with the integrity hashes
- 2c23536 Declaring the WebKitGTK dependency of the deb and snap packages
- ded0a76 Installing the WebKitGTK development package into the Jenkins pipeline image
- 136cb12 Fixing the cppcheck findings of the GTK branch sources
- 7185910 Restoring the stop flag assertions of the Application unit test
- 0cb107a Dropping the executable bit of the logo image
- 68f8464 Naming the existing GResource template in the resource embedding docs
- 9988c0c Revoking the X server access on every exit of the docker single run
- dd82a4a Removing the dead code of the GTK main window and controller
- 63e6576 Indexing the toolkit messages section in the project structure page
- d88c762 Guarding the clang-tidy build stage with the RUN_CLANGTIDY parameter
- 85dc0d7 Declaring the snap build and stage packages of the toolkit
- b017b93 Dropping the Glade from the GTK4 branch requirements
- ac96694 Regenerating the GResource source on the listed resource files change
- ca5173a Quitting the GTK application main loop on the raised stop flag
- 23e01f1 Handing the program name alone to the GTK application
- 5a55abb Synchronizing the drifted docker and cppcheck enablers with the app branch
- 2da8e84 Hiding the ApplicationContext fields and adding the atomic stop flag
- e5ba41a Replacing int flag with a bool for the CommandLineParser
- be6567c Supressing the cppcheck's missingIncludeSystem and unusedStructMember warnings.
- 74659c6 Renaming the GtkmmIniter component into the Gtkmm4Controller
- 43ecf40 Replacing the unreachable GNU gettext site link with its Savannah page
- e9f57cb Introducing the destination CPU architecture into the package names
- 4e0f546 Introducing the appGettext branch info into the READMEs
- b8d6cbc Introducing the appDarknetXX branch info into the READMEs
- d23e807 Introducing the RedHat packages install script
- 5f5639b Introducing the appWhisperCPP branch info into the READMEs
- c07d5c5 Introducing the FreeBSD packages install script
- f5d7ac7 Introducing the appV8 branch info into the READMEs
- c046c3b Erasing the build sources and trees of the docker images
- 84d89b0 Introducing the debug clang-format script
- a8cd2c0 Resetting the inherited signals dispositions in the signals handlers tests
- e3fa486 Introducing the binary hardening options section into the READMEs
- e2b6522 Introducing the binary hardening compile and link options
- 446f3d9 Introducing the GitLab CI/CD pipeline section into the READMEs
- 172b902 Introducing the GitLab CI/CD pipeline mirroring the Jenkinsfile
- 0831d93 Introducing the GitHub Actions CI pipeline section into the READMEs
- 741b8cd Introducing the GitHub Actions CI pipeline mirroring the Jenkinsfile
- abaf7ab Correcting the appQt6QtDBusClient branch description in the READMEs
- 6306d28 Introducing the desktop application packaging switch
- 699bb9c Limiting the documentation checks to the repository own markdown files
- 280fe2d Excluding the GCC own include directories from the clang-tidy search path
- 8be32c3 Accepting the 405 documentation URLs
- 2c623b4 Spacing out the branch entries in the READMEs
- 8f41aaa Rewording the DOCKER_HOST environment requirement in the docker docs
- 8236173 Removing the DOCKER_HOST variables from the docker enablers
- 2635788 Escaping the shell environment variables of the docker run command
- 127a960 Installing the webkitgtk development package in the Docker image
- d195bd2 Excluding the build trees from the Docker build context
- 90f1a68 Retrying the unreachable documentation URLs and accepting the 403 ones
- 60106a6 Introducing the --rebuild flag into the Jenkins docker scripts
- b3d717d Rebuilding the image from its base on the Jenkins pipeline force rebuild
- 1144e4e Introducing the audio assets branches info into the READMEs
- 33b9416 Splitting the signals handlers per category and covering the pause, reload, user defined and ignored signals
- 52b8f64 Introducing the app signals handlers subcomponent
- 7fcf12e Declaring the main function argv parameter as an array
- d5609e4 Moving the packagers templates into the per-packager directories
- 99ec0c3 Dropping the packagers and the development tools from the packages install list
- 3b9c256 The destination CPU architecture of the AppImage package name
- 1ca0d6b Picking the CPack AppImage enabler since the CMake 4.2 and dropping the debug banners
- a566fef Extracting the AppImage enabler pick into its own general enabler
- 1c0fc68 Selecting the AppImage packager enabler by the CMake version
- 28f4e81 Introducing the CPack based AppImage packager enabler
- 03ac9de Introducing the AppImage packager
- 4e11fba Introducing the --install flag into the packager build scripts
- dd2521f Renaming the packages install script and adding the Ubuntu one
- b0085ca Introducing the target architecture into the flatpak package name
- cd21fa8 Introducing the AppStream metainfo file into the flatpak package
- 62406d4 Consuming the install directory variables the flatpak-builder passes
- 505bb2a Introducing the required packages install script
- ed49227 Force cleaning the previous flatpak build directory
- 8a591d3 Sharing the network with the flatpak packaged application
- 31cc7f1 Configuring the flatpak host build tree without the gtkmm4 stack
- f2adedb Installing the flatpak build dependencies from the flathub remote
- 4e71699 Pointing the flatpak packager requirements to the GNOME 49 runtime
- 2936502 Building the flatpak gtkmm4 stack from the release tarballs on the GNOME 49 runtime
- 0f31ea9 Dropping the redundant build step from the packager scripts
- ea4243e Introducing the per packager build scripts
- c32c383 Introducing the appCFITSIO branch info into the READMEs
- b53aa15 Log every toolkit message through the application log
- d864747 Make the compile time log level gate really gate
- d4358c1 Introducing the appGtkmm4Libadwaita branch info into the READMEs
- 6ff6034 Pinning the log message stream to the classic locale
- 5884fde Decomposing the IApplication descendants into the applications subcomponent
- 68b5ac3 Introducing the appFontAwesome branch info into the READMEs
- 9672310 Introducing the debug test script and its --test parameter
- ec07757 Incrementing version to appGtkmm4LeafLet0.12.0
- f15a787 Release appGtkmm4LeafLet0.11.0 at 2026-08-17

## [appGtkmm4LeafLet0.11.0] - 2026-08-17

- e6b9e8e Introducing the InsertNewlineAtEOF clang-format option
- 9ae22c9 Introducing the appCURLChatGPT branch info into the READMEs
- 3175f9a Hiding the ApplicationContext fields and adding the atomic stop flag
- ebc132e Moving the linker hardening options out of the compile options
- 8c3e111 Split the DefaultLogger into a static proxy and a real logger instance
- e20398f Introducing the appCURLClaude branch info into the READMEs
- da74a0e Introducing the external documentation URLs check into the Jenkins pipeline
- fb039b1 Correcting the docker modules path of the documentation
- b7f4eda Introducing the quick build and the docker starter scripts
- fb8cfe3 Introducing the quick build and the docker starter scripts
- 856ca6e Making the docker containers run under unprivileged users
- edbdb86 Formatting the sources with the clang-format
- c36e095 Repairing the pipeline code check stages
- cd1c2ad Introducing the appPGPLOT branch info into the READMEs
- c9c951a Fixing the Jenkinsfile
- 5674595 Fix broken cppcheck link in section 5 index
- 30b4e45 Fix Groovy escape sequences in markdown link checker stage
- 7c9bd31 Rework markdown link checker stage to pure bash
- 2ea9190 Add Jenkinsfile stage to detect broken markdown links; fix pre-existing broken links
- 54a99d7 Reorganize doc/sections into section dirs with category grouping
- e6c78c6 Add an OpenSSL cmake enabler module with SHA-256, HMAC-SHA256 and HTTPS/TLS client code samples
- fd7cc92 Group the enabler documentation under subsections in the READMEs
- abfad04 Group the compression branches under a dedicated README section
- 7498bfe Fix the misc/Jenkinsfile checkout branch to the appGtkmm4LeafLet branch name
- 4c14813 Introducing the appLZMA branch info into the READMEs
- 5124c49 Add a liblzma (XZ Utils) compression library enabler module
- 4e2e591 Introducing the appZlib branch info into the READMEs
- 3b2f9bf Add zlib compression usage examples to its enabler documentation
- edfdb6e Replace the redundant PROJECT_NAME CMake variable with CMAKE_PROJECT_NAME
- 0718254 Introducing the appGtkmm4Vulkan branch info into the READMEs
- d787f8f Removing the appGtkmm4Vulkan branch info from the READMEs
- 3dcaa2d Introducing the appQt6Vulkan and appGtkmm4Vulkan branches info into the READMEs
- 01e3a43 Simplifying root CMakeLists.txt
- 7a89aea Introducing the appFirebird branch info into the READMEs
- 7bd96c5 Introducing the appGtkmm4GDBusClient branch info into the READMEs
- 226f48e Introducing the appQt6GLArea branch info into the READMEs
- b972afa Introducing the appGtkmm4GLArea branch info into the READMEs
- 1c334e2 Splitting the Data Visualization README category into Plots/Graphs and Maps
- 8397e07 Introducing the applibMeson branch info into the READMEs
- d182f35 Introducing the zlib and image format cmake enablers with docs
- e4bde79 Introducing the appSFML branch info into the READMEs
- 1dd2cd3 Introducing the appwxWidgets branch info into the READMEs
- 618d78b Introducing the appQt6QtDBusClient branch info into the READMEs
- eb39432 Introducing the appQt6QtLocation branch info into the READMEs
- 5a6b601 Introducing the appQt6ChartView branch into the READMEs
- cd0385e Marking appGtkmm4LeafLet as a current branch
- 1b24e55 Introducing the appGtkmm4LeafLet and appQt6LeafLet branches info into the READMEs
- 16de22a Introducing the Leaflet map component instead of the welcome screen
- 78e6ffc Introducing the COMPONENTS arg for template_project_default_3rdparty_enabler
- 016a8fb Removing the SDL3 current marking
- 879e472 Introducing information about the SDL3 branch in the READMEs
- c27da5e Erasing redundant doc/sections/uk_UA/4-8-gtkmm3glade-ui-implementation.md
- 6ec5a5d Replacing faulty SimpleLogger mention with the DefaultLogger
- ea04c98 Rename the simple logger to DefaultLogger and add top-level log.h tests
- 4c2af86 Removing faulty simple_logger mention in the log.h
- 1b4fbe2 Add template-specific packager, documentation and registration checks
- 368440b Introducing the appSDBusCxxClient and appSDBusCxxServer branches info into the READMEs
- ba91cd4 Moving Dockerfiles and packagers files into separate subdirs in the misc
- 344ecb2 Adding .claude dir to .gitignore
- e6a89e5 Introducing project structure section Будь ласка, зверніться до адміністратора subsection
- 90d3b78 Introducing the libMeson branch info into the READMEs
- 900b783 Introducing info about newly created branch appOpenCV into READMEs with it's cmake enabler.
- ab535d2 Introducing the CPack's RPM package generator integration
- 64f6f07 Removing unmerged lines in the doc/README.uk_UA.md
- bae9b8b Introducing the MS Windows WIX package generation through CPack integration
- bf21f33 Introducing the project's FreeBSD pkg package generation support through CPack. Works only on FreeBSD.
- 676358f Deleting REQUIRED marking from the snapcraft's find_program
- 384991a By default disabling the snap package manager
- 74b5c39 Introducing the snap packager integration with documentation
- e0483bd Moving Gtkmm4 integration cmake code into separate cmake file. To enable it for possible multiple components of interest.
- 03877fd Introducing and migrating to the template_project_default_3rdparty_enabler cmake function. Making enablers git sources variables modifiable.
- 2b0191a Moving all CMake variables declarations into their respectful enablers.
- 3168919 Moving Doxygen related CMake variables into doc/CMakeLists.txt file
- 331c4d6 Introducing the libxml2 enabler cmake module
- f354231 Enhancing the cmake files fs structure
- e99338a Making docker base image configurable through CMake variables
- a3eaa88 Introducing the appPLplot branch info into the READMEs
- ff96226 Introducing the MatPlot++ appMatPlotxx branch into the READMEs
- 659b233 Making the clang-tidy Jenkinsfile stage optional for the pipeline
- 86e6c95 Making the cppcheck stage optional due to unstable results
- f736bcd Fixing clang-tidy conf misspell
- 23f820d Switching off the clang-tydy's unrecognizable AnalyzeTemporaryDtors config param
- f2ad201 Loggging README's misspell refine
- 294ff0a Introducing the PROJECT_REVERSE_URL CMake variable instead of unreachable FLATPAK_PROJECT_URL
- 4c9a324 Replacing GTK3 mentions in the GtkmmIniter class logging messages
- 0725299 Grouping and categorising available template flavors links in the READMEs
- 327295f Renaming properly Nlohmann JSON library CMake enabler file
- 0b56c71 Introducing the forgottent Nlohmann JSON library enabler info into the READMEs
- 004414b Decomposing READMEs
- 53b9643 Introducing the ENABLE_LOGS_MICROSECONDS_TIME CMake option in order to be able to disable microseconds in the log messages.
- 0743579  Introducing the --branch cmd line flag for git clone command in the READMEs
- 43572f1 Introducing explicit template altering notice in the READMEs headers
- 18a2963 Optimizing some CMake commands in the README.md
- 222ba50 Applied code formatting
- b9167f3 Fixing the GtkmmWindow bootstrap code
- 65f9671 Increasing the flatpak gtkmm version to 4.20.0
- eb4a1c2 Refining the flatpak app URLs
- 1588834 Making the template.gresource.xml file CMake-configurable template.gresource.xml.in
- 884a5e0 Marking the appGtkmm4 as a current branch in the READMEs
- aa29eec Introducing the appGtkmm4 branch info into the READMEs
- dc68316 Renaming the GTKmm UI component to gtkmm4 and refining the code as appropriate
- d9e7bff Incrementing version to 0.11.0
- ae14444 Release appGtkmm30.10.0 at 2025-09-29

## [appGtkmm30.10.0] - 2025-09-29

- 2540ec4 Integrating log into the GtkmmIniter, moving GtkmmWindow into separate sub component
- 2fe567d Introducing the PlantUML app component diagram into the READMEs
- 6f3e17f Fixing app CT
- 37a69c9 Enabling GTest during for CTs
- 38c15b7 Pointing Jenkins configurable port into standart in-container 8080
- f0e54d4 Making the Jenkins pipeline container and image names configurable
- 01e434f Introducing basic app CTs samples
- 7bbd727 Introducing basic SimpleLogger CTs with CMake and Jenkins integration
- 87e7ad7 Refining the branches link in the READMEs, introducing gitlab links also
- 3d40981 Specifying the Jenkins container run target in the READMEs
- c3f6e1a Introducing basic Jenkins pipeline CMake target and Jenkinsfile conf
- f96ee3a Fixing typo in the README.md
- 06d08ec Introducing the valgrind callgrind profiler target for the project
- fc72988 Introducing the gprof profiling target
- 269f60a Adding money emoji to donation notice in the READMEs
- 1e009d5 Introducing the appCURL branch info into the READMEs
- e4a8f03 Introducing the enabling libcurl section into the READMEs
- 295e92b Introducing the libcurl cmake enabler script
- 671bbaf Moving the DEFAULT_LOG_FILE_PATH macro declaration into severity-macro-consts.h
- 8db9bec Refining unit tests to match the new log code
- 58b3233 Introducing a custom log file cmd param for the executable
- 9c6fd78 Introducing the DEFAULT_LOG_FILE_PATH cmake var and cpp macro to specify default dst log file location
- eb47498 Introducing the CMDParamNames class to encapsulate CMD params names
- 8b1f92a Introducing some marketing sentences in the README's goal section
- 5c7da57 Introducing the cmake/enablers subdirectory to locate the 3rd-party dependencies
- 09730a4 Renaming emplate-project-make-GTest-available - template-project-GTest-enabler
- 26f69f7 Introducing the NLohmann JSON library enabler cmake module
- 0b43578 Refining the main header label size setup with CSS
- 1504eae Introducing the main CSS styling file with it's preload for the window
- 93b11c0 Renaming the templateGtkmm namespace into the Gtkmm4i
- c106a26 Refining the Application UTs
- 6d8ce25 Passing whole application context instance into the GtkmmIniter run method.
- 80d5c69 Fixing the sanitizers cmake file in the READMEs
- cb8dec0 Avoiding unnecessary badly portable localtime_r usage
- 176480e Introducing the thread id into simple logger
- 8f4ecbb Avoiding backward time in the simple logs
- 49660d0 Avoiding final log multiple str fetches
- e4c1c2e Refining the log current timestamp method, increasing thread safety
- aa52ff5 Introducing the CMake configurable log severity messages compilation switch
- 7f0e839 Introducing the appBoostLog branch info into the READMEs
- 90498c7 Hiding the compile options cmake files under separate directory
- 96a005a Enhancing sanitizers combinations and new cmake dir for ones
- fb0fc34 Introducing the sanitizers enabling info into the READMEs
- c30e2e2 Removing redundant cmake traces messages
- 6be468b Introducing the GCC compiler sanitizers
- fcba634 Incrementing version to appGtkmm30.10.0

## [appGtkmm30.9.0] - 2025-06-06

- 6a212b4 Release appGtkmm30.9.0 2025-06-06
- 3cf8cc7 Introducing misc/.cppcheck-suppress file to list cppcheck suppressions of the false positives
- 89e5b3a Refined issues in the Docker READMEs doc
- d30f685 Refining the Docker container target
- 958d3db Separating the Docker single container build and run targets
- 35f8741 Introducing the Docker single run container target.
- ba688e6 Adding project neatness to the READMEs
- 5b928e4 Introducing the appLog4Cpp5 branch info into the READMEs
- 414602b Implementing the logging macros and a simple logger to perform log messaging
- 5ecbac0 Introducing the appMongoDBCpp4 branch info into the READMEs
- ee66f27 Making the flatpak source json conf file configurable during cmake conf stage
- 6ffbbfa specifying the pkg-config tool as requirement for dev into hte READMEs
- 6274792 Inserting the libgtkmm-3.0-dev into deb dependencies
- 9c6fb84 Refining the deb cmake info for cpack
- e2adbed Refining the flatpak description in the READMEs
- f961e7d Fixing flatpak dbus connection issues
- 37a3bee Refining the flatpak target with json
- a8c60da Introducing the appSQLiteCpp3 branch info into the READMEs
- 508c4c1 Refining the ApplicationContext mock
- 8863765 Introducing the gitlab mirror into the READMEs
- 46ba4a1 Introducing the appMySQLCppConn branch info into the READMEs
- 8f4cda7 Introducing the appBoostBeast branch info into the READMEs
- f627e1b Explicitly specifying the combining of the template branches
- 5692eef introducing the appPgSQLxx branch into the READMEs
- c0a8a86 Introducing a new appWt4 branch info into the READMEs
- 7e3e099 Introducing the error exit code for a cppcheck target
- ee7a835 Refinining the cppcheck target
- 2af8ce5 Introducing the donation notice into the READMEs
- e23ddc8 Refining flatpak target
- dd90f39 Introducing the appMeson branch info into the READMEs
- c489f97 Refining the branch info
- f9156fb Flatpack adjust workflow
- a9c7d1c Introducing the flatpak sections into the READMEs
- eac4b5e Introducing the flatpak package creation from the template source.
- 8178e8a Erasing the /analyze from the default MSVC compile options
- 9cc1c83 Introducing the DEB package gen info in the READMEs
- 40d14f3 Introducing the cpack configuration for the deb package generation
- 5523a97 Introducing the LICENSE file with free of use license and notice
- 16cdb99 Introducing the appSDL2 branch into the READMEs
- ea5a3dd Introducing clang-tidy
- 4343ab0 Introducing the FreeGlut/OpenGL appFreeGlut branch info into READMEs
- 218a414 Introducing MSVC extra compile options for warnings
- 741acaf Adding MSVC settings file to the .gitignore
- 0f0714b Avoiding the compilation warnings at the UTEST_CommandLineParser
- 67cd1b3 Introducing MS Windows tools install description into READMEs
- ca0b1fc Adding the out directory for MSVC into .gitignore
- 3132d72 Incrementing version to 0.9.0
- 92f77a5 Release appGtkmm30.8.0 2025-03-17

## [appGtkmm30.8.0] - 2025-03-17

- d347ffb Incrementing version to 0.8.0
- 9403985 Mentioning the glib-compile-resources resource file in the READMEs
- 347d86f Moving a src/gtkmm to the src/gtkmm4
- cbfbb5d Introducing GResource compilation with glib-compile-resources and resource lib target
- 15da6a1 Removing annoying GTKmm vars traces
- 14426ff Specifying the appGtkmm3Glade branch in the READMEs

## [appGtkmm30.7.0] - 2025-03-16

- 0b67e70 Release appGtkmm30.7.0 2025-03-16
- 512bbd0 Refining the READMEs for the GTKmm
- c3bb27c Margin the appGtkmm3 branch as current in the READMEs
- 79d22dc Introducing the appGtkmm3 branch info into the READMEs
- 045a1a4 Refining the Application UTs.
- d2eee0c Applying clang-format
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

[appGtkmm4LeafLet0.12.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/appGtkmm4LeafLet0.12.0)
[appGtkmm4LeafLet0.11.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/appGtkmm4LeafLet0.11.0)
[appGtkmm30.10.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/appGtkmm30.10.0)
[appGtkmm30.9.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/appGtkmm30.9.0)
[appGtkmm30.8.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/appGtkmm30.8.0)
[appGtkmm30.7.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/appGtkmm30.7.0)
[app0.6.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.6.0)
[app0.5.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.5.0)
[app0.4.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.4.0)
[app0.3.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.3.0)
[app0.2.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.2.0)
[v0.1.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/v0.1.0)
