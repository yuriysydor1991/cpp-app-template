# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [appBoostLog0.10.0] - 2026-08-17

- 7cf3c07 Introducing the InsertNewlineAtEOF clang-format option
- 7539091 Introducing the appCURLChatGPT branch info into the READMEs
- 02725a5 Hiding the ApplicationContext fields and adding the atomic stop flag
- 6e06df2 Moving the linker hardening options out of the compile options
- c19f839 Introducing the appCURLClaude branch info into the READMEs
- 291cf47 Introducing the external documentation URLs check into the Jenkins pipeline
- 0bcbe93 Correcting the docker modules path of the documentation
- d3ec4af Introducing the quick build and the docker starter scripts
- 8c4b673 Introducing the quick build and the docker starter scripts
- f23a2b3 Making the docker containers run under unprivileged users
- 90351fa Repairing the appBoostLog branch build
- 92a430f Repairing the pipeline code check stages
- 905e0b7 Introducing the appPGPLOT branch info into the READMEs
- a402285 Fixing redundant curly braces in the Jenkinsfile
- 5acc554 Inserting missing Jenkinsfile booleans
- 8781277 Fixing the Jenkinsfile
- e9a4307 Fix broken cppcheck link in section 5 index
- 8d63c74 Fix Groovy escape sequences in markdown link checker stage
- 70ddef3 Rework markdown link checker stage to pure bash
- 0030f2a Add Jenkinsfile stage to detect broken markdown links; fix pre-existing broken links
- 1fc35e4 Reorganize doc/sections into section dirs with category grouping
- 09658bc Add an OpenSSL cmake enabler module with SHA-256, HMAC-SHA256 and HTTPS/TLS client code samples
- 8e20657 Register the missing tests in the misc/Jenkinsfile
- 3e036ee Group the enabler documentation under subsections in the READMEs
- 3c5e033 Group the compression branches under a dedicated README section
- 5c871de Introducing the appLZMA branch info into the READMEs
- 5c2c687 Add a liblzma (XZ Utils) compression library enabler module
- 5da25f7 Introducing the appZlib branch info into the READMEs
- 8e66fb1 Add zlib compression usage examples to its enabler documentation
- b653142 Replace the redundant PROJECT_NAME CMake variable with CMAKE_PROJECT_NAME
- 5f7f861 Introducing the appGtkmm4Vulkan branch info into the READMEs
- c74fcb1 Removing the appGtkmm4Vulkan branch info from the READMEs
- 789d0c8 Introducing the appQt6Vulkan and appGtkmm4Vulkan branches info into the READMEs
- 53ed424 Simplifying root CMakeLists.txt
- d60dc3a Introducing the appFirebird branch info into the READMEs
- 4a84868 Introducing the appGtkmm4GDBusClient branch info into the READMEs
- 2c13c4c Introducing the appQt6GLArea branch info into the READMEs
- 2b35d92 Introducing the appGtkmm4GLArea branch info into the READMEs
- c7fcb15 Splitting the Data Visualization README category into Plots/Graphs and Maps
- 7fb86b1 Introducing the applibMeson branch info into the READMEs
- bbe07e6 Introducing the log facade component test (CTEST_log) into appBoostLog
- 51ca661 Introducing the zlib and image format cmake enablers with docs
- 1a14adf Introducing the appSFML branch info into the READMEs
- 180e06f Introducing the appwxWidgets branch info into the READMEs
- e9bab32 Introducing the appQt6QtDBusClient branch info into the READMEs
- 928ccd1 Introducing the appQt6QtLocation branch info into the READMEs
- ac0ad61 Introducing the appQt6ChartView branch into the READMEs
- 7c2dbf5 Introducing the appGtkmm4LeafLet and appQt6LeafLet branches info into the READMEs
- 4db82ad Introducing the COMPONENTS arg for template_project_default_3rdparty_enabler
- e183d00 Introducing the appSDBusCxxClient and appSDBusCxxServer branches info into the READMEs
- 98b13f5 Moving Dockerfiles and packagers files into separate subdirs in the misc
- 46ca302 Adding .claude dir to .gitignore
- ccbfaff Introducing project structure section Будь ласка, зверніться до адміністратора subsection
- 1c48242 Introducing the libMeson branch info into the READMEs
- 4e7b187 Introducing info about newly created branch appOpenCV into READMEs with it's cmake enabler.
- e6bf46f Introducing the CPack's RPM package generator integration
- a2c365e Removing unmerged lines in the doc/README.uk_UA.md
- 4e48da5 Introducing the MS Windows WIX package generation through CPack integration
- 4454d2d Introducing the project's FreeBSD pkg package generation support through CPack. Works only on FreeBSD.
- 8579c4f Deleting REQUIRED marking from the snapcraft's find_program
- 4860e6d By default disabling the snap package manager
- cd6103a Introducing the snap packager integration with documentation
- ff8074e Introducing and migrating to the template_project_default_3rdparty_enabler cmake function. Making enablers git sources variables modifiable.
- fffa482 Moving all CMake variables declarations into their respectful enablers.
- 2218db0 Moving Doxygen related CMake variables into doc/CMakeLists.txt file
- 2fc9ea7 Introducing the libxml2 enabler cmake module
- 9860599 Enhancing the cmake files fs structure
- dba8f96 Making docker base image configurable through CMake variables
- 9201d74 Introducing the appPLplot branch info into the READMEs
- ad69015 Introducing the MatPlot++ appMatPlotxx branch into the READMEs
- f9a651d Making the cppcheck stage optional due to unstable results
- 41b9eee Fixing clang-tidy conf misspell
- cf4bc17 Switching off the clang-tydy's unrecognizable AnalyzeTemporaryDtors config param
- 061621f Loggging README's misspell refine
- 1c8e84b Grouping and categorising available template flavors links in the READMEs
- 419afe4 Renaming properly Nlohmann JSON library CMake enabler file
- 7f638c2 Introducing the forgottent Nlohmann JSON library enabler info into the READMEs
- 424de28 Replacing app branch to the appBoostLog branch in the en_US cloning project documentation section.
- 8e0884e Decomposing READMEs
- ad6e076  Introducing the --branch cmd line flag for git clone command in the READMEs
- 016d264 Introducing explicit template altering notice in the READMEs headers
- 7ccab10 Optimizing some CMake commands in the README.md
- 9f3400e Introducing the appGtkmm4 branch info into the READMEs
- 1cf6055 Introducing the PlantUML app component diagram into the READMEs
- 4fa6db8 Enabling GTest during for CTs
- 03015d5 Erasing absent SimpleLogger CTs stage from Jenkinsfile
- 663ae7b Pointing Jenkins configurable port into standart in-container 8080
- 45f73fa Making the Jenkins pipeline container and image names configurable
- 09f4746 Introducing basic app CTs samples
- d938554 Refining the branches link in the READMEs, introducing gitlab links also
- 8a11b40 Specifying the Jenkins container run target in the READMEs
- 108de02 Introducing basic Jenkins pipeline CMake target and Jenkinsfile conf
- 38ccb59 Fixing typo in the README.md
- 9c56e4d Introducing the valgrind callgrind profiler target for the project
- 3d59cad Introducing the gprof profiling target
- 0b9241d Adding money emoji to donation notice in the READMEs
- 61038d6 Introducing the appCURL branch info into the READMEs
- f3a3160 Introducing the enabling libcurl section into the READMEs
- 3350316 Introducing the libcurl cmake enabler script
- d825883 Introducing the CMDParamNames class to encapsulate CMD params names
- 0211fea Introducing some marketing sentences in the README's goal section
- 2cbec5d Introducing the cmake/enablers subdirectory to locate the 3rd-party dependencies
- 16c738d Renaming emplate-project-make-GTest-available - template-project-GTest-enabler
- 0b178bf Introducing the NLohmann JSON library enabler cmake module
- c2a2de4 Fixing the sanitizers cmake file in the READMEs
- 518aac3 Introducing the thread id into the logging messages
- 1c559a5 Introducing the CMake configurable log severity messages compilation switch
- d4dcfcc Reintroducing the LOG_BODY macro
- 3c83455 Introducing the boost all dev libs to the deb package dependency
- 359fef3 Refining the flatpak target
- 3c81f84 Refining the Docker single run target
- 4ed9207 Marking the appBoostLog branch as the current in the READMEs
- f2d0e4c Introducing the appBoostLog branch info into the READMEs
- dbb0b2a Implementing a basic boost log controller with LOGx macro integrations
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
