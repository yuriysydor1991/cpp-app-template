# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [appQt60.8.0] - 2025-06-06

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

[appQt60.8.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/appQt60.8.0)
[appQt60.7.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/appQt60.7.0)
[app0.6.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.6.0)
[app0.5.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.5.0)
[app0.4.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.4.0)
[app0.3.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.3.0)
[app0.2.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.2.0)
[v0.1.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/v0.1.0)
