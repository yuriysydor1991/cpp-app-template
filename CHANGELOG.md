# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [applib0.10.0] - 2025-09-08

- 6290c4e Repairing segflt on the App's UTs
- 8eb03ba Refining Application's UTs
- 1c4a74e Including the main Config.cmake file into installation candidates
- 8758a28 Library infrastructure reorg. Introducing basic installable CMake module.
- cae6ce6 Fixing typo in the README.md
- 9be1e05 Introducing the valgrind callgrind profiler target for the project
- 363dd55 Introducing the gprof profiling target
- 2ede6fa Adding money emoji to donation notice in the READMEs
- 29b35a6 Introducing the appCURL branch info into the READMEs
- b5a186d Introducing the enabling libcurl section into the READMEs
- 72c984e Introducing the libcurl cmake enabler script
- 09a78df Moving the DEFAULT_LOG_FILE_PATH macro declaration into severity-macro-consts.h
- 37d345c Refining unit tests to match the new log code
- 3d7add8 Introducing a custom log file cmd param for the executable
- d470e5c Introducing the DEFAULT_LOG_FILE_PATH cmake var and cpp macro to specify default dst log file location
- 5a38cf0 Introducing the CMDParamNames class to encapsulate CMD params names
- b454c72 Introducing some marketing sentences in the README's goal section
- aa05140 Introducing the cmake/enablers subdirectory to locate the 3rd-party dependencies
- ceb5b6e Renaming emplate-project-make-GTest-available - template-project-GTest-enabler
- e4227d0 Introducing the NLohmann JSON library enabler cmake module
- fc07827 Fixing the sanitizers cmake file in the READMEs
- 88ddbf2 Avoiding unnecessary badly portable localtime_r usage
- 5ca30e4 Introducing the thread id into simple logger
- 1afa9bb Avoiding backward time in the simple logs
- edf6d90 Avoiding final log multiple str fetches
- 33b6962 Refining the log current timestamp method, increasing thread safety
- 9e8999d Introducing the CMake configurable log severity messages compilation switch
- 038e9c9 Introducing the appBoostLog branch info into the READMEs
- 7ec2633 Hiding the compile options cmake files under separate directory
- 2166e5a Enhancing sanitizers combinations and new cmake dir for ones
- 6485392 Introducing the sanitizers enabling info into the READMEs
- 2190f74 Removing redundant cmake traces messages
- a8833e9 Introducing the GCC compiler sanitizers
- f2f2653 Release applib0.9.0 2025-06-06

## [applib0.9.0] - 2025-06-06

- 8c15c24 Incrementing version to 0.9.0
- 2bf709a Refined issues in the Docker READMEs doc
- b8fc7d2 Separating the Docker single container build and run targets
- 40c7eb0 Introducing the Docker single run container target.
- c1eb4e4 Adding project neatness to the READMEs
- da45334 Introducing the appLog4Cpp5 branch info into the READMEs
- 62f169f Implementing the logging macros and a simple logger to perform log messaging
- 70d9c05 Introducing the appMongoDBCpp4 branch info into the READMEs
- 93b7563 Making the flatpak source json conf file configurable during cmake conf stage
- 448ed29 Refining the deb cmake info for cpack
- 619ccc8 Introducing the appSQLiteCpp3 branch info into the READMEs
- bf40e16 Refining the ApplicationContext mock
- fff404c Introducing the gitlab mirror into the READMEs
- 9d9904c Introducing the appMySQLCppConn branch info into the READMEs
- 369ff0f Introducing the appBoostBeast branch info into the READMEs
- 7cfd03c Explicitly specifying the combining of the template branches
- bbb5879 introducing the appPgSQLxx branch into the READMEs
- ced3566 Introducing a new appWt4 branch info into the READMEs
- fbd0a34 Introducing the error exit code for a cppcheck target
- 1a30076 Refining the cppcheck target
- d74a56a Introducing the donation notice into the READMEs
- 0ed43d8 Introducing the flatpak sections into the READMEs
- 78c1bfc Introducing the flatpak package creation from the template source.
- 837f4e1 Introducing the appMeson branch info into the READMEs
- da1bcfc Refining branch info
- ac72506 Erasing the /analyze from the default MSVC compile options
- 48d4668 Introducing the DEB package gen info in the READMEs
- 2735d3e Introducing the cpack configuration for the deb package generation
- c5c9978 Introducing the LICENSE file with free of use license and notice
- 9a3cb05 Introducing the appSDL2 branch into the READMEs
- f9ff528 Introducing clang-tidy
- b6a5c7b Erasing redundant libraries installation info
- afd6b57 Introducing the FreeGlut/OpenGL appFreeGlut branch info into READMEs
- 0fa45ef Release applib0.8.0 2025-03-17

## [applib0.8.0] - 2025-03-17

- d8149e0 Introducing MSVC extra compile options for warnings
- ffaeb75 Adding MSVC settings file to the .gitignore
- 543a7fa Avoiding the compilation warnings at the UTEST_CommandLineParser
- 94c12a5 Introducing MS Windows tools install description into READMEs
- 8ca7ba4 Adding the out directory for MSVC into .gitignore
- 35e34fd Specifying the appGtkmm3Glade branch in the READMEs
- 55c4a42 Introducing the appGtkmm3 branch info into the READMEs
- 4062f58 Replacing the /usr/bin prefix parameter with right /usr in installation section
- eb1a749 Introducing the lib branch info into the READMEs
- 7e8d539 Introducing the appQt6 branch in READMEs
- a6d72dc Introducing Doxygen doc with translated README as main page facility
- 73e5d0d Introducing COMPILE_WARNINGS_AS_ERRORS and ENABLE_COMPILER_CODE_ANALYZER CMake vars.
- d4c6dc1 Incrementing version to 0.8.0
- ead330e Inserting forgoten realease link in the CHANGELOG

## [applib0.7.0] - 2025-03-14

- f5b1d13 Release applib0.7.0 2025-03-17
- 473bb31 Refining typos in uk_UA README
- ab45738 Refining all the READMEs
- cfa03d8 Introducing the sample LibMain UTs
- c019bd3 Refining lib UTs
- 2230643 refining LibraryFacade tests
- 5b23447 Introducing LibFactory UTs
- f67a3ca Specifying the library targets and formatting the code.
- 11f5b6d Introducing LibraryFacade UTs.
- 95092ff Moving ILib to the facade folder.
- d02674e Incrementing version to 0.7.0 and changing description

## [applib0.6.0] - 2025-03-13

- 3b43b68 Release applib0.6.0 2025-03-13 21:54
- 8635ccb Release applib0.6.0 2025-03-13
- d0a0eed Introducing explanatory comments for new LibraryContext class fields.
- 34988bb Introducing ApplicationContext2LibraryContext UTs with moved general mocks
- f83084b Removing forgotten debug #error
- d978ec1 Specifying translation documents for the root README under the doc
- c41e944 Specifying the source file for the PROJECT_BINARY_NAME CMake variable
- 78e90c7 Some README.md refinements
- 1f46f37 Refining SOLID comment for Implement code straight away
- 89de1b3 Introducing the ApplicationContext2LibraryContext class with mocks and refined Application UTs
- 492817a Introducing additional library related info into README.md
- 6f48e44 Marking applib branch as current in the README.md
- 522ccfc Introducing multibranch info into the root README.md
- 3f11e47 Marking LibraryContext destructure as virtual to allow subclassing
- 5a8b53b Renaming library facade namespace to templatelib0
- 27bc62a Fixing wrong article.
- 96e24aa Applying clang-format
- 71c3c6d Refining UTEST_Application unit test to pass.
- c223375 Introducing library mocks for the app component
- 45cb5fb Refining library classes explanatory comments.
- 2d2c974 Marking library facade cpp file as private.
- 8cac51b Introducing library component facade and default implementation.
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

[applib0.10.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/applib0.10.0)
[applib0.9.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/applib0.9.0)
[applib0.8.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/applib0.8.0)
[applib0.7.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/applib0.7.0)
[applib0.6.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/applib0.6.0)
[app0.5.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.5.0)
[app0.4.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.4.0)
[app0.3.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.3.0)
[app0.2.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.2.0)
[v0.1.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/v0.1.0)

