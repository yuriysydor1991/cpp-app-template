# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [appFirebird0.10.0] - 2026-11-08

- 3b7ee88 Removing the destination OS from the AppImage package name
- 59eca43 Introducing the STT branches info into the READMEs
- e415c77 Replacing the CMAKE_SOURCE_DIR/CMAKE_BINARY_DIR by the PROJECT_SOURCE_DIR/PROJECT_BINARY_DIR
- 1c49dc7 Introducing the appWebAssembly branch info into the READMEs
- 23ea7e6 Introducing the appLlamaCPP branch info into the READMEs
- 613632f Introducing the TTS branches info into the READMEs
- 03e593e Introducing the destination OS into the package names
- c63277e Synchronizing the template flavors list of the READMEs
- 19ef8f8 Refreshing the shared library cache after the from-source installs
- 18cb5b0 Failing the flavor CI test stages which match no tests
- 779cc89 Converting the flavor link calls of the project binary to the keyword signature
- efd0c26 Fixing the cppcheck findings of the new signals handler, tests and log mock
- 8e1cdeb Updating the app component diagram to the signals handlers design
- e94b066 Renumbering the custom command line parameters section numbered 4-6 twice
- 04c9272 Documenting the built in command line options and the usage errors
- 0aef8cf Testing the application with the real command line arguments
- 0a0ed3c Parsing the command line before the log file initialization
- 347513e Exiting with a failure status on the command line usage errors
- 723970c Fixing the missing option value raising the version flag instead of the help one
- 4cccf6f Fixing the CommandLineParser test assertions which could not fail
- 52ab40b Fixing the log mock LOG_INIT forwarding into the LOG_INIT_DEFAULTS mock
- 20e3b35 Restoring the previous signal dispositions on the signals handler uninstall
- 0335edc Leaving the SIGTTIN and SIGTTOU signals to the shell job control
- d1f83b1 Removing the nonexistent module path directories and cppcheck suppression
- 9b4acbd Fixing the zlib gzip file example ignoring the read and close errors
- ca47272 Fixing the flatpak requirements section naming an outdated SDK version
- 996ea25 Documenting the ENABLE_COMPONENT_TESTS option of the test builds
- 31db878 Listing every linked doc section in the requirements and build index pages
- 4455884 Fixing the documentation links pointing into the other language
- b31e3cf Fixing the stale file paths named in the documentation
- 7c4b579 Fixing the snap command path ignoring the install prefix
- 6434d80 Fixing the documentation install which needed a manual Doxygen-doc build
- 2ec1a8b Skipping the Doxygen and callgrind targets when their tools are missing
- 94ae14f Installing the packager tools into the Jenkins pipeline image
- 07c4cdf Replacing the libjpeg-turbo download fallback with a clear configure error
- ad4c910 Fixing the libavif download fallback stopping without the system libyuv
- 6cb7012 Pinning the third-party download fallbacks to their release tags
- 2b3dea5 Failing the CI test stages which match no tests
- e438b2b Replacing the broken OpenSSL download fallback with a clear configure error
- acf5154 Fixing the mixed target_link_libraries signatures on the project binary
- 5bfb48a Fixing the MAX_LOG_LEVEL option help text error level value
- 26b481e Fixing the logger level filter tests which could not fail
- 0c6ecda Fixing the log macros to expand into single statements
- 4833140 Fixing the logger data races on the log file reopening and the level
- 20c3ded Fixing the log file open failure aborting the process
- 10e56bd Splitting the CTEST_DefaultLogger helper classes into own files
- 40f08fe Splitting the packages install scripts per OS release
- 9f2bd32 Adding the missing semicolon of the log macro call
- 6e61400 Naming the Firebird server package that matches the client version
- 9b1b929 Introducing the Firebird connection settings override through the environment
- 79e3e7d Fixing the configure with the Firebird client disabled
- 304eefc Rolling back the Firebird transaction after a failed query execution
- f2dd246 Rejecting the Firebird DPB values longer than 255 bytes
- db9b936 Moving the Firebird test helper classes into their own mock headers
- 8cf7bcf Moving the Firebird native handles out of the nested FbClient struct
- b5e06dc Breaking the shared_ptr cycle between the context and the DB connection
- c967c94 Renumbering the branch requirements doc into the free 3-13 section
- 8b35be4 Removing the duplicate using-directive from the CTEST_app
- a979198 Synchronizing the get_stop assertions and the CommandLineParser doc comment with app
- 8969e2b Replacing the unreachable GNU gettext site link with its Savannah page
- 6ffe819 Introducing the destination CPU architecture into the package names
- d184710 Introducing the appGettext branch info into the READMEs
- 5386515 Introducing the appDarknetXX branch info into the READMEs
- 4e4deb3 Introducing the RedHat packages install script
- 4b84282 Introducing the appWhisperCPP branch info into the READMEs
- 1ae7b52 Introducing the FreeBSD packages install script
- 994144a Introducing the appV8 branch info into the READMEs
- e3b349b Building the Firebird client from its sources when the system lacks it
- 1135bd9 Repairing the appFirebird pipeline cppcheck stage
- 4d71bec Erasing the build sources and trees of the docker images
- d4c71f1 Introducing the debug clang-format script
- 26a751a Resetting the inherited signals dispositions in the signals handlers tests
- 6b36053 Introducing the binary hardening options section into the READMEs
- 63dd4f6 Introducing the binary hardening compile and link options
- 5ba4169 Introducing the GitLab CI/CD pipeline section into the READMEs
- b0631ae Introducing the GitLab CI/CD pipeline mirroring the Jenkinsfile
- d61fab4 Introducing the GitHub Actions CI pipeline section into the READMEs
- cdb4ac5 Introducing the GitHub Actions CI pipeline mirroring the Jenkinsfile
- 48e933d Correcting the appQt6QtDBusClient branch description in the READMEs
- dbbc09c Introducing the desktop application packaging switch
- 7314295 Limiting the documentation checks to the repository own markdown files
- 9f1ba12 Excluding the GCC own include directories from the clang-tidy search path
- 02e5b07 Accepting the 405 documentation URLs
- 71a31f3 Applying the clang-format to the test sources
- 3f2b75d Spacing out the branch entries in the READMEs
- 7aea46b Rewording the DOCKER_HOST environment requirement in the docker docs
- 1c6c34f Removing the DOCKER_HOST variables from the docker enablers
- 9fcb535 Excluding the build trees from the Docker build context
- f0d6733 Retrying the unreachable documentation URLs and accepting the 403 ones
- d2ec8a1 Introducing the --rebuild flag into the Jenkins docker scripts
- e9934a5 Rebuilding the image from its base on the Jenkins pipeline force rebuild
- 92f01e6 Introducing the audio assets branches info into the READMEs
- ce1f0ad Splitting the signals handlers per category and covering the pause, reload, user defined and ignored signals
- c8adf5e Introducing the app signals handlers subcomponent
- d873e77 Declaring the main function argv parameter as an array
- 2f6df1f Moving the packagers templates into the per-packager directories
- 3a74331 Dropping the packagers and the development tools from the packages install list
- 70b7989 The destination CPU architecture of the AppImage package name
- 451a7a1 Picking the CPack AppImage enabler since the CMake 4.2 and dropping the debug banners
- c7ef869 Extracting the AppImage enabler pick into its own general enabler
- bd80bd8 Selecting the AppImage packager enabler by the CMake version
- 5a9119a Introducing the CPack based AppImage packager enabler
- eed305f Introducing the AppImage packager
- b2ad974 Introducing the --install flag into the packager build scripts
- 140e805 Renaming the packages install script and adding the Ubuntu one
- 8142efc Introducing the target architecture into the flatpak package name
- 4fe9c1d Introducing the AppStream metainfo file into the flatpak package
- b093f80 Consuming the install directory variables the flatpak-builder passes
- d1fd48b Introducing the required packages install script
- c400f8c Installing the flatpak build dependencies from the flathub remote
- e2e6cf7 Repairing the flatpak package generation
- 97c1c40 Dropping the redundant build step from the packager scripts
- 360f923 Introducing the per packager build scripts
- fe39e66 Introducing the appCFITSIO branch info into the READMEs
- 4ad42a8 Make the compile time log level gate really gate
- b0edd24 Introducing the appGtkmm4Libadwaita branch info into the READMEs
- 89814a1 Pinning the log message stream to the classic locale
- 5e478c7 Decomposing the IApplication descendants into the applications subcomponent
- ffc2df6 Introducing the appFontAwesome branch info into the READMEs
- 05b15d2 Introducing the debug test script and its --test parameter
- cedac5e Incrementing version to appFirebird0.10.0
- 571dd69 Release appFirebird0.9.0 at 2026-08-17

## [appFirebird0.9.0] - 2026-08-17

- 672a1c4 Introducing the InsertNewlineAtEOF clang-format option
- 57476f1 Repairing the mismatched ApplicationContext forward declaration tag
- f5c681a Introducing the appCURLChatGPT branch info into the READMEs
- f7d594f Hiding the ApplicationContext fields and adding the atomic stop flag
- 00b3bf9 Moving the linker hardening options out of the compile options
- 5426057 Split the DefaultLogger into a static proxy and a real logger instance
- d8bb34b Introducing the appCURLClaude branch info into the READMEs
- cee3846 Introducing the external documentation URLs check into the Jenkins pipeline
- 12c8cf6 Correcting the docker modules path of the documentation
- ad4c8ef Introducing the quick build and the docker starter scripts
- 49168af Introducing the quick build and the docker starter scripts
- 00253f9 Making the docker containers run under unprivileged users
- 12588f2 Repairing the appFirebird pipeline build and unit test stages
- 7f86488 Formatting the sources with the clang-format
- 5e25e9d Repairing the pipeline code check stages
- 1273de3 Introducing the appPGPLOT branch info into the READMEs
- 75d4573 Fixing the Jenkinsfile
- 73d2f5d Fix broken cppcheck link in section 5 index
- 9814ce7 Fix Groovy escape sequences in markdown link checker stage
- 6664184 Rework markdown link checker stage to pure bash
- 48a733f Add Jenkinsfile stage to detect broken markdown links; fix pre-existing broken links
- 87f69b3 Reorganize doc/sections into section dirs with category grouping
- 9115e81 Add an OpenSSL cmake enabler module with SHA-256, HMAC-SHA256 and HTTPS/TLS client code samples
- dee3332 Register the missing tests in the misc/Jenkinsfile
- 4847598 Group the enabler documentation under subsections in the READMEs
- ef177ea Group the compression branches under a dedicated README section
- dae89d9 Fix the misc/Jenkinsfile checkout branch to the appFirebird branch name
- eaf90fe Introducing the appLZMA branch info into the READMEs
- d4176e4 Add a liblzma (XZ Utils) compression library enabler module
- 733610c Introducing the appZlib branch info into the READMEs
- d864d0e Add zlib compression usage examples to its enabler documentation
- 1bf64cf Replace the redundant PROJECT_NAME CMake variable with CMAKE_PROJECT_NAME
- 3bd0370 Introducing the appGtkmm4Vulkan branch info into the READMEs
- 67f754a Removing the appGtkmm4Vulkan branch info from the READMEs
- ceb5e3e Introducing the appQt6Vulkan and appGtkmm4Vulkan branches info into the READMEs
- ba336a8 Simplifying root CMakeLists.txt
- db24ec9 Introducing the appGtkmm4GDBusClient branch info into the READMEs
- 7aeec2e Introducing the appQt6GLArea branch info into the READMEs
- 53ae5a8 Introducing the appGtkmm4GLArea branch info into the READMEs
- 13d0b8c Splitting the Data Visualization README category into Plots/Graphs and Maps
- 6fbbf81 Introducing the applibMeson branch info into the READMEs
- 95586c0 Introducing the zlib and image format cmake enablers with docs
- 624bb1e Introducing the appSFML branch info into the READMEs
- a872b53 Introducing the appwxWidgets branch info into the READMEs
- 7a72838 Introducing the appQt6QtDBusClient branch info into the READMEs
- 01a355b Introducing the appQt6QtLocation branch info into the READMEs
- 945dfec Introducing the appQt6ChartView branch into the READMEs
- 65174be Migrating the Firebird enabler to template_project_default_3rdparty_enabler
- b5f4700 Introducing the appGtkmm4LeafLet and appQt6LeafLet branches info into the READMEs
- a78da94 Introducing the COMPONENTS arg for template_project_default_3rdparty_enabler
- db15e0a Removing the SDL3 current marking
- bdecf0c Introducing information about the SDL3 branch in the READMEs
- 2d2b592 Replacing faulty SimpleLogger mention with the DefaultLogger
- cf4ea96 Rename the simple logger to DefaultLogger and add top-level log.h tests
- 33f0ca9 Removing faulty simple_logger mention in the log.h
- 4506d42 Add template-specific packager, documentation and registration checks
- ac60f8f Introducing the appSDBusCxxClient and appSDBusCxxServer branches info into the READMEs
- e3f51fe Moving Dockerfiles and packagers files into separate subdirs in the misc
- 844650d Adding .claude dir to .gitignore
- aa20997 Introducing project structure section Будь ласка, зверніться до адміністратора subsection
- b2d83de Implementing the appFirebird branch for the Firebird DBMS usage
- a668bc3 Introducing the libMeson branch info into the READMEs
- a5d58fa Introducing info about newly created branch appOpenCV into READMEs with it's cmake enabler.
- 188f328 Introducing the CPack's RPM package generator integration
- 3853630 Removing unmerged lines in the doc/README.uk_UA.md
- 6afe3c9 Introducing the MS Windows WIX package generation through CPack integration
- 1549df1 Introducing the project's FreeBSD pkg package generation support through CPack. Works only on FreeBSD.
- c244cb9 Deleting REQUIRED marking from the snapcraft's find_program
- d7d0131 By default disabling the snap package manager
- 8db3c88 Introducing the snap packager integration with documentation
- b866745 Introducing and migrating to the template_project_default_3rdparty_enabler cmake function. Making enablers git sources variables modifiable.
- 5c3efa0 Moving all CMake variables declarations into their respectful enablers.
- e026962 Moving Doxygen related CMake variables into doc/CMakeLists.txt file
- 39248c1 Introducing the libxml2 enabler cmake module
- f132fa2 Enhancing the cmake files fs structure
- 96ce4c3 Making docker base image configurable through CMake variables
- b7043a1 Introducing the appPLplot branch info into the READMEs
- f4a3237 Introducing the MatPlot++ appMatPlotxx branch into the READMEs
- ae89240 Making the cppcheck stage optional due to unstable results
- a7eb16c Fixing clang-tidy conf misspell
- 07bd0f3 Switching off the clang-tydy's unrecognizable AnalyzeTemporaryDtors config param
- a329b88 Loggging README's misspell refine
- d749e7f Grouping and categorising available template flavors links in the READMEs
- e70395d Renaming properly Nlohmann JSON library CMake enabler file
- 26aed3c Introducing the forgottent Nlohmann JSON library enabler info into the READMEs
- fef67db Decomposing READMEs
- f567e2e Introducing the ENABLE_LOGS_MICROSECONDS_TIME CMake option in order to be able to disable microseconds in the log messages.
- d8a66c5  Introducing the --branch cmd line flag for git clone command in the READMEs
- 992a2fc Introducing explicit template altering notice in the READMEs headers
- c09448a Optimizing some CMake commands in the README.md
- ae42c86 Introducing the appGtkmm4 branch info into the READMEs
- 1dcddaa Introducing the PlantUML app component diagram into the READMEs
- 5ed2544 Fixing CTEST_app
- 41de200 Enabling GTest during for CTs
- 62de971 Pointing Jenkins configurable port into standart in-container 8080
- dfb60d0 Making the Jenkins pipeline container and image names configurable
- 2513770 Introducing basic app CTs samples
- e93285e Introducing basic SimpleLogger CTs with CMake and Jenkins integration
- 03c31f7 Refining the branches link in the READMEs, introducing gitlab links also
- c063692 Specifying the Jenkins container run target in the READMEs
- 20d91ed Introducing basic Jenkins pipeline CMake target and Jenkinsfile conf
- 53962e1 Fixing typo in the README.md
- 22de6e5 Introducing the valgrind callgrind profiler target for the project
- c304cca Introducing the gprof profiling target
- ae2d21a Adding money emoji to donation notice in the READMEs
- d507ac7 Introducing the appCURL branch info into the READMEs
- 263a236 Introducing the enabling libcurl section into the READMEs
- beb758f Introducing the libcurl cmake enabler script
- 2ed22ca Moving the DEFAULT_LOG_FILE_PATH macro declaration into severity-macro-consts.h
- 0fb57dc Refining unit tests to match the new log code
- 39dc4e6 Introducing a custom log file cmd param for the executable
- 6039ad3 Introducing the DEFAULT_LOG_FILE_PATH cmake var and cpp macro to specify default dst log file location
- af2ca14 Introducing the CMDParamNames class to encapsulate CMD params names
- a509cfc Introducing some marketing sentences in the README's goal section
- 548af11 Introducing the cmake/enablers subdirectory to locate the 3rd-party dependencies
- 2b03a72 Renaming emplate-project-make-GTest-available - template-project-GTest-enabler
- 11985b0 Introducing the NLohmann JSON library enabler cmake module
- 5aef4be Fixing the sanitizers cmake file in the READMEs
- 584ed97 Avoiding unnecessary badly portable localtime_r usage
- 893cc98 Introducing the thread id into simple logger
- 03435c2 Avoiding backward time in the simple logs
- 84ba67e Avoiding final log multiple str fetches
- 3841300 Refining the log current timestamp method, increasing thread safety
- a3d6fd4 Introducing the CMake configurable log severity messages compilation switch
- e6b4cb6 Introducing the appBoostLog branch info into the READMEs
- 1475fcf Hiding the compile options cmake files under separate directory
- 28552e8 Enhancing sanitizers combinations and new cmake dir for ones
- 5929af7 Introducing the sanitizers enabling info into the READMEs
- f4e8dc9 Removing redundant cmake traces messages
- 692dd55 Introducing the GCC compiler sanitizers
- 7ce82af Refined issues in the Docker READMEs doc
- ac2fbe3 Refining the Docker target for the PQxx
- bb314c9 Separating the Docker single container build and run targets
- 79c300b Introducing the Docker single run container target.
- 8bc5ff1 Adding project neatness to the READMEs
- d438fbe Introducing the appLog4Cpp5 branch info into the READMEs
- f422d19 Implementing the logging macros and a simple logger to perform log messaging
- 145efd5 Introducing the appMongoDBCpp4 branch info into the READMEs
- aa68fba Applying the code formatting
- 6c032c9 Fixing the cppcheck code warnings
- 7cc3170 Making the flatpak source json conf file configurable during cmake conf stage
- 7c89e74 Introducing the libpqxx dependency into the deb cpack variables
- fbab3a3 Introducing the PostgreSQL requirements into the READMEs
- 36f0750 Refining the deb cmake info for cpack
- 17641db Introducing the appSQLiteCpp3 branch info into the READMEs
- bfbfdc2 Repair Application UT
- 2c6ff1c Refined flatpak package json configuration
- a98541a Refining the ApplicationContext mock
- 308a00d Introducing the gitlab mirror into the READMEs
- 3be4795 Introducing the appMySQLCppConn branch info into the READMEs
- 619ba64 Introducing the donation notice into the READMEs
- e9700b2 Introducing the appBoostBeast branch info into the READMEs
- 57fecee Explicitly specifying the combining of the template branches
- 64a6efd Applying clang-format
- dc81237 Decomposing PgSQL internal objects creation
- ef447ae Refining Application class UTs to be compilable
- 486a339 Avoiding struct->class warning of clang-tidy
- c0e05d7 Marking the appPgSQLxx branch as current in the READMEs
- 446aa41 introducing the appPgSQLxx branch into the READMEs
- 0b3a78f Introducing the PostgreSQL initial infrastructure
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
- dfff631 Release app0.8.0 2025-03-20

## [app0.8.0] - 2025-03-20

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

[appFirebird0.10.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/appFirebird0.10.0)
[appFirebird0.9.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/appFirebird0.9.0)
[app0.8.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.8.0)
[app0.7.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.7.0)
[app0.6.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.6.0)
[app0.5.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.5.0)
[app0.4.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.4.0)
[app0.3.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.3.0)
[app0.2.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.2.0)
[v0.1.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/v0.1.0)
