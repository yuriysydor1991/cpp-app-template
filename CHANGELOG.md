# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [appQt6QtDBusClient0.10.0] - 2026-08-17

- 665e4b3 Introducing the InsertNewlineAtEOF clang-format option
- ef1383f Introducing the appCURLChatGPT branch info into the READMEs
- 9ac480b Adding the missing PRIVATE keyword into the real default logger linking
- f0db512 Hiding the ApplicationContext fields and adding the atomic stop flag
- 1714c02 Moving the linker hardening options out of the compile options
- e18c97e Split the DefaultLogger into a static proxy and a real logger instance
- 220b809 Introducing the appCURLClaude branch info into the READMEs
- b141fc6 Introducing the external documentation URLs check into the Jenkins pipeline
- 55fcb8a Correcting the docker modules path of the documentation
- eee8755 Introducing the quick build and the docker starter scripts
- 739bc40 Introducing the quick build and the docker starter scripts
- c3b2a37 Making the docker containers run under unprivileged users
- 282d74c Formatting the sources with the clang-format
- b0ae5d2 Repairing the pipeline code check stages
- 68d1805 Introducing the appPGPLOT branch info into the READMEs
- c3699f8 Fixing the Jenkinsfile
- 2a84400 Fix broken cppcheck link in section 5 index
- 44fbc97 Fix Groovy escape sequences in markdown link checker stage
- f0099bd Rework markdown link checker stage to pure bash
- d691d63 Add Jenkinsfile stage to detect broken markdown links; fix pre-existing broken links
- 4930fe0 Reorganize doc/sections into section dirs with category grouping
- dc8bdfb Add an OpenSSL cmake enabler module with SHA-256, HMAC-SHA256 and HTTPS/TLS client code samples
- a46664a Register the missing tests in the misc/Jenkinsfile
- 648366d Group the enabler documentation under subsections in the READMEs
- 9ef2bd6 Group the compression branches under a dedicated README section
- 783be05 Fix the misc/Jenkinsfile checkout branch to the appQt6QtDBusClient branch name
- 9405146 Introducing the appLZMA branch info into the READMEs
- 045ec53 Add a liblzma (XZ Utils) compression library enabler module
- 9070ce4 Introducing the appZlib branch info into the READMEs
- 3b4f567 Add zlib compression usage examples to its enabler documentation
- 6e2f6d0 Replace the redundant PROJECT_NAME CMake variable with CMAKE_PROJECT_NAME
- 709de20 Introducing the appGtkmm4Vulkan branch info into the READMEs
- 1ed47cf Removing the appGtkmm4Vulkan branch info from the READMEs
- 5c4b45b Introducing the appQt6Vulkan and appGtkmm4Vulkan branches info into the READMEs
- ecf2908 Simplifying root CMakeLists.txt
- 6978d85 Introducing the appFirebird branch info into the READMEs
- df748f0 Introducing the appGtkmm4GDBusClient branch info into the READMEs
- c4fc625 Introducing the appQt6GLArea branch info into the READMEs
- 823212e Introducing the appGtkmm4GLArea branch info into the READMEs
- e2e9f42 Splitting the Data Visualization README category into Plots/Graphs and Maps
- 5d037f9 Introducing the applibMeson branch info into the READMEs
- 751700d Introducing the zlib and image format cmake enablers with docs
- fad8abb Introducing the appSFML branch info into the READMEs
- a120867 Introducing the appwxWidgets branch info into the READMEs
- d3a46ae Drop the QML GUI from appQt6QtDBusClient; log the D-Bus system info instead
- fd55e7e Introducing the appQt6QtDBusClient branch with a native QtDBus system info client
- c3cf260 Introducing the appQt6QtLocation branch info into the READMEs
- 7d6c756 Introducing the appQt6ChartView branch into the READMEs
- 82249dc Introducing the appGtkmm4LeafLet and appQt6LeafLet branches info into the READMEs
- 083286b Introducing the COMPONENTS arg for template_project_default_3rdparty_enabler
- cb13509 Removing the SDL3 current marking
- 164edbd Introducing information about the SDL3 branch in the READMEs
- 24f7d12 Fixing unmerged Jenkinsfile
- 7cdf985 Rename the simple logger to DefaultLogger and add top-level log.h tests
- e8c917a Removing faulty simple_logger mention in the log.h
- 885410a Add template-specific packager, documentation and registration checks
- 86b0d92 Introducing the appSDBusCxxClient and appSDBusCxxServer branches info into the READMEs
- 615eab3 Moving Dockerfiles and packagers files into separate subdirs in the misc
- 4f7dafb Adding .claude dir to .gitignore
- 7c57624 Introducing project structure section Будь ласка, зверніться до адміністратора subsection
- 6a22fde Introducing the libMeson branch info into the READMEs
- 434993a Introducing info about newly created branch appOpenCV into READMEs with it's cmake enabler.
- 0524881 Introducing the CPack's RPM package generator integration
- 2ae943f Removing unmerged lines in the doc/README.uk_UA.md
- d369525 Introducing the MS Windows WIX package generation through CPack integration
- ef8b594 Introducing the project's FreeBSD pkg package generation support through CPack. Works only on FreeBSD.
- 2a293f8 Deleting REQUIRED marking from the snapcraft's find_program
- 20e2cfc By default disabling the snap package manager
- 4362a0c Introducing the snap packager integration with documentation
- 026f65b Introducing the Qt6 enabler file to allow it's usage across multiple components of interest
- b11021c Introducing and migrating to the template_project_default_3rdparty_enabler cmake function. Making enablers git sources variables modifiable.
- 16986ed Moving all CMake variables declarations into their respectful enablers.
- 847696a Moving Doxygen related CMake variables into doc/CMakeLists.txt file
- 4c3d61e Introducing the libxml2 enabler cmake module
- 7fcb19f Enhancing the cmake files fs structure
- d366d02 Making docker base image configurable through CMake variables
- 7394e3e Introducing the appPLplot branch info into the READMEs
- 3e6e9b0 Introducing the MatPlot++ appMatPlotxx branch into the READMEs
- 324ab4c Making the clang-tidy Jenkinsfile stage optional for the pipeline
- fa82874 root src dir try for clan-tidy II
- ccdcb1e root src dir try for clan-tidy
- 72be2d6 Excluding the build directory from clang-tidy analysis.
- cad827f Making the cppcheck stage optional due to unstable results
- 3f2751e Fixing clang-tidy conf misspell
- 1a8b05d Switching off the clang-tydy's unrecognizable AnalyzeTemporaryDtors config param
- 954f171 Loggging README's misspell refine
- e614051 Grouping and categorising available template flavors links in the READMEs
- 8cd3c6c Renaming properly Nlohmann JSON library CMake enabler file
- cc69ec1 Introducing the forgottent Nlohmann JSON library enabler info into the READMEs
- 6aa5192 Removed duplicated requirements.
- 06f660f Introducing the required Qt6 packages in the READMEs.
- 2e4041e Returning the Qt6 required packages list
- d0ff6d1 Decomposing READMEs
- a717d78 Refining the QML build system with separate qt_add_qml_module modules declaration.
- 9f445c1 Adding missing Qt6 QML packages to READMEs
- c8f0965 Introducing the ENABLE_LOGS_MICROSECONDS_TIME CMake option in order to be able to disable microseconds in the log messages.
- a615cb6  Introducing the --branch cmd line flag for git clone command in the READMEs
- 90d2ee9 Introducing explicit template altering notice in the READMEs headers
- 12892cd Optimizing some CMake commands in the README.md
- e22e7d0 Introducing the appGtkmm4 branch info into the READMEs
- 18fe599 Introducing the PlantUML app component diagram into the READMEs
- a151b0a Enabling GTest during for CTs
- 418be7f Adding Qt6Initer mock to the app CTs
- a50c9eb Pointing Jenkins configurable port into standart in-container 8080
- 6be4c06 Making the Jenkins pipeline container and image names configurable
- 24d016a Introducing basic app CTs samples
- c183ecd Introducing basic SimpleLogger CTs with CMake and Jenkins integration
- 0064d7e Refining the branches link in the READMEs, introducing gitlab links also
- 29e225f Introducing the basic DefaultWelcome component sample
- 5cc9104 Replacing wrong freeglut mention in the README.ua_UA.md with a Qt6 packages
- fc98b93 Specifying the Jenkins container run target in the READMEs
- 02a174a Introducing basic Jenkins pipeline CMake target and Jenkinsfile conf
- bf6fbfa Incrementing version to 0.10.0
- 183594c Release appQt60.9.0 at 2025-09-08

## [appQt60.9.0] - 2025-09-08

- 141985f Fixing typo in the README.md
- f5bc559 Introducing the valgrind callgrind profiler target for the project
- 2bdd9c3 Introducing the gprof profiling target
- 3a06007 Adding money emoji to donation notice in the READMEs
- 3093ccf Introducing the appCURL branch info into the READMEs
- a59f05b Introducing the enabling libcurl section into the READMEs
- 78b5195 Introducing the libcurl cmake enabler script
- 9da8ae1 Moving the DEFAULT_LOG_FILE_PATH macro declaration into severity-macro-consts.h
- 1632298 Refining unit tests to match the new log code
- 2c3856a Introducing a custom log file cmd param for the executable
- efcc4e0 Introducing the DEFAULT_LOG_FILE_PATH cmake var and cpp macro to specify default dst log file location
- 5ea75c0 Introducing the CMDParamNames class to encapsulate CMD params names
- 79da049 Introducing some marketing sentences in the README's goal section
- 2c41781 Introducing the cmake/enablers subdirectory to locate the 3rd-party dependencies
- a8545c9 Renaming emplate-project-make-GTest-available - template-project-GTest-enabler
- b15babc Introducing the NLohmann JSON library enabler cmake module
- d58f0f9 Fixing the sanitizers cmake file in the READMEs
- 1103143 Avoiding unnecessary badly portable localtime_r usage
- 0610361 Introducing the thread id into simple logger
- baa46e2 Avoiding backward time in the simple logs
- 6f03357 Avoiding final log multiple str fetches
- b0e30c2 Refining the log current timestamp method, increasing thread safety
- 5313892 Introducing the CMake configurable log severity messages compilation switch
- fe1abb6 Introducing the appBoostLog branch info into the READMEs
- 712551b Hiding the compile options cmake files under separate directory
- 6d10760 Enhancing sanitizers combinations and new cmake dir for ones
- ed87682 Introducing the sanitizers enabling info into the READMEs
- 62187d9 Removing redundant cmake traces messages
- a7c0386 Introducing the GCC compiler sanitizers
- 123cdb6 Decomposing the reqources paths into specialized class
- a276e1b Renaming the templateQt6app namespace into the more short Qt6i
- 44e5964 introducing the Application's instance failure exit UT
- 1c3672b Pasing the whole application context instance to the Qt6 controller Qt6Initer
- c19319d Incrementing version to 0.9.0

## [appQt60.8.0] - 2025-06-06

- d9aeeb7 Release appQt60.8.0 2025-06-06
- e671fb9 Refined issues in the Docker READMEs doc
- 376a0d4 Refining the Docker target for the Qt6
- 985e78c Separating the Docker single container build and run targets
- 92fd745 Introducing the Docker single run container target.
- cbcefde Adding project neatness to the READMEs
- dfd0532 Introducing the appLog4Cpp5 branch info into the READMEs
- d2d7bfb Implementing the logging macros and a simple logger to perform log messaging
- 7575c6b Introducing the appMongoDBCpp4 branch info into the READMEs
- f4b6417 Making the flatpak source json conf file configurable during cmake conf stage
- 2b1aac5 Introducing the Qt6 dependencies into the dep-variables for cpack
- 44051f5 Refining the deb cmake info for cpack
- b6cec47 Introducing the appSQLiteCpp3 branch info into the READMEs
- dbc0e9a Refining the ApplicationContext mock
- 7a392b6 Introducing the gitlab mirror into the READMEs
- 0060ba1 Introducing the appMySQLCppConn branch info into the READMEs
- b216bcb Introducing the appBoostBeast branch info into the READMEs
- 4c41a3c Explicitly specifying the combining of the template branches
- b8e29cf introducing the appPgSQLxx branch into the READMEs
- 9701986 Introducing a new appWt4 branch info into the READMEs
- 608080f Introducing the error exit code for a cppcheck target
- 0379b5c Refinining the cppcheck target
- 158da47 Introducing the donation notice into the READMEs
- d8e3d37 Sharing screen for thr flatpak package to show window
- f7b8dc9 Reintroducing lost applib branch in README.md
- 6b339b7 Introducing the appMeson branch info into the READMEs
- 8c01f65 Refining the branch info
- 927544b Replacing flatpak SDK from the KDE in READMEs
- 5020d71 Replacing the platform and SDK with one from kde 6.8
- 52a43a8 Applied clang-format
- 98c1cb6 Introducing the flatpak sections into the READMEs
- 49b02c0 Introducing the flatpak package creation from the template source.
- 74df07d Erasing the /analyze from the default MSVC compile options
- 06c56a6 Introducing the DEB package gen info in the READMEs
- e3f2bcf Introducing the cpack configuration for the deb package generation
- 03e4417 Introducing the LICENSE file with free of use license and notice
- 6bcffdd Introducing the appSDL2 branch into the READMEs
- d44e58d Introducing clang-tidy
- ac3f852 Introducing the FreeGlut/OpenGL appFreeGlut branch info into READMEs
- 2e6be64 Avoiding the compilation warnings at the UTEST_CommandLineParser
- df9a502 Introducing MSVC extra compile options for warnings
- 1bf1d01 Adding MSVC settings file to the .gitignore
- 452ae08 Adding the out directory for MSVC into .gitignore
- 6f8c73d Erasing merging syms in READMEs
- 5d92e2d Specifying the appGtkmm3Glade branch in the READMEs
- f5d62c9 Introducing the appGtkmm3 branch info into the READMEs
- a736514 Replacing the /usr/bin prefix parameter with right /usr in installation section
- d83d0d2 Introducing the lib branch info into the READMEs

## [appQt60.7.0] - 2025-03-15

- cde5c67 Release appQt60.7.0 2025-03-15
- 789ffb9 Decomposing Qt6Initer class into separate virtual method.
- 5d8f1f6 Refining READMEs
- 41e363b Refining the Application UTs
- 8565a19 Erasing redundant Qt headers
- ff4a6d7 Replacing accidental Ukrainian word inserted to README.md
- 26e3781 Refining Application UTs
- 360716e Marking the correct current branch in the READMEs
- 3738044 Introducing the appQt6 branch in READMEs
- ad36932 Introducing the Qt6 window component
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

[appQt60.9.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/appQt60.9.0)
[appQt60.8.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/appQt60.8.0)
[appQt60.7.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/appQt60.7.0)
[app0.6.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.6.0)
[app0.5.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.5.0)
[app0.4.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.4.0)
[app0.3.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.3.0)
[app0.2.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.2.0)
[v0.1.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/v0.1.0)
