# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [appFreeGlut0.10.0] - 2026-11-08

- e032e4d Removing the destination OS from the AppImage package name
- 7c60bc0 Introducing the STT branches info into the READMEs
- 36f1673 Replacing the CMAKE_SOURCE_DIR/CMAKE_BINARY_DIR by the PROJECT_SOURCE_DIR/PROJECT_BINARY_DIR
- 11ad66f Introducing the appWebAssembly branch info into the READMEs
- 272f3a1 Introducing the appLlamaCPP branch info into the READMEs
- fe0d6c7 Introducing the TTS branches info into the READMEs
- 0ea117e Introducing the destination OS into the package names
- c108861 Synchronizing the template flavors list of the READMEs
- bee98ed Refreshing the shared library cache after the from-source installs
- 6271604 Failing the flavor CI test stages which match no tests
- faa482c Converting the flavor link calls of the project binary to the keyword signature
- a3b4374 Fixing the cppcheck findings of the new signals handler, tests and log mock
- b9f1023 Updating the app component diagram to the signals handlers design
- c289265 Renumbering the custom command line parameters section numbered 4-6 twice
- d65cdff Documenting the built in command line options and the usage errors
- 6bf1cef Testing the application with the real command line arguments
- 250bcd7 Parsing the command line before the log file initialization
- dfb3593 Exiting with a failure status on the command line usage errors
- ad74978 Fixing the missing option value raising the version flag instead of the help one
- 3e318df Fixing the CommandLineParser test assertions which could not fail
- 04e54b7 Fixing the log mock LOG_INIT forwarding into the LOG_INIT_DEFAULTS mock
- d92ac71 Restoring the previous signal dispositions on the signals handler uninstall
- fb59fd9 Leaving the SIGTTIN and SIGTTOU signals to the shell job control
- 0b91414 Removing the nonexistent module path directories and cppcheck suppression
- d1d1075 Fixing the zlib gzip file example ignoring the read and close errors
- c366155 Fixing the flatpak requirements section naming an outdated SDK version
- e89ebb7 Documenting the ENABLE_COMPONENT_TESTS option of the test builds
- 4d9f7ba Listing every linked doc section in the requirements and build index pages
- d58cb42 Fixing the documentation links pointing into the other language
- 52151cd Fixing the stale file paths named in the documentation
- 14cc1d7 Fixing the flatpak target failing on its repeated build
- f467dcf Fixing the snap command path ignoring the install prefix
- d061e4e Fixing the documentation install which needed a manual Doxygen-doc build
- 9b5e996 Skipping the Doxygen and callgrind targets when their tools are missing
- b89b734 Installing the packager tools into the Jenkins pipeline image
- 510db34 Replacing the libjpeg-turbo download fallback with a clear configure error
- 8389cef Fixing the libavif download fallback stopping without the system libyuv
- caedb7a Pinning the third-party download fallbacks to their release tags
- 893528c Failing the CI test stages which match no tests
- ba6aff5 Fixing the Jenkins doc sections linked check skipping the section directories
- 84f47ae Replacing the broken OpenSSL download fallback with a clear configure error
- 89abf41 Fixing the mixed target_link_libraries signatures on the project binary
- 08e6aad Fixing the MAX_LOG_LEVEL option help text error level value
- db6205f Fixing the logger level filter tests which could not fail
- 79544dd Fixing the log macros to expand into single statements
- 4d65238 Fixing the logger data races on the log file reopening and the level
- de36885 Fixing the log file open failure aborting the process
- f5227bc Splitting the CTEST_DefaultLogger helper classes into own files
- 951b607 Splitting the packages install scripts per OS release
- 1163801 Hiding the ApplicationContext fields and adding the atomic stop flag
- 03cd8aa Replacing int flag with a bool for the CommandLineParser
- 9ed0c59 Forwarding the host X display into the docker single run
- 39e519b Synchronizing the drifted cppcheck enabler and suppressions with the app branch
- 4e11032 Declaring the snap build and stage packages of the toolkit
- c1a2e15 Fixing the DEB package dependencies to the linked runtime libraries
- cf36306 Fixing the FreeGlut application id and the docs naming the app one
- da51be7 Removing the unused GLEW and GLM packages
- 6bdb667 Removing the freeglut3 package missing from the newer Debian and Ubuntu releases
- 27aa432 Naming the FreeGlut window after the project instead of the binary path
- 224c844 Removing the unused GLU and GLUT compatibility headers
- 33fcd32 Fixing the FreeGlut scene lacking its depth buffer and scaling by zero
- 1cebcce Fixing the FreeGlut main loop ignoring the stop signals
- d6e3be0 Fixing the installed binary not finding the Steamworks library on GNU/Linux
- d95e268 Pinning the stb_truetype fetch to a fixed stb commit
- 817e51c Fixing the HarfBuzz FreeType glue missing with a system FreeType
- f7606c3 Fixing the Jolt static MSVC runtime clashing with the project's DLL one
- 50e4f96 Fixing the Box2D system probe taking the incompatible 2.x releases
- c855e10 Introducing the VERSION argument into the 3rd party enabler function
- 48cd1fa Renaming the FreeGlutIniter component into the FreeGlutController
- 7b7dafe Replacing the unreachable GNU gettext site link with its Savannah page
- e9cb708 Introducing the destination CPU architecture into the package names
- 76e1a2c Introducing the appGettext branch info into the READMEs
- b3ce610 Introducing the appDarknetXX branch info into the READMEs
- 1876f6d Introducing the RedHat packages install script
- 13d80f4 Introducing the appWhisperCPP branch info into the READMEs
- 5b19bd8 Introducing the FreeBSD packages install script
- e112415 Introducing the appV8 branch info into the READMEs
- b2a5a93 Erasing the build sources and trees of the docker images
- d287262 Introducing the debug clang-format script
- 41ba8ba Introducing the 3D assets sections into the READMEs
- 8652652 Introducing the Poly Haven, Kenney, Quaternius and Khronos glTF Sample Assets CMake enablers
- 86c92f8 Resetting the inherited signals dispositions in the signals handlers tests
- ca2dac3 Introducing the binary hardening options section into the READMEs
- 3347594 Introducing the binary hardening compile and link options
- b680cfd Introducing the GitLab CI/CD pipeline section into the READMEs
- 88a612b Introducing the GitLab CI/CD pipeline mirroring the Jenkinsfile
- ebf71ce Introducing the GitHub Actions CI pipeline section into the READMEs
- 9872cb2 Introducing the GitHub Actions CI pipeline mirroring the Jenkinsfile
- 30ddc33 Correcting the appQt6QtDBusClient branch description in the READMEs
- 5683887 Introducing the desktop application packaging switch
- f8384c2 Introducing the font type usage examples into the font enabler docs
- a894155 Introducing the FreeType, HarfBuzz, Fontconfig, msdfgen and stb_truetype CMake enablers
- cd8dc33 Limiting the documentation checks to the repository own markdown files
- bd7e5e6 Excluding the GCC own include directories from the clang-tidy search path
- 01b5492 Accepting the 405 documentation URLs
- 4d7bef1 Spacing out the branch entries in the READMEs
- b37d381 Rewording the DOCKER_HOST environment requirement in the docker docs
- 5b97227 Removing the DOCKER_HOST variables from the docker enablers
- 89fe232 Dropping the absent freeglut3 package from the Docker image
- 4b36bca Excluding the build trees from the Docker build context
- 1d09cbf Retrying the unreachable documentation URLs and accepting the 403 ones
- d85271d Introducing the --rebuild flag into the Jenkins docker scripts
- 7b2286c Rebuilding the image from its base on the Jenkins pipeline force rebuild
- 14dfdc6 Introducing the audio assets branches info into the READMEs
- e8af571 Splitting the signals handlers per category and covering the pause, reload, user defined and ignored signals
- d3ca6b6 Introducing the app signals handlers subcomponent
- 80a6e8c Introducing the Steamworks SDK CMake enabler
- a4165f5 Introducing the Box2D and the Jolt Physics CMake enablers
- 5d1827f Declaring the main function argv parameter as an array
- 3479d66 Moving the packagers templates into the per-packager directories
- 436778d Dropping the packagers and the development tools from the packages install list
- db17ec3 The destination CPU architecture of the AppImage package name
- b5fb444 Picking the CPack AppImage enabler since the CMake 4.2 and dropping the debug banners
- 214bb91 Extracting the AppImage enabler pick into its own general enabler
- 1301d38 Selecting the AppImage packager enabler by the CMake version
- 43cf92d Introducing the CPack based AppImage packager enabler
- d108507 Introducing the AppImage packager
- d7e4444 Introducing the --install flag into the packager build scripts
- ad17a20 Renaming the packages install script and adding the Ubuntu one
- a4eab81 Introducing the target architecture into the flatpak package name
- fe3fa2f Introducing the AppStream metainfo file into the flatpak package
- ce07fc8 Consuming the install directory variables the flatpak-builder passes
- d87e943 Introducing the required packages install script
- 53b3d4a Installing the flatpak build dependencies from the flathub remote
- 283c774 Dropping the redundant build step from the packager scripts
- a5bae3f Introducing the per packager build scripts
- 9d0251e Introducing the appCFITSIO branch info into the READMEs
- bd36ee2 Make the compile time log level gate really gate
- 6ccf484 Introducing the appGtkmm4Libadwaita branch info into the READMEs
- ca46a52 Pinning the log message stream to the classic locale
- e871907 Decomposing the IApplication descendants into the applications subcomponent
- 1610080 Introducing the appFontAwesome branch info into the READMEs
- 0a6f660 Introducing the debug test script and its --test parameter
- 5f1ac11 Incrementing version to appFreeGlut0.10.0
- b1eecc6 Release appFreeGlut0.9.0 at 2026-08-17

## [appFreeGlut0.9.0] - 2026-08-17

- 323d5ca Introducing the InsertNewlineAtEOF clang-format option
- 725d372 Introducing the appCURLChatGPT branch info into the READMEs
- e483f7b Hiding the ApplicationContext fields and adding the atomic stop flag
- 910da6b Moving the linker hardening options out of the compile options
- ab9dd19 Split the DefaultLogger into a static proxy and a real logger instance
- eef5021 Introducing the appCURLClaude branch info into the READMEs
- b0f68ff Introducing the external documentation URLs check into the Jenkins pipeline
- 67a1cce Correcting the docker modules path of the documentation
- 43a7f04 Introducing the quick build and the docker starter scripts
- 42d07dd Introducing the quick build and the docker starter scripts
- 0658b37 Making the docker containers run under unprivileged users
- cd61da7 Formatting the sources with the clang-format
- bd7633c Repairing the pipeline code check stages
- cabd197 Introducing the appPGPLOT branch info into the READMEs
- e9375d4 Fixing the Jenkinsfile
- 7fe33a3 Fix broken cppcheck link in section 5 index
- e17f6c8 Fix Groovy escape sequences in markdown link checker stage
- 83ca4ae Rework markdown link checker stage to pure bash
- 8c3c5ce Add Jenkinsfile stage to detect broken markdown links; fix pre-existing broken links
- d63ac23 Reorganize doc/sections into section dirs with category grouping
- 038c398 Add an OpenSSL cmake enabler module with SHA-256, HMAC-SHA256 and HTTPS/TLS client code samples
- 37711b7 Group the enabler documentation under subsections in the READMEs
- 4f749f9 Group the compression branches under a dedicated README section
- 28adce4 Introducing the appLZMA branch info into the READMEs
- 6f82aa1 Add a liblzma (XZ Utils) compression library enabler module
- 6897228 Introducing the appZlib branch info into the READMEs
- 24aae77 Add zlib compression usage examples to its enabler documentation
- 55405af Replace the redundant PROJECT_NAME CMake variable with CMAKE_PROJECT_NAME
- a7664ba Introducing the appGtkmm4Vulkan branch info into the READMEs
- 105f64e Removing the appGtkmm4Vulkan branch info from the READMEs
- 9e0babf Introducing the appQt6Vulkan and appGtkmm4Vulkan branches info into the READMEs
- 1e32027 Simplifying root CMakeLists.txt
- 0399032 Introducing the appFirebird branch info into the READMEs
- b1337a9 Introducing the appGtkmm4GDBusClient branch info into the READMEs
- e202aa8 Introducing the appQt6GLArea branch info into the READMEs
- 44d3371 Introducing the appGtkmm4GLArea branch info into the READMEs
- 330432f Splitting the Data Visualization README category into Plots/Graphs and Maps
- cf1ff0a Introducing the applibMeson branch info into the READMEs
- 38c4341 Introducing the zlib and image format cmake enablers with docs
- 1bc4c40 Introducing the appSFML branch info into the READMEs
- eded869 Introducing the appwxWidgets branch info into the READMEs
- acab67f Introducing the appQt6QtDBusClient branch info into the READMEs
- 5f1d5a9 Introducing the appQt6QtLocation branch info into the READMEs
- 58477c2 Introducing the appQt6ChartView branch into the READMEs
- 4c20b05 Introducing the appGtkmm4LeafLet and appQt6LeafLet branches info into the READMEs
- 49d2ebf Introducing the COMPONENTS arg for template_project_default_3rdparty_enabler
- 80bcddc Removing the SDL3 current marking
- 62e184d Introducing information about the SDL3 branch in the READMEs
- 69b7193 Replacing faulty SimpleLogger mention with the DefaultLogger
- e622b11 Rename the simple logger to DefaultLogger and add top-level log.h tests
- 5a94af9 Removing faulty simple_logger mention in the log.h
- 02bed16 Add template-specific packager, documentation and registration checks
- 037f7b1 Introducing the appSDBusCxxClient and appSDBusCxxServer branches info into the READMEs
- 3634bb8 Moving Dockerfiles and packagers files into separate subdirs in the misc
- f635750 Adding .claude dir to .gitignore
- a38c398 Introducing project structure section Будь ласка, зверніться до адміністратора subsection
- 0f710cb Introducing the libMeson branch info into the READMEs
- 6675d3b Introducing info about newly created branch appOpenCV into READMEs with it's cmake enabler.
- 58071b7 Introducing the CPack's RPM package generator integration
- ee62917 Removing unmerged lines in the doc/README.uk_UA.md
- b2799bf Introducing the MS Windows WIX package generation through CPack integration
- 2126cf8 Introducing the project's FreeBSD pkg package generation support through CPack. Works only on FreeBSD.
- 160443a Deleting REQUIRED marking from the snapcraft's find_program
- d0a624b By default disabling the snap package manager
- 096d95b Introducing the snap packager integration with documentation
- ec14bc2 Introducing and migrating to the template_project_default_3rdparty_enabler cmake function. Making enablers git sources variables modifiable.
- c209719 Moving all CMake variables declarations into their respectful enablers.
- de3fbcd Moving Doxygen related CMake variables into doc/CMakeLists.txt file
- c381303 Introducing the libxml2 enabler cmake module
- e53cade Enhancing the cmake files fs structure
- c4ab773 Making docker base image configurable through CMake variables
- 1d15a18 Introducing the appPLplot branch info into the READMEs
- 4f979c3 Introducing the MatPlot++ appMatPlotxx branch into the READMEs
- ad0e600 Making the cppcheck stage optional due to unstable results
- 78833a0 Fixing clang-tidy conf misspell
- 1477156 Switching off the clang-tydy's unrecognizable AnalyzeTemporaryDtors config param
- 49f5a03 Loggging README's misspell refine
- 49c306b Grouping and categorising available template flavors links in the READMEs
- 4cb0358 Renaming properly Nlohmann JSON library CMake enabler file
- d7b4873 Introducing the forgottent Nlohmann JSON library enabler info into the READMEs
- 214bdb4 Additional READMEs refine.
- 904c1a0 Decomposing READMEs
- 2dc05a5 Introducing the ENABLE_LOGS_MICROSECONDS_TIME CMake option in order to be able to disable microseconds in the log messages.
- b0febdb  Introducing the --branch cmd line flag for git clone command in the READMEs
- e5cd6b4 Introducing explicit template altering notice in the READMEs headers
- 35a2e95 Optimizing some CMake commands in the README.md
- 85fe238 Introducing the appGtkmm4 branch info into the READMEs
- c2545b2 Introducing the PlantUML app component diagram into the READMEs
- d839010 Fixing app CTs
- 6ea9178 Enabling GTest during for CTs
- 8ad7b49 Pointing Jenkins configurable port into standart in-container 8080
- 12d1771 Making the Jenkins pipeline container and image names configurable
- ff6832d Introducing basic app CTs samples
- a4c5334 Introducing basic SimpleLogger CTs with CMake and Jenkins integration
- a245cbb Refining the branches link in the READMEs, introducing gitlab links also
- 74c1ce8 Specifying the Jenkins container run target in the READMEs
- b4d072d Erasing unknown package freeglut3
- 8740384 Fixing typos in Jenkins target
- ebafbc9 Introducing basic Jenkins pipeline CMake target and Jenkinsfile conf
- e65314d Fixing typo in the README.md
- d034f2f Introducing the valgrind callgrind profiler target for the project
- 10ca829 Introducing the gprof profiling target
- b09fa90 Adding money emoji to donation notice in the READMEs
- cab156b Introducing the appCURL branch info into the READMEs
- 904b0e2 Introducing the enabling libcurl section into the READMEs
- 3328cb1 Introducing the libcurl cmake enabler script
- c25244d Moving the DEFAULT_LOG_FILE_PATH macro declaration into severity-macro-consts.h
- 3ac1593 Refining unit tests to match the new log code
- 58fdd8e Introducing a custom log file cmd param for the executable
- ad91b91 Introducing the DEFAULT_LOG_FILE_PATH cmake var and cpp macro to specify default dst log file location
- ca85cbe Introducing the CMDParamNames class to encapsulate CMD params names
- 0ba51ba Introducing some marketing sentences in the README's goal section
- e50ec20 Introducing the cmake/enablers subdirectory to locate the 3rd-party dependencies
- ac53e7a Renaming emplate-project-make-GTest-available - template-project-GTest-enabler
- 52b7cb7 Introducing the NLohmann JSON library enabler cmake module
- 35ee89a Fixing the sanitizers cmake file in the READMEs
- 8167c16 Avoiding unnecessary badly portable localtime_r usage
- 54c7a45 Introducing the thread id into simple logger
- 69c83d6 Avoiding backward time in the simple logs
- dba934a Avoiding final log multiple str fetches
- 4aaf394 Refining the log current timestamp method, increasing thread safety
- 076d0b9 Introducing the CMake configurable log severity messages compilation switch
- 546a1d2 Introducing the appBoostLog branch info into the READMEs
- 5673302 Hiding the compile options cmake files under separate directory
- c81165b Enhancing sanitizers combinations and new cmake dir for ones
- d640b9e Introducing the sanitizers enabling info into the READMEs
- 0a90ba4 Removing redundant cmake traces messages
- 7f95c21 Introducing the GCC compiler sanitizers
- dd30c14 Incrementing version to 0.9.0
- fcbd54c Release appFreeGlut0.8.0 2025-06-06

## [appFreeGlut0.8.0] - 2025-06-06

- ab67529 Refined issues in the Docker READMEs doc
- 39f441f Adjusting the Docker target for freeglut packages
- 00c1899 Separating the Docker single container build and run targets
- 64a9d3e Introducing the Docker single run container target.
- be42965 Adding project neatness to the READMEs
- 8c2e404 Introducing the appLog4Cpp5 branch info into the READMEs
- cc0b14f Implementing the logging macros and a simple logger to perform log messaging
- 49ef8ff Introducing the appMongoDBCpp4 branch info into the READMEs
- 8a10fb3 Making the flatpak source json conf file configurable during cmake conf stage
- e80bc3c Refining the deb cmake info for cpack
- ef22c45 Introducing the appSQLiteCpp3 branch info into the READMEs
- 8546e7d Refining the ApplicationContext mock
- b7bbb10 Introducing the gitlab mirror into the READMEs
- 82bd40a Introducing the appMySQLCppConn branch info into the READMEs
- b9c736c Introducing the appBoostBeast branch info into the READMEs
- 2d42e5c Explicitly specifying the combining of the template branches
- e826ec0 introducing the appPgSQLxx branch into the READMEs
- 1e7e5b0 Introducing a new appWt4 branch info into the READMEs
- b9b1c08 Introducing the error exit code for a cppcheck target
- 60b5c7c Refinining the cppcheck target
- d65a3f2 Introducing the donation notice into the READMEs
- fff391e Changing the flatpak application URL
- 321e65b Refining the flatpak target
- 08c4c68 Introducing the flatpak sections into the READMEs
- eb80b84 Introducing the flatpak package creation from the template source.
- a0f0f1b Introducing the appMeson branch info into the READMEs
- 1f6413d Refining top branch info in READMEs
- 159a816 Erasing the /analyze from the default MSVC compile options
- 4f00514 Introducing MSVC extra compile options for warnings
- c360fa2 Introducing the DEB package gen info in the READMEs
- 0ed06ab Introducing the cpack configuration for the deb package generation
- 0f30cfe Introducing the LICENSE file with free of use license and notice
- 472299f Introducing the appSDL2 branch into the READMEs
- 18693fd Fixing implicit double convertion for clang-tidy
- 5ed240f Introducing clang-tidy
- 520b6f7 Avoiding the compilation warnings at the UTEST_CommandLineParser
- a2c8e29 Fixing missing packages in the requirements READMEs
- 6954e53 Incrementing version to 0.8.0

## [appFreeGlut0.7.0] - 2025-03-19

- afe8dc9 Release appFreeGlut0.7.0 2025-03-19
- 0496dc9 Adding markup for introduced info.
- 7c2acd8 Introducing the FreeGlutIniter class into the READMEs
- 01c3e36 Refining Application UTs
- 257622f Introducing the FreeGlut/OpenGL appFreeGlut branch info into READMEs
- dc4ab28 Introducing a FreeGlut subdirectory with initer class.
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

[appFreeGlut0.10.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/appFreeGlut0.10.0)
[appFreeGlut0.9.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/appFreeGlut0.9.0)
[appFreeGlut0.8.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/appFreeGlut0.8.0)
[appFreeGlut0.7.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/appFreeGlut0.7.0)
[app0.6.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.6.0)
[app0.5.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.5.0)
[app0.4.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.4.0)
[app0.3.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.3.0)
[app0.2.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.2.0)
[v0.1.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/v0.1.0)
