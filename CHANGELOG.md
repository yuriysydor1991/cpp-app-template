# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [maintenance0.12.0] - 2026-11-08

- 945809a Removing the destination OS from the AppImage package name
- c421088 Introducing the appSherpaONNXSTT Jenkins exported jobs
- e172aa4 Introducing the STT branches info into the READMEs
- cb7bee4 Replacing the CMAKE_SOURCE_DIR/CMAKE_BINARY_DIR by the PROJECT_SOURCE_DIR/PROJECT_BINARY_DIR
- c1ed32e Introducing the appWebAssembly Jenkins exported jobs
- 1a727ac Introducing the appWebAssembly branch info into the READMEs
- 089e385 Introducing the appWebAssembly branch packages into the pipelines image
- 173fa1f Introducing the appLlamaCPP Jenkins exported jobs
- a2b963b Introducing the appLlamaCPP branch info into the READMEs
- d11e183 Introducing the TTS branches packages into the pipelines image
- 1bbfd96 Introducing the TTS branches Jenkins exported jobs
- 6f188a6 Introducing the TTS branches info into the READMEs
- 76bbb05 Introducing the destination OS into the package names
- 7ae8a5c Synchronizing the template flavors list of the READMEs
- 51faa56 Refreshing the shared library cache after the from-source installs
- e4b44ff Removing the personal tools and the unused packages of the install scripts
- 5bab608 Listing the QEMU and the local CI pipelines sections in the build index pages
- fa10a01 Removing the nonexistent module path directories and cppcheck suppression
- 1706f85 Removing the unused log mock of the main branch
- 5ca5217 Fixing the zlib gzip file example ignoring the read and close errors
- dcd2ff3 Fixing the flatpak requirements section naming an outdated SDK version
- e5496b8 Documenting the ENABLE_COMPONENT_TESTS option of the test builds
- 08f919a Listing every linked doc section in the requirements and build index pages
- ad46b9f Fixing the documentation links pointing into the other language
- 73bf62b Fixing the stale file paths named in the documentation
- 0569d22 Fixing the flatpak target failing on its repeated build
- 4a92548 Fixing the snap command path ignoring the install prefix
- 17f3b27 Fixing the documentation install which needed a manual Doxygen-doc build
- 32a73b5 Skipping the Doxygen and callgrind targets when their tools are missing
- 7de10b5 Replacing the libjpeg-turbo download fallback with a clear configure error
- 8e20403 Fixing the libavif download fallback stopping without the system libyuv
- 30b8d21 Pinning the third-party download fallbacks to their release tags
- 173fc5a Failing the CI test stages which match no tests
- 01f4059 Fixing the Jenkins doc sections linked check skipping the section directories
- e39d698 Replacing the broken OpenSSL download fallback with a clear configure error
- 4a4f4cf Fixing the mixed target_link_libraries signatures on the project binary
- eff05e8 Fixing the MAX_LOG_LEVEL option help text error level value
- 02f1dc7 Fixing the logger level filter tests which could not fail
- 6b12550 Fixing the log macros to expand into single statements
- 5512d10 Fixing the logger data races on the log file reopening and the level
- be34143 Fixing the log file open failure aborting the process
- 3e0ea41 Splitting the CTEST_DefaultLogger helper classes into own files
- 17e9e49 Splitting the packages install scripts per OS release
- c849545 Fixing the local pipelines parallel jobs default described as every job
- 3899b39 Listing every library the Jenkins pipeline image builds from the sources
- ff89e05 Fixing the uk_UA requirements index linking the snap build section
- 04c8cb1 Seeding the Qt WebEngine flatpak base app into the Jenkins pipeline image
- 7e283e0 Removing the unused multimedia packages of the Jenkins pipeline image
- d10027c Pinning the libraries the Jenkins pipeline image builds from the sources
- 7985974 Synchronizing the version tracking section with main
- 04ad041 Removing the Jenkins job of the separate darknetxx repository
- 7be79c7 Fixing the Jenkins jobs import which imported nothing by default
- 7b0ac73 Restoring the log.h component tests and the CTEST_log stage of main
- 5c3a7c8 Introducing the local CI pipelines tools into the packages install scripts
- aa9e0df Introducing the local CI pipelines run section into the READMEs
- 635168a Introducing the local CI pipelines starter scripts
- 4780eb6 Introducing the local GitHub Actions and GitLab CI/CD pipeline runner targets
- 3584c3f Replacing the unreachable GNU gettext site link with its Savannah page
- 45dbdf4 Introducing the destination CPU architecture into the package names
- 39a6c65 Introducing the appGettext packages into the pipelines image
- b905ca4 Introducing the appGettext Jenkins exported jobs
- 59aefc8 Introducing the appGettext branch info into the READMEs
- fa67247 Moving gitlab Jenkins exportees files into separate dir
- 0714170 Introducing the appDarknetXX Jenkins exported jobs
- 617f84c Introducing the appDarknetXX branch info into the READMEs
- 6ab0823 Introducing the RedHat packages install script
- 1674bb4 Introducing the FreeBSD and MS Windows QEMU virtual machine scripts
- 34abddc Introducing the appWhisperCPP Jenkins exported jobs
- 65e6974 Collecting the new branches packages and libraries into the pipelines image
- 4c1cd47 Raising the Jenkins durable task heartbeat interval of the pipelines image
- 15ff5e5 Introducing the appWhisperCPP branch info into the READMEs
- 00a9513 Introducing the FreeBSD packages install script
- 252bf2f Introducing the appV8 Jenkins exported jobs
- a6f34fb Introducing the appV8 branch info into the READMEs
- 1e919ac Erasing the apt archives and lists of the Jenkins pipeline image
- a69f673 Erasing the build sources and trees of the docker images
- 1cc4154 Erasing faulty flatpak package
- f113d8e Fixing the absent packages of the Jenkins pipeline container
- 566cf11 Disabling the GitLab sourced Jenkins pipeline jobs
- 689947d Introducing the debug clang-format script
- f869d24 Introducing the binary hardening options section into the READMEs
- 69ad511 Introducing the binary hardening compile and link options
- cf66ae8 Introducing the GitLab CI/CD pipeline section into the READMEs
- 990297e Introducing the GitLab CI/CD pipeline mirroring the Jenkinsfile
- 6228ad4 Introducing the GitHub Actions CI pipeline section into the READMEs
- 8fec83f Introducing the GitHub Actions CI pipeline mirroring the Jenkinsfile
- b119b77 Correcting the appQt6QtDBusClient branch description in the READMEs
- 1831638 Introducing the desktop application packaging switch
- 100eb8a Limiting the documentation checks to the repository own markdown files
- 209ad1c Excluding the GCC own include directories from the clang-tidy search path
- 1080edb Accepting the 405 documentation URLs
- 57eb68a Spacing out the branch entries in the READMEs
- c34b633 Rewording the DOCKER_HOST environment requirement in the docker docs
- b0aae2f Removing the DOCKER_HOST variables from the docker enablers
- c6a91af Excluding the build trees from the Docker build context
- 9847e73 Seeding the flatpak runtimes the branches use
- 2dd3cf5 Unconfining the container system paths for the flatpak-builder procfs mount
- 5fdc2d4 Retrying the unreachable documentation URLs and accepting the 403 ones
- d7e5f0d Dropping the darknetxx at GitLab exported Jenkins job
- 1c2b4ca Introducing the --renew-container flag into the Jenkins docker run script
- 3078b79 Keeping two executors on the Jenkins pipeline built-in node
- b740742 Introducing the --rebuild flag into the Jenkins docker scripts
- f07e136 Rebuilding the image from its base on the Jenkins pipeline force rebuild
- 7fa0229 Introducing the audio assets branches exported Jenkins jobs
- b470a0d Refining the Jenkins pipeline container for the packagers of every branch
- 515fd61 Introducing the audio assets branches info into the READMEs
- 2c667f2 Declaring the main function argv parameter as an array
- 3cb88f4 Moving the packagers templates into the per-packager directories
- 1d677a5 Dropping the packagers and the development tools from the packages install list
- 1b98f24 The destination CPU architecture of the AppImage package name
- 74f00eb Picking the CPack AppImage enabler since the CMake 4.2 and dropping the debug banners
- 6225190 Extracting the AppImage enabler pick into its own general enabler
- 324a25a Selecting the AppImage packager enabler by the CMake version
- 9846d14 Introducing the CPack based AppImage packager enabler
- 160ca90 Introducing the AppImage packager
- 6b48098 Introducing the --install flag into the packager build scripts
- 1aaa26b Renaming the packages install script and adding the Ubuntu one
- 17734a2 Introducing the target architecture into the flatpak package name
- 34a7cc2 Introducing the AppStream metainfo file into the flatpak package
- a174fde Consuming the install directory variables the flatpak-builder passes
- fa34f50 Introducing the required packages install script
- d6169a1 Installing the flatpak build dependencies from the flathub remote
- c7ca43a Dropping the redundant build step from the packager scripts
- 94824e5 Introducing the per packager build scripts
- 9e28712 Introducing the appCFITSIO and appGtkmm4Libadwaita exported Jenkins jobs
- c14369d Introducing the appCFITSIO branch info into the READMEs
- c9afd18 Make the compile time log level gate really gate
- c4ede30 Introducing the appGtkmm4Libadwaita branch info into the READMEs
- ccfaac6 Pinning the log message stream to the classic locale
- 3e52d07 Introducing the appFontAwesome exported Jenkins jobs
- 2540954 Introducing the appFontAwesome branch info into the READMEs
- 561629b Enabling the appMeson exported Jenkins jobs by default
- 73f25bd Erasing the exported Jenkins jobs of the gone experimental branches
- d398d9d Introducing the debug test script and its --test parameter
- 011034c Introducing the InsertNewlineAtEOF clang-format option
- 28d159d Adding additional cores for the jenkins all in one pipeline container
- 5d75332 Introducing the appCURLChatGPT branch info into the READMEs
- d2bb5db Introducing the missing Jenkins exported jobs of the GNU/Linux capable branches
- 3a11606 Moving the linker hardening options out of the compile options
- 6cb5941 Split the DefaultLogger into a static proxy and a real logger instance
- c6818f6 Introducing the appCURLClaude branch info into the READMEs
- 47d30d1 Introducing the GitLab Jenkins exported jobs and the forge suffixed names
- fa85686 Introducing the external documentation URLs check into the Jenkins pipeline
- 478a70b Introducing the quick build and the docker starter scripts
- 7173c37 Making the docker containers run under unprivileged users
- 0b6b53d Renaming the SimpleLogger component into the DefaultLogger
- 77c9880 Making jenkins the default user
- 967123d Erased redundant backslashes
- 37ae150 Limiting the pipeline containers cpus and flatpak refinements
- 8502459 Repairing the pipeline code check stages
- a8f6f6f Introducing the appPGPLOT branch info into the READMEs
- 8a4833c Fixing the Jenkinsfile
- e5771e6 Enhancing the general pipeline Dockerfile
- 93fc927 Fix broken cppcheck link in section 5 index on maintenance
- f7b39fd Fix Groovy escape sequences in markdown link checker stage
- a8f4928 Rework markdown link checker stage to pure bash
- 0d3a367 Add Jenkinsfile stage to detect broken markdown links; fix pre-existing broken links
- 2c075b8 Reorganize doc/sections into section dirs with category grouping
- e51a6ad Add an OpenSSL cmake enabler module with SHA-256, HMAC-SHA256 and HTTPS/TLS client code samples
- 418461c Some additional Jenkins jobs backups
- b99abb9 Group the enabler documentation under subsections in the READMEs
- 23b430a Group the compression branches under a dedicated README section
- 0147919 Fix the misc/Jenkinsfile checkout branch to the maintenance branch name
- aa4e5d7 Introducing the appLZMA branch info into the READMEs
- db1ebca Add a liblzma (XZ Utils) compression library enabler module
- 6e703bf Drop dead cmake/dockerers module-path append
- 360e1bd Fix stale cmake/dockerers doc paths to cmake/enablers/dockerers
- f433bc4 Add a CMake target to import Jenkins job XMLs into a configurable server
- 6428931 Introducing the appZlib branch info into the READMEs
- d78e64e Add zlib compression usage examples to its enabler documentation
- eae10ae Replace the redundant PROJECT_NAME CMake variable with CMAKE_PROJECT_NAME
- 2e1e82f Introducing the appGtkmm4Vulkan branch info into the READMEs
- af32cbf Removing the appGtkmm4Vulkan branch info from the READMEs
- 9add2d8 Introducing the appQt6Vulkan and appGtkmm4Vulkan branches info into the READMEs
- 314d243 Simplifying root CMakeLists.txt
- 2bb88b7 Introducing the appFirebird branch info into the READMEs
- d8afec4 Introducing the appGtkmm4GDBusClient branch info into the READMEs
- fc7c0f0 Introducing the appQt6GLArea branch info into the READMEs
- 0f5ab5b Introducing the appGtkmm4GLArea branch info into the READMEs
- 6620ce4 Splitting the Data Visualization README category into Plots/Graphs and Maps
- 08ff466 Introducing the applibMeson branch info into the READMEs
- 2317a61 Introducing the zlib and image format cmake enablers with docs
- 9858e9d Introducing the appSFML branch info into the READMEs
- fad0ead Introducing the appwxWidgets branch info into the READMEs
- 2d03b1c Introducing the appQt6QtDBusClient branch info into the READMEs
- a75aea8 Introducing the appQt6QtLocation branch info into the READMEs
- 2df9a0c Introducing the appQt6ChartView branch into the READMEs
- 3136e18 Introducing the appGtkmm4LeafLet and appQt6LeafLet branches info into the READMEs
- 4d9d4d4 Exposing the fuse FS for Jenkins pipelines
- e7b9a64 Introducing additional webview alike packages for jenkins pipeline
- 2aa8a98 Introducing the webview widgets for jenkins container
- 1046853 Introducing the COMPONENTS arg for template_project_default_3rdparty_enabler
- 2db5848 Introducing the dbus-c++ lib into jenkins docker container
- 2ebfbba Updating jenkins jobs exportees
- 6a64011 Updating the jeneral pipeline container
- 97fdafc Introducing the appSDBusCxxClient and appSDBusCxxServer branches info into the READMEs
- 4613b37 Moving Dockerfiles and packagers files into separate subdirs in the misc
- 06c3592 Adding .claude dir to .gitignore
- 1001ee0 Introducing project structure section Будь ласка, зверніться до адміністратора subsection
- caab664 Introducing the libMeson branch info into the READMEs
- 26577f5 Introducing info about newly created branch appOpenCV into READMEs with it's cmake enabler.
- 1ab8f6d Introducing the CPack's RPM package generator integration
- eef08a6 Introducing the MS Windows WIX package generation through CPack integration
- f4d0349 Introducing the project's FreeBSD pkg package generation support through CPack. Works only on FreeBSD.
- b53c136 Deleting REQUIRED marking from the snapcraft's find_program
- 026145b By default disabling the snap package manager
- 98983d9 Introducing the snap packager integration with documentation
- 842b4a7 Introducing and migrating to the template_project_default_3rdparty_enabler cmake function. Making enablers git sources variables modifiable.
- 064ca1c Moving all CMake variables declarations into their respectful enablers.
- 939b5c0 Moving Doxygen related CMake variables into doc/CMakeLists.txt file
- b81fb01 Introducing the libxml2 enabler cmake module
- 23f4b3c Screening Jenkins jar connector manipulation targets
- 65d0438 Enhancing the cmake files fs structure
- 1b3abc4 Making docker base image configurable through CMake variables
- 6d03627 Introducing the appPLplot branch info into the READMEs
- bafe202 Introducing Jenkins pipelines jobs CMake export script
- 9142da3 Introducing the MatPlot++ appMatPlotxx branch into the READMEs
- 6eb2009 Introducing the all in one jenkins pipeline docker builder script
- d63ca6c Making the cppcheck stage optional due to unstable results
- 2cda7cf Fixing clang-tidy conf misspell
- 286cd82 Switching off the clang-tydy's unrecognizable AnalyzeTemporaryDtors config param
- bfdb643 Supressing the cppcheck's missingIncludeSystem and unusedStructMember warnings.
- 5c318cd Fixing the main Jenkinsfile pipeline script.
- 9eb25b9 Loggging README's misspell refine
- 399a644 Missing newlines in the READMEs
- ae6b6b9 Grouping and categorising available template flavors links in the READMEs
- 79920a1 Renaming properly Nlohmann JSON library CMake enabler file
- 57ab382 Introducing the forgottent Nlohmann JSON library enabler info into the READMEs
- 898f8cb Fixing 'command line build' links
- cd7d51b Additional READMEs split refinements. Adding new sub sections for the "project structure".
- b78814f Splitting main READMEs files into separate sub sections files under the /doc/sections/[locale] Since people are afraid of the large documents.
- 47f4d94 Introducing the ENABLE_LOGS_MICROSECONDS_TIME CMake option in order to be able to disable microseconds in the log messages.
- 70aeb0b Introducing explicit template altering notice in the READMEs headers
- 289605e Optimizing some CMake commands in the README.md
- 9bede14 Introducing the appGtkmm4 branch info into the READMEs
- 2ce3c54 Enabling GTest during for CTs
- f6b0242 Pointing Jenkins configurable port into standart in-container 8080
- 6b76c98 Making the Jenkins pipeline container and image names configurable
- 0590f02 Introducing basic SimpleLogger CTs with CMake and Jenkins integration
- 2a3e69a Adding CTs CMake flag to a Jenkins pipeline debug build
- d171624 Introducing basic SimpleLogger CTs with CMake and Jenkins integration
- a12f160 Introducing the SimpleLogger CTs samples
- 0c25987 Refining the branches link in the READMEs, introducing gitlab links also
- 94cf40b Fixing another link type in the README.md
- 1d90533 Fixing link typo inside READMEs
- 7f7f230 Specifying the Jenkins container run target in the READMEs
- ba50a1d Erasing UTs Jenkins stage due to absens of UTs
- 9995775 Introducing basic Jenkins pipeline CMake target and Jenkinsfile conf
- ac33438 Incrementing version to 0.12.0
- 06edab4 Release main0.11.0 at 2025-09-08

## [main0.11.0] - 2025-09-08

- ff7a28a Fixing typo in the README.md
- 5851c08 Introducing the valgrind callgrind profiler target for the project
- 0a57308 Introducing the gprof profiling target
- 37e942c Adding money emoji to donation notice in the READMEs
- 1bbabb5 Introducing the appCURL branch info into the READMEs
- f0adc15 Erasing redundant iostream include in the main.cpp
- ea880b0 Introducing the DEFAULT_LOG_FILE_PATH cmake var and cpp macro to specify default dst log file location
- fa33d33 Introducing the enabling libcurl section into the READMEs
- 898b248 Introducing the libcurl cmake enabler script
- cb582a7 Moving the DEFAULT_LOG_FILE_PATH macro declaration into severity-macro-consts.h
- a4a984f Introducing some marketing sentences in the README's goal section
- 3913f28 Introducing the cmake/enablers subdirectory to locate the 3rd-party dependencies
- b44ec67 Renaming emplate-project-make-GTest-available - template-project-GTest-enabler
- ca466f6 Introducing the NLohmann JSON library enabler cmake module
- a0590d6 Fixing the sanitizers cmake file in the READMEs
- 2631a54 Avoiding unnecessary badly portable localtime_r usage
- 626884a Introducing the thread id into simple logger
- fb5d64e Avoiding backward time in the simple logs
- 42933e1 Avoiding final log multiple str fetches
- 1f456f4 Refining the log current timestamp method, increasing thread safety
- 5da6342 Introducing the CMake configurable log severity messages compilation switch
- 36e0d25 Introducing the appBoostLog branch info into the READMEs
- 7d504d9 Hiding the compile options cmake files under separate directory
- c5341ac Enhancing sanitizers combinations and new cmake dir for ones
- 3ae7d93 Introducing the sanitizers enabling info into the READMEs
- cb841dc Removing redundant cmake traces messages
- 866d012 Introducing the GCC compiler sanitizers
- 045cc31 Inserting release main0.10.0 to releases lists in CHANGELOG.md
- 2296397 Incrementing version to 0.10.0

## [main0.10.0] - 2025-06-06

- 976e79f Release 0.10.0 2025-06-06
- 27ebb79 Refined issues in the Docker READMEs doc
- 9b01974 Separating the Docker single container build and run targets
- cc85abf Erasing UTs build and ctest call inside the Dockerfile
- 7f78451 Introducing the Docker single run container target.
- 4466527 Adding project neatness to the READMEs
- 061869f Introducing the appLog4Cpp5 branch info into the READMEs
- bcc9e4f Implementing the logging macros and a simple logger to perform log messaging
- be5178c Introducing the appMongoDBCpp4 branch info into the READMEs
- 024453c Code formatting applied
- 9d19ef2 Making the flatpak source json conf file configurable during cmake conf stage
- 2e50a87 Refining the deb cmake info for cpack
- e25158c Including and reusing the project-global-decls.h for demonstration
- 3992ba3 Erasing redundant suppression that causes cppcheck to fail
- 2055c45 Replacing the inviting comment with printable message on main.
- d61425b Introducing the appSQLiteCpp3 branch info into the READMEs
- e07d63b Introducing the gitlab mirror into the READMEs
- bb779b1 Introducing misc/.cppcheck-suppress file to list cppcheck suppressions of the false positives
- c182171 Introducing the appMySQLCppConn branch info into the READMEs
- ce81652 Introducing the appBoostBeast branch info into the READMEs
- 09bf4c6 Explicitly specifying the combining of the template branches
- 85ef7c7 introducing the appPgSQLxx branch into the READMEs
- 4c8cacd Introducing a new appWt4 branch info into the READMEs

## [main0.9.0] - 2025-03-31

- bb3bf64 Release 0.9.0 2025-03-31
- 3d7f096 Introducing the error exit code for a cppcheck target
- b3441c5 Refining the cppcheck target
- f0be94a Decomposing ALLSORUCES variable into template-project-misc-variables-declare.cmake
- f732fb3 Introducing the donation notice into the READMEs
- 0520380 the main branch info refine
- 7c505e3 Refining the READMEs to represent single main.cpp file
- a7d1c9b Introducing the appMeson branch info into the READMEs
- 7880f6f Fixing applib on the app branch on the READMEs
- a3cf6c2 Erasing the app branch code
- b1e99d8 Introducing the app branch and refine the master branch
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

[maintenance0.12.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/maintenance0.12.0)
[main0.11.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/main0.11.0)
[main0.10.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/main0.10.0)
[main0.9.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/main0.9.0)
[app0.8.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.8.0)
[app0.7.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.7.0)
[app0.6.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.6.0)
[app0.5.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.5.0)
[app0.4.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.4.0)
[app0.3.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.3.0)
[app0.2.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.2.0)
[v0.1.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/v0.1.0)
