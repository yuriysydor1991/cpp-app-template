# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [appGtkmm4Vulkan0.11.0] - 2026-08-17

- 66e7ae1 Introducing the InsertNewlineAtEOF clang-format option
- 7dd6d2e Introducing the appCURLChatGPT branch info into the READMEs
- b6ddc00 Hiding the ApplicationContext fields and adding the atomic stop flag
- 779ffe8 Moving the linker hardening options out of the compile options
- f08e68b Split the DefaultLogger into a static proxy and a real logger instance
- 51c7964 Introducing the appCURLClaude branch info into the READMEs
- 2b12af4 Introducing the external documentation URLs check into the Jenkins pipeline
- 51f89b5 Correcting the docker modules path of the documentation
- 6e16e2c Introducing the quick build and the docker starter scripts
- 56121e9 Introducing the quick build and the docker starter scripts
- 5a50605 Making the docker containers run under unprivileged users
- 2944ffb Formatting the sources with the clang-format
- 28fe41c Repairing the pipeline code check stages
- 15f3d60 Introducing the appPGPLOT branch info into the READMEs
- 26f2ac2 Fixing the Jenkinsfile
- ed45a1d Fix broken cppcheck link in section 5 index
- c9e4a9f Fix Groovy escape sequences in markdown link checker stage
- 7020f48 Rework markdown link checker stage to pure bash
- cde4a36 Add Jenkinsfile stage to detect broken markdown links; fix pre-existing broken links
- 5b95274 Reorganize doc/sections into section dirs with category grouping
- 6d50f0e Add an OpenSSL cmake enabler module with SHA-256, HMAC-SHA256 and HTTPS/TLS client code samples
- 956e998 Register the missing tests in the misc/Jenkinsfile
- 14a0f6e Group the enabler documentation under subsections in the READMEs
- cf2df3e Group the compression branches under a dedicated README section
- 45011d4 Fix the misc/Jenkinsfile checkout branch to the appGtkmm4Vulkan branch name
- b716202 Introducing the appLZMA branch info into the READMEs
- 3be46d0 Add a liblzma (XZ Utils) compression library enabler module
- d4f6970 Introducing the appZlib branch info into the READMEs
- ffb1b4a Add zlib compression usage examples to its enabler documentation
- 3c38664 Replace the redundant PROJECT_NAME CMake variable with CMAKE_PROJECT_NAME
- eb4f8b9 Introducing the appGtkmm4Vulkan branch info into the READMEs
- 561593e Render the appGtkmm4Vulkan window through Vulkan via a dma-buf
- 132a046 Removing the appGtkmm4Vulkan branch info from the READMEs
- 25dbb4d Introducing the appQt6Vulkan and appGtkmm4Vulkan branches info into the READMEs
- df3d5e6 Introduce the appGtkmm4Vulkan branch (Vulkan device info + blank black GTK window)
- 9bb1a59 Simplifying root CMakeLists.txt
- 5539cbe Introducing the appFirebird branch info into the READMEs
- f2a98a1 Introducing the appGtkmm4GDBusClient branch info into the READMEs
- eb5a96e Introducing the appQt6GLArea branch info into the READMEs
- 9ab2f74 Introducing the appGtkmm4GLArea branch info into the READMEs
- a31e1c7 Splitting the Data Visualization README category into Plots/Graphs and Maps
- 20ba7f7 Introducing the applibMeson branch info into the READMEs
- 5f50650 Introducing the zlib and image format cmake enablers with docs
- f411087 Introducing the appSFML branch info into the READMEs
- f5f4f6b Introducing the appwxWidgets branch info into the READMEs
- ef26324 Introducing the appQt6QtDBusClient branch info into the READMEs
- 852e10c Introducing the appQt6QtLocation branch info into the READMEs
- 666bb03 Introducing the appQt6ChartView branch into the READMEs
- ff84069 Introducing the appGtkmm4LeafLet and appQt6LeafLet branches info into the READMEs
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
