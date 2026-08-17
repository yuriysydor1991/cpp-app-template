# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [appCURLClaude0.10.0] - 2026-08-17

- 5c100c8 Introducing the InsertNewlineAtEOF clang-format option
- 1ac8e98 Introducing the appCURLChatGPT branch info into the READMEs
- bcea280 Introducing the last_response_successfull call into the CURLController
- 2e4c3b0 Hiding the ApplicationContext fields and adding the atomic stop flag
- 5443a74 Moving the linker hardening options out of the compile options
- 5cd03d0 Split the DefaultLogger into a static proxy and a real logger instance
- 4cf7759 Add a Claude API client built on the libcurl and the nlohmann JSON libraries
- f1f08c2 Introducing the external documentation URLs check into the Jenkins pipeline
- 26a8664 Correcting the docker modules path of the documentation
- b198842 Introducing the quick build and the docker starter scripts
- 4b3022d Introducing the quick build and the docker starter scripts
- 28eec3c Making the docker containers run under unprivileged users
- f56e9b6 Formatting the sources with the clang-format
- 4dc67ca Repairing the pipeline code check stages
- 0627660 Introducing the appPGPLOT branch info into the READMEs
- 3701da7 Fixing the Jenkinsfile
- a3a12ab Fix broken cppcheck link in section 5 index
- 6cfcf17 Fix Groovy escape sequences in markdown link checker stage
- b2c2ec3 Rework markdown link checker stage to pure bash
- b9f30fb Add Jenkinsfile stage to detect broken markdown links; fix pre-existing broken links
- daba890 Reorganize doc/sections into section dirs with category grouping
- 9562496 Add an OpenSSL cmake enabler module with SHA-256, HMAC-SHA256 and HTTPS/TLS client code samples
- d36c6b3 Group the enabler documentation under subsections in the READMEs
- 7743cc9 Group the compression branches under a dedicated README section
- 837048e Introducing the appLZMA branch info into the READMEs
- fb01a7c Add a liblzma (XZ Utils) compression library enabler module
- cd43372 Introducing the appZlib branch info into the READMEs
- 9093c7e Add zlib compression usage examples to its enabler documentation
- ca8a76f Replace the redundant PROJECT_NAME CMake variable with CMAKE_PROJECT_NAME
- 1dfdc57 Introducing the appGtkmm4Vulkan branch info into the READMEs
- 3c27ab4 Removing the appGtkmm4Vulkan branch info from the READMEs
- 2e97e0a Introducing the appQt6Vulkan and appGtkmm4Vulkan branches info into the READMEs
- b073c01 Simplifying root CMakeLists.txt
- 0124f8b Introducing the appFirebird branch info into the READMEs
- 034c67f Introducing the appGtkmm4GDBusClient branch info into the READMEs
- 7ea50e1 Introducing the appQt6GLArea branch info into the READMEs
- 4caa8a9 Introducing the appGtkmm4GLArea branch info into the READMEs
- f54a1a4 Splitting the Data Visualization README category into Plots/Graphs and Maps
- 91d2fcd Introducing the applibMeson branch info into the READMEs
- 97a7725 Introducing the zlib and image format cmake enablers with docs
- 00d37e6 Introducing the appSFML branch info into the READMEs
- 24414ad Introducing the appwxWidgets branch info into the READMEs
- 8a6b2bb Introducing the appQt6QtDBusClient branch info into the READMEs
- cb881c0 Introducing the appQt6QtLocation branch info into the READMEs
- e23b963 Introducing the appQt6ChartView branch into the READMEs
- 9ad913d Introducing the appGtkmm4LeafLet and appQt6LeafLet branches info into the READMEs
- 8d53d09 Introducing the COMPONENTS arg for template_project_default_3rdparty_enabler
- c9a1ed9 Removing the SDL3 current marking
- ea96145 Introducing information about the SDL3 branch in the READMEs
- c364fd2 Replacing faulty SimpleLogger mention with the DefaultLogger
- a51d313 Rename the simple logger to DefaultLogger and add top-level log.h tests
- d9ab73b Removing faulty simple_logger mention in the log.h
- 3523079 Add template-specific packager, documentation and registration checks
- 7aa73cd Introducing the appSDBusCxxClient and appSDBusCxxServer branches info into the READMEs
- 63b3f61 Moving Dockerfiles and packagers files into separate subdirs in the misc
- b879b40 Adding .claude dir to .gitignore
- c716bc3 Introducing project structure section Будь ласка, зверніться до адміністратора subsection
- d245e0b Introducing the libMeson branch info into the READMEs
- e58fdc5 Introducing info about newly created branch appOpenCV into READMEs with it's cmake enabler.
- c9ce960 Introducing the CPack's RPM package generator integration
- 37a9f7e Removing unmerged lines in the doc/README.uk_UA.md
- 09e057c Introducing the MS Windows WIX package generation through CPack integration
- ddd593c Introducing the project's FreeBSD pkg package generation support through CPack. Works only on FreeBSD.
- 2d49de7 Deleting REQUIRED marking from the snapcraft's find_program
- 54debff By default disabling the snap package manager
- fe25fac Introducing the snap packager integration with documentation
- 3be8dc5 Introducing and migrating to the template_project_default_3rdparty_enabler cmake function. Making enablers git sources variables modifiable.
- 519fa2a Fixing binaries build
- b02c2e1 Moving all CMake variables declarations into their respectful enablers.
- 6e8f571 Moving Doxygen related CMake variables into doc/CMakeLists.txt file
- 563fea9 Introducing the libxml2 enabler cmake module
- 0950d2f Enhancing the cmake files fs structure
- 13d067d Making docker base image configurable through CMake variables
- 93ae182 Introducing the appPLplot branch info into the READMEs
- 38a8df4 Introducing the MatPlot++ appMatPlotxx branch into the READMEs
- 918b24e Making the cppcheck stage optional due to unstable results
- 85f99a6 Fixing clang-tidy conf misspell
- 0d387f5 Switching off the clang-tydy's unrecognizable AnalyzeTemporaryDtors config param
- 7e0b704 Loggging README's misspell refine
- ce760e0 Grouping and categorising available template flavors links in the READMEs
- 62c2ce6 Renaming properly Nlohmann JSON library CMake enabler file
- e4688e0 Introducing the forgottent Nlohmann JSON library enabler info into the READMEs
- 2aa9649 Decomposing READMEs
- 4e4298e Introducing the ENABLE_LOGS_MICROSECONDS_TIME CMake option in order to be able to disable microseconds in the log messages.
- dd323e1  Introducing the --branch cmd line flag for git clone command in the READMEs
- 3123378 Introducing explicit template altering notice in the READMEs headers
- 0c0981a Optimizing some CMake commands in the README.md
- 551c10d Introducing the appGtkmm4 branch info into the READMEs
- ab3cdb6 Introducing the PlantUML app component diagram into the READMEs
- a464a5d Introducing basic app CTs samples
- 304ab43 Enabling GTest during for CTs
- 03bd7c3 Pointing Jenkins configurable port into standart in-container 8080
- a308233 Making the Jenkins pipeline container and image names configurable
- 09bc949 Introducing basic SimpleLogger CTs with CMake and Jenkins integration
- cf63040 Refining the branches link in the READMEs, introducing gitlab links also
- 27a6225 Specifying the Jenkins container run target in the READMEs
- af57d1b Introducing basic Jenkins pipeline CMake target and Jenkinsfile conf
- e3d562e Fixing typo in the README.md
- 2190dfb Introducing the valgrind callgrind profiler target for the project
- 3304578 Introducing the gprof profiling target
- a43d07a Refining the Dockerfile
- 54c0088 Introducing timeouts to the CURLController download method
- 83026f3 Refining and optimizing CURL controller
- 3d9616a Marking the appCURL branch as current in the branches list
- dbb807e Adding money emoji to donation notice in the READMEs
- 4c14f71 Introducing the appCURL branch info into the READMEs
- 46385d2 Refining the Application class UTs
- a8fe1b6 Implementing basic libcurl downloader wrapper class CURLController
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
- 8f5fc89 Release 0.9.0 2025-06-06

## [app0.9.0] - 2025-03-20

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

[app0.9.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.9.0)
[app0.8.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.8.0)
[app0.7.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.7.0)
[app0.6.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.6.0)
[app0.5.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.5.0)
[app0.4.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.4.0)
[app0.3.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.3.0)
[app0.2.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.2.0)
[v0.1.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/v0.1.0)
