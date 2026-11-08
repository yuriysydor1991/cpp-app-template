# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [appLog4Cpp50.10.0] - 2026-11-08

- d89bec2 Removing the destination OS from the AppImage package name
- 34d0a51 Introducing the STT branches info into the READMEs
- 7c09336 Replacing the CMAKE_SOURCE_DIR/CMAKE_BINARY_DIR by the PROJECT_SOURCE_DIR/PROJECT_BINARY_DIR
- b01c667 Introducing the appWebAssembly branch info into the READMEs
- 9b87a05 Introducing the appLlamaCPP branch info into the READMEs
- a8a8abf Introducing the TTS branches info into the READMEs
- 09a4c33 Introducing the destination OS into the package names
- 7f64259 Synchronizing the template flavors list of the READMEs
- b77d0e5 Documenting the log4cpp init result of an unopenable log file
- b332ead Fixing the AppImage and log4cpp entries of the build index pages
- 5ab2621 Refreshing the shared library cache after the from-source installs
- 0de859a Fixing the cppcheck findings of the new signals handler, tests and log mock
- a020369 Updating the app component diagram to the signals handlers design
- b1dd0dd Renumbering the custom command line parameters section numbered 4-6 twice
- 1f42ad5 Documenting the built in command line options and the usage errors
- 908363a Testing the application with the real command line arguments
- ee9ab84 Parsing the command line before the log file initialization
- 045b16c Exiting with a failure status on the command line usage errors
- dd7d169 Fixing the missing option value raising the version flag instead of the help one
- 5e8655e Fixing the CommandLineParser test assertions which could not fail
- 0b01ba1 Fixing the log mock LOG_INIT forwarding into the LOG_INIT_DEFAULTS mock
- f9eb981 Restoring the previous signal dispositions on the signals handler uninstall
- 7ff5d68 Leaving the SIGTTIN and SIGTTOU signals to the shell job control
- 7f23848 Removing the nonexistent module path directories and cppcheck suppression
- 5cbe79a Fixing the zlib gzip file example ignoring the read and close errors
- 21ea836 Fixing the flatpak requirements section naming an outdated SDK version
- f7fd104 Documenting the ENABLE_COMPONENT_TESTS option of the test builds
- 33146ed Listing every linked doc section in the requirements and build index pages
- 054fe1e Fixing the documentation links pointing into the other language
- c992f5a Fixing the stale file paths named in the documentation
- c12f9ae Fixing the flatpak target failing on its repeated build
- c538bd4 Fixing the snap command path ignoring the install prefix
- 54a61d5 Fixing the documentation install which needed a manual Doxygen-doc build
- 2a4a56c Skipping the Doxygen and callgrind targets when their tools are missing
- 1cb2d7e Installing the packager tools into the Jenkins pipeline image
- a82bb64 Replacing the libjpeg-turbo download fallback with a clear configure error
- b4c793f Fixing the libavif download fallback stopping without the system libyuv
- e425e01 Pinning the third-party download fallbacks to their release tags
- 7b73c8d Failing the CI test stages which match no tests
- 3c0a07e Fixing the Jenkins doc sections linked check skipping the section directories
- b719366 Replacing the broken OpenSSL download fallback with a clear configure error
- b608ca2 Fixing the mixed target_link_libraries signatures on the project binary
- 28e3689 Fixing the MAX_LOG_LEVEL option help text error level value
- fd4f9ac Fixing the logger level filter tests which could not fail
- 886d1f7 Fixing the log macros to expand into single statements
- bfed0af Fixing the log file open failure aborting the process
- 213885a Splitting the packages install scripts per OS release
- be4faf4 Introducing the flatpak cleanup of the log4cpp development files
- 9e2aefe Fixing the logger branch name in the CTEST_log comment
- fc361a7 Fixing the log4cpp link snippets to the keyword target_link_libraries signature
- 0c25aef Removing the redundant ENABLE_LOGS_MICROSECONDS_TIME option
- d9cc25e Fixing the log4cpp requirements doc numbering and wording
- 3a50e8b Introducing the log4cpp runtime dependency into the deb and snap packages
- 1099426 Introducing the Log4Cpp5Init component test
- ac33e5c Fixing the shifted log4cpp priorities of the log macros
- fca36fc Warning about the unopenable log4cpp log file instead of dropping the logs
- 58493b9 Fixing the ignored and duplicated log4cpp appenders of the repeated log inits
- 8304eef Pinning the log4cpp 1.1.6 release instead of its release candidate
- 8c1df44 Excluding the fetched log4cpp files from the project installation
- 4b326c3 Fixing the include directory of the fetched log4cpp sources
- 9858db0 Synchronizing the log mock with app
- 0220bc1 Synchronizing the CommandLineParser parse doc comment with app
- 80723a9 Synchronizing the get_stop assertions of the application tests with app
- a5534fc Replacing the unreachable GNU gettext site link with its Savannah page
- e1b9354 Introducing the destination CPU architecture into the package names
- c9b3d5b Introducing the appGettext branch info into the READMEs
- 70760f6 Introducing the appDarknetXX branch info into the READMEs
- 95d98e0 Introducing the RedHat packages install script
- 29c390e Registering the CTEST_app component tests in the build and the pipeline
- 5e38b3c Introducing the appWhisperCPP branch info into the READMEs
- d19bdab Introducing the FreeBSD packages install script
- dd8a71f Introducing the appV8 branch info into the READMEs
- 23e27f7 Erasing the build sources and trees of the docker images
- f9e7cf4 Introducing the debug clang-format script
- 4c9809d Resetting the inherited signals dispositions in the signals handlers tests
- 3463017 Introducing the binary hardening options section into the READMEs
- 9d1156c Introducing the binary hardening compile and link options
- 1c76820 Introducing the GitLab CI/CD pipeline section into the READMEs
- d6a049d Introducing the GitLab CI/CD pipeline mirroring the Jenkinsfile
- e45f4a8 Introducing the GitHub Actions CI pipeline section into the READMEs
- 013a5fc Introducing the GitHub Actions CI pipeline mirroring the Jenkinsfile
- 3fc309e Correcting the appQt6QtDBusClient branch description in the READMEs
- 63fdd4d Introducing the desktop application packaging switch
- 803e99d Limiting the documentation checks to the repository own markdown files
- 214375d Excluding the GCC own include directories from the clang-tidy search path
- a82a1c5 Accepting the 405 documentation URLs
- 63cbedd Spacing out the branch entries in the READMEs
- fadb3e2 Rewording the DOCKER_HOST environment requirement in the docker docs
- 35f2a84 Removing the DOCKER_HOST variables from the docker enablers
- db6decb Excluding the build trees from the Docker build context
- dfafaf6 Retrying the unreachable documentation URLs and accepting the 403 ones
- 72f346d Introducing the --rebuild flag into the Jenkins docker scripts
- 1751d9a Rebuilding the image from its base on the Jenkins pipeline force rebuild
- e29acd7 Introducing the audio assets branches info into the READMEs
- 2a3f0c3 Splitting the signals handlers per category and covering the pause, reload, user defined and ignored signals
- 15164aa Introducing the app signals handlers subcomponent
- 4fd2334 Declaring the main function argv parameter as an array
- 3284343 Moving the packagers templates into the per-packager directories
- 8f0ba2d Dropping the packagers and the development tools from the packages install list
- 768c23a The destination CPU architecture of the AppImage package name
- a0b926d Picking the CPack AppImage enabler since the CMake 4.2 and dropping the debug banners
- a5da894 Extracting the AppImage enabler pick into its own general enabler
- a241988 Selecting the AppImage packager enabler by the CMake version
- fbc7c31 Introducing the CPack based AppImage packager enabler
- 4a296c9 Introducing the AppImage packager
- c0dfbbb Introducing the --install flag into the packager build scripts
- cd6935f Renaming the packages install script and adding the Ubuntu one
- 99153f3 Introducing the target architecture into the flatpak package name
- b15038a Introducing the AppStream metainfo file into the flatpak package
- ecfe31b Consuming the install directory variables the flatpak-builder passes
- e8eb414 Introducing the required packages install script
- 19d0c30 Introducing the log4cpp enabler with the Internet fallback
- baf3f7a Installing the flatpak build dependencies from the flathub remote
- 5088121 Dropping the redundant build step from the packager scripts
- 01dcfc5 Introducing the per packager build scripts
- a58d207 Introducing the appCFITSIO branch info into the READMEs
- f3eb58f Make the compile time log level gate really gate
- cb3e2ce Introducing the appGtkmm4Libadwaita branch info into the READMEs
- 0fa7cfb Decomposing the IApplication descendants into the applications subcomponent
- 723a030 Introducing the appFontAwesome branch info into the READMEs
- 3920c1d Introducing the debug test script and its --test parameter
- 6f8f2e0 Incrementing version to appLog4Cpp50.10.0
- e0048f8 Release appLog4Cpp50.9.0 at 2026-08-17

## [appLog4Cpp50.9.0] - 2026-08-17

- 29a9bf3 Introducing the InsertNewlineAtEOF clang-format option
- 3635c0b Introducing the appCURLChatGPT branch info into the READMEs
- 1b9860b Hiding the ApplicationContext fields and adding the atomic stop flag
- 0280f76 Moving the linker hardening options out of the compile options
- dbc9106 Introducing the appCURLClaude branch info into the READMEs
- 6d0b542 Introducing the external documentation URLs check into the Jenkins pipeline
- 70b22a7 Correcting the docker modules path of the documentation
- 77a2c0f Introducing the quick build and the docker starter scripts
- 938392a Introducing the quick build and the docker starter scripts
- 257aea4 Making the docker containers run under unprivileged users
- 6712e1a Enabling the component tests in the Jenkinsfile debug configure
- d6f3468 Fixing the stray closing brace in the Jenkinsfile
- 4957f7b Repairing the appLog4Cpp5 cppcheck stage
- 8ac3e00 Repairing the pipeline code check stages
- 9aa6ce1 Fix the log4cpp requirements link in the section 3 index
- 6d97e44 Introducing the appPGPLOT branch info into the READMEs
- a4191df Fixing the Jenkisfile
- a9c876e Fix broken cppcheck link in section 5 index
- 9a3259a Fix Groovy escape sequences in markdown link checker stage
- 45f5bff Rework markdown link checker stage to pure bash
- 2ed960e Add Jenkinsfile stage to detect broken markdown links; fix pre-existing broken links
- e91bbea Reorganize doc/sections into section dirs with category grouping
- 628e866 Add an OpenSSL cmake enabler module with SHA-256, HMAC-SHA256 and HTTPS/TLS client code samples
- 464c144 Register the missing tests in the misc/Jenkinsfile
- c39656f Group the enabler documentation under subsections in the READMEs
- f55b3e2 Group the compression branches under a dedicated README section
- 27a3ea0 Introducing the appLZMA branch info into the READMEs
- 971b4fd Add a liblzma (XZ Utils) compression library enabler module
- 8234d40 Introducing the appZlib branch info into the READMEs
- 9a6a783 Add zlib compression usage examples to its enabler documentation
- 61eacea Replace the redundant PROJECT_NAME CMake variable with CMAKE_PROJECT_NAME
- d64f100 Introducing the appGtkmm4Vulkan branch info into the READMEs
- 65e9c5a Removing the appGtkmm4Vulkan branch info from the READMEs
- 7b84f59 Introducing the appQt6Vulkan and appGtkmm4Vulkan branches info into the READMEs
- b1859b3 Simplifying root CMakeLists.txt
- d6c0fe9 Introducing the appFirebird branch info into the READMEs
- 2aef383 Introducing the appGtkmm4GDBusClient branch info into the READMEs
- ac68e2a Introducing the appQt6GLArea branch info into the READMEs
- 5392bb3 Introducing the appGtkmm4GLArea branch info into the READMEs
- a4a3d59 Splitting the Data Visualization README category into Plots/Graphs and Maps
- cf05129 Introducing the applibMeson branch info into the READMEs
- 414b018 Introducing the log facade component test (CTEST_log) into appLog4Cpp5
- 49d67fc Introducing the zlib and image format cmake enablers with docs
- 7283b01 Introducing the appSFML branch info into the READMEs
- e169255 Introducing the appwxWidgets branch info into the READMEs
- 418828b Introducing the appQt6QtDBusClient branch info into the READMEs
- 4b01c4e Introducing the appQt6QtLocation branch info into the READMEs
- e44a440 Introducing the appQt6ChartView branch into the READMEs
- d653a2d Introducing the appGtkmm4LeafLet and appQt6LeafLet branches info into the READMEs
- 83f1753 Introducing the COMPONENTS arg for template_project_default_3rdparty_enabler
- 87f8619 Introducing the appSDBusCxxClient and appSDBusCxxServer branches info into the READMEs
- 00d0df3 Moving Dockerfiles and packagers files into separate subdirs in the misc
- 4b8f955 Adding .claude dir to .gitignore
- be6f6f3 Introducing project structure section Будь ласка, зверніться до адміністратора subsection
- a1ae2cf Introducing the libMeson branch info into the READMEs
- f38e31d Introducing info about newly created branch appOpenCV into READMEs with it's cmake enabler.
- 3959519 Introducing the CPack's RPM package generator integration
- 3788dcb Removing unmerged lines in the doc/README.uk_UA.md
- cfe829c Introducing the MS Windows WIX package generation through CPack integration
- f1a676c Introducing the project's FreeBSD pkg package generation support through CPack. Works only on FreeBSD.
- 59599f3 Deleting REQUIRED marking from the snapcraft's find_program
- a86b6e7 By default disabling the snap package manager
- bdbe813 Introducing the snap packager integration with documentation
- 4e6a052 Introducing and migrating to the template_project_default_3rdparty_enabler cmake function. Making enablers git sources variables modifiable.
- cec42bd Moving all CMake variables declarations into their respectful enablers.
- 8b749dd Moving Doxygen related CMake variables into doc/CMakeLists.txt file
- ebf2c56 Introducing the libxml2 enabler cmake module
- b83e7d2 Enhancing the cmake files fs structure
- e06c29a Making docker base image configurable through CMake variables
- b916be0 Introducing the appPLplot branch info into the READMEs
- a5760e5 Introducing the MatPlot++ appMatPlotxx branch into the READMEs
- 03f3954 Making the cppcheck stage optional due to unstable results
- c3a1a59 Fixing clang-tidy conf misspell
- f330c1d Switching off the clang-tydy's unrecognizable AnalyzeTemporaryDtors config param
- c580ee5 Loggging README's misspell refine
- 38e1130 Grouping and categorising available template flavors links in the READMEs
- 014b8f6 Renaming properly Nlohmann JSON library CMake enabler file
- 7c7466a Introducing the forgottent Nlohmann JSON library enabler info into the READMEs
- 5902236 Decomposing READMEs
- d6dcbbd  Introducing the --branch cmd line flag for git clone command in the READMEs
- 334cba0 Introducing explicit template altering notice in the READMEs headers
- fb520bd Optimizing some CMake commands in the README.md
- d0619f4 Introducing the appGtkmm4 branch info into the READMEs
- 39e3ca8 Introducing the PlantUML app component diagram into the READMEs
- eee94f7 Enabling GTest during for CTs
- 6ed46c3 Pointing Jenkins configurable port into standart in-container 8080
- 4876e0c Making the Jenkins pipeline container and image names configurable
- 0e8a2c8 Refining the branches link in the READMEs, introducing gitlab links also
- 70bbe91 Specifying the Jenkins container run target in the READMEs
- df14932 Introducing basic Jenkins pipeline CMake target and Jenkinsfile conf
- a8d13dd Refinining the cppcheck target
- fbecdd4 Introducing misc/.cppcheck-suppress file to list cppcheck suppressions of the false positives
- 9e6f475 Fixing typo in the README.md
- a32a942 Introducing the valgrind callgrind profiler target for the project
- f6ba07c Introducing the gprof profiling target
- 88e786b Introducing the libcurl cmake enabler script
- 50d3356 Adding money emoji to donation notice in the READMEs
- 465c051 Introducing the appCURL branch info into the READMEs
- af55c10 Introducing the enabling libcurl section into the READMEs
- ad968d4 Introducing a custom log file cmd param for the executable
- bbe827c Deleting redundant coma sign from flatpak json conf
- e4abc6a Introducing the CMDParamNames class to encapsulate CMD params names
- 0cfdcb8 Introducing some marketing sentences in the README's goal section
- df26f1c Introducing the cmake/enablers subdirectory to locate the 3rd-party dependencies
- c79885e Renaming emplate-project-make-GTest-available - template-project-GTest-enabler
- c8d56a0 Introducing the NLohmann JSON library enabler cmake module
- 6e4886d Fixing the sanitizers cmake file in the READMEs
- de8c85f Introducing the thread id into the logging messages
- a33c92e Introducing the CMake configurable log severity messages compilation switch
- 429e41e Introducing the appBoostLog branch info into the READMEs
- 2ebadf9 Hiding the compile options cmake files under separate directory
- b92660e Enhancing sanitizers combinations and new cmake dir for ones
- 0db676d Introducing the sanitizers enabling info into the READMEs
- 1ca27c7 Removing redundant cmake traces messages
- cc098fd Introducing the GCC compiler sanitizers
- 00cfb5f Refined issues in the Docker READMEs doc
- 8c3f7cf Fixing the log4cpp v5 dev package name for Dockerfile
- 5e00673 Refining the Docker target for required packages
- 2fce939 Separating the Docker single container build and run targets
- abd44e8 Introducing the Docker single run container target.
- bad31b8 Adding project neatness to the READMEs
- 8969f48 Marking the appLog4Cpp5 as the current branch in the READMEs
- adce198 Introducing the appLog4Cpp5 branch info into the READMEs
- c24f2bb Refining the flatpak target
- c1d8423 Introducing the required packages for log4cpp v5 into the READMEs
- 49d0a29 Implementing the basic log4cpp v5 logging infrastructure.
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

[appLog4Cpp50.10.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/appLog4Cpp50.10.0)
[appLog4Cpp50.9.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/appLog4Cpp50.9.0)
[app0.8.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.8.0)
[app0.7.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.7.0)
[app0.6.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.6.0)
[app0.5.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.5.0)
[app0.4.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.4.0)
[app0.3.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.3.0)
[app0.2.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.2.0)
[v0.1.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/v0.1.0)
