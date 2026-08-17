# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [appMySQLCppConn0.9.0] - 2026-08-17

- a49dd44 Introducing the InsertNewlineAtEOF clang-format option
- 0432ee5 Repairing the mismatched ApplicationContext forward declaration tag
- 746dd02 Introducing the appCURLChatGPT branch info into the READMEs
- 2d4baec Hiding the ApplicationContext fields and adding the atomic stop flag
- ba2ef08 Moving the linker hardening options out of the compile options
- 4cd48ca Split the DefaultLogger into a static proxy and a real logger instance
- efca4a1 Introducing the appCURLClaude branch info into the READMEs
- dbafd66 Introducing the external documentation URLs check into the Jenkins pipeline
- adb5515 Correcting the docker modules path of the documentation
- 5059ab2 Introducing the quick build and the docker starter scripts
- a5ae049 Introducing the quick build and the docker starter scripts
- e9c1902 Making the docker containers run under unprivileged users
- 5c7b74b Formatting the sources with the clang-format
- 575b8e5 Repairing the pipeline code check stages
- 4ea3964 Introducing the appPGPLOT branch info into the READMEs
- 027d353 Fixing the Jenkisfile
- 354aa16 Fix broken cppcheck link in section 5 index
- 1441e13 Fix Groovy escape sequences in markdown link checker stage
- 94d4a94 Rework markdown link checker stage to pure bash
- bf96a64 Add Jenkinsfile stage to detect broken markdown links; fix pre-existing broken links
- 0c18c55 Reorganize doc/sections into section dirs with category grouping
- 1f7bb61 Add an OpenSSL cmake enabler module with SHA-256, HMAC-SHA256 and HTTPS/TLS client code samples
- 7bc60bf Group the enabler documentation under subsections in the READMEs
- d6bbaa3 Group the compression branches under a dedicated README section
- 3d4a8f5 Introducing the appLZMA branch info into the READMEs
- 937e04f Add a liblzma (XZ Utils) compression library enabler module
- 6ff1fd5 Introducing the appZlib branch info into the READMEs
- 302093a Add zlib compression usage examples to its enabler documentation
- 3621f99 Replace the redundant PROJECT_NAME CMake variable with CMAKE_PROJECT_NAME
- 643dac1 Introducing the appGtkmm4Vulkan branch info into the READMEs
- 0761017 Removing the appGtkmm4Vulkan branch info from the READMEs
- 36fcc5d Introducing the appQt6Vulkan and appGtkmm4Vulkan branches info into the READMEs
- 7abccf9 Simplifying root CMakeLists.txt
- a190205 Introducing the appFirebird branch info into the READMEs
- d8995a0 Introducing the appGtkmm4GDBusClient branch info into the READMEs
- 20b6a93 Introducing the appQt6GLArea branch info into the READMEs
- b4f6f3d Introducing the appGtkmm4GLArea branch info into the READMEs
- 76b10dd Splitting the Data Visualization README category into Plots/Graphs and Maps
- e2920cf Introducing the applibMeson branch info into the READMEs
- 93d4570 Introducing the zlib and image format cmake enablers with docs
- f64b8f0 Introducing the appSFML branch info into the READMEs
- e5fabe3 Introducing the appwxWidgets branch info into the READMEs
- acafc8b Introducing the appQt6QtDBusClient branch info into the READMEs
- cf23cd5 Introducing the appQt6QtLocation branch info into the READMEs
- ee8c2e5 Introducing the appQt6ChartView branch into the READMEs
- 394e40c Introducing the appGtkmm4LeafLet and appQt6LeafLet branches info into the READMEs
- cbabee6 Introducing the COMPONENTS arg for template_project_default_3rdparty_enabler
- dbb2af6 Removing the SDL3 current marking
- 6acdb0a Introducing information about the SDL3 branch in the READMEs
- d1d7313 Replacing faulty SimpleLogger mention with the DefaultLogger
- b85e3a9 Rename the simple logger to DefaultLogger and add top-level log.h tests
- 3f68777 Removing faulty simple_logger mention in the log.h
- fa9fd19 Add template-specific packager, documentation and registration checks
- 682045c Introducing the appSDBusCxxClient and appSDBusCxxServer branches info into the READMEs
- 1ab5f3b Moving Dockerfiles and packagers files into separate subdirs in the misc
- 812db1c Adding .claude dir to .gitignore
- d87047a Introducing project structure section Будь ласка, зверніться до адміністратора subsection
- f8ea775 Introducing the libMeson branch info into the READMEs
- 70de7ea Introducing info about newly created branch appOpenCV into READMEs with it's cmake enabler.
- fb7c680 Introducing the CPack's RPM package generator integration
- f9d8f47 Removing unmerged lines in the doc/README.uk_UA.md
- c6361af Introducing the MS Windows WIX package generation through CPack integration
- 6dcf0f6 Introducing the project's FreeBSD pkg package generation support through CPack. Works only on FreeBSD.
- b247093 Deleting REQUIRED marking from the snapcraft's find_program
- ea34ec5 By default disabling the snap package manager
- 63c0784 Introducing the snap packager integration with documentation
- 665fb56 Introducing and migrating to the template_project_default_3rdparty_enabler cmake function. Making enablers git sources variables modifiable.
- bd00c5f Moving all CMake variables declarations into their respectful enablers.
- 2249c70 Moving Doxygen related CMake variables into doc/CMakeLists.txt file
- f1b1272 Introducing the libxml2 enabler cmake module
- 659aa6e Enhancing the cmake files fs structure
- 35f95bd Making docker base image configurable through CMake variables
- ecb4302 Introducing the appPLplot branch info into the READMEs
- 79833d6 Introducing the MatPlot++ appMatPlotxx branch into the READMEs
- 0e2b355 Making the cppcheck stage optional due to unstable results
- 74a4609 Fixing clang-tidy conf misspell
- ebec234 Switching off the clang-tydy's unrecognizable AnalyzeTemporaryDtors config param
- ef7f421 Loggging README's misspell refine
- 0aaea79 Grouping and categorising available template flavors links in the READMEs
- fac6f91 Renaming properly Nlohmann JSON library CMake enabler file
- 5369fb2 Introducing the forgottent Nlohmann JSON library enabler info into the READMEs
- a4c9e25 Translating required MySQL packages README.us_UA.md section.
- 0874464 Decomposing READMEs
- e17eead Introducing the ENABLE_LOGS_MICROSECONDS_TIME CMake option in order to be able to disable microseconds in the log messages.
- cb1e83b  Introducing the --branch cmd line flag for git clone command in the READMEs
- 6a677cc Introducing explicit template altering notice in the READMEs headers
- d218374 Optimizing some CMake commands in the README.md
- 90a7681 Introducing the appGtkmm4 branch info into the READMEs
- c439a46 Introducing the PlantUML app component diagram into the READMEs
- 03c79b4 Code formatting applied
- e3a3f46 Introducing new app CT for MySQLController
- 0536fec Fixing app CTs
- 4d2fbb1 Enabling GTest during for CTs
- fd0d362 Pointing Jenkins configurable port into standart in-container 8080
- 8afa6f5 Making the Jenkins pipeline container and image names configurable
- bba4c3f Introducing basic app CTs samples
- de216c1 Introducing basic SimpleLogger CTs with CMake and Jenkins integration
- 71cf73c Refining the branches link in the READMEs, introducing gitlab links also
- bd4524c Specifying the Jenkins container run target in the READMEs
- 0073b1e Introducing basic Jenkins pipeline CMake target and Jenkinsfile conf
- 1d4002d Fixing typo in the README.md
- 82087f6 Introducing the valgrind callgrind profiler target for the project
- 6ca40f5 Introducing the gprof profiling target
- 0388d9b Adding money emoji to donation notice in the READMEs
- 3fd3ea5 Introducing the appCURL branch info into the READMEs
- 1613279 Introducing the enabling libcurl section into the READMEs
- 1fa0d97 Introducing the libcurl cmake enabler script
- b8f0694 Moving the DEFAULT_LOG_FILE_PATH macro declaration into severity-macro-consts.h
- accdc58 Refining unit tests to match the new log code
- 4f9ec7a Introducing a custom log file cmd param for the executable
- a35e9db Introducing the DEFAULT_LOG_FILE_PATH cmake var and cpp macro to specify default dst log file location
- 1427bf6 Introducing the CMDParamNames class to encapsulate CMD params names
- db1d355 Introducing some marketing sentences in the README's goal section
- 8e357e6 Introducing the cmake/enablers subdirectory to locate the 3rd-party dependencies
- 238cc60 Renaming emplate-project-make-GTest-available - template-project-GTest-enabler
- 636e6c1 Introducing the NLohmann JSON library enabler cmake module
- a988124 Fixing the sanitizers cmake file in the READMEs
- 7117aed Avoiding unnecessary badly portable localtime_r usage
- 7b229ea Introducing the thread id into simple logger
- 51e6f4d Avoiding backward time in the simple logs
- bca668f Avoiding final log multiple str fetches
- 9cdf216 Refining the log current timestamp method, increasing thread safety
- 8de6aeb Introducing the CMake configurable log severity messages compilation switch
- 6cfe386 Introducing the appBoostLog branch info into the READMEs
- 37e2fce Hiding the compile options cmake files under separate directory
- d151cf6 Enhancing sanitizers combinations and new cmake dir for ones
- ebabe1c Introducing the sanitizers enabling info into the READMEs
- 2567ce9 Removing redundant cmake traces messages
- 258124a Introducing the GCC compiler sanitizers
- bfbb30e Refined issues in the Docker READMEs doc
- 07d9da1 Refining the Docker target for the MySQLCppConn
- a2eb6ec Separating the Docker single container build and run targets
- 03ab315 Introducing the Docker single run container target.
- 35da5f2 Adding project neatness to the READMEs
- 902279f Introducing the appLog4Cpp5 branch info into the READMEs
- 2b6dc5f Enabling multithreading in the flatpak boost build
- d20b809 Implementing the logging macros and a simple logger to perform log messaging
- df6d4d9 Introducing the appMongoDBCpp4 branch info into the READMEs
- 28fd073 Making the flatpak source json conf file configurable during cmake conf stage
- ccd02ce Introducing the libmysqlcppconn7v5 into the dev variables dependencies
- 642cab9 Refining the deb cmake info for cpack
- 84b7370 Introducing the appSQLiteCpp3 branch info into the READMEs
- d124c76 Refining the flatpak target final
- cc8c53e Refining the flatpak target workflow second
- 1a4d137 Refining the flatpak target workflow
- 3f57339 Refining the cppcheck code warnings
- 3cc86ec Refining Application UTs
- f173c54 Refining the ApplicationContext mock
- d7ad68b Introducing the gitlab mirror into the READMEs
- 1ebc3d7 Marking the appMySQLCppConn as the current branch
- 3414a0f Introducing the appMySQLCppConn branch info into the READMEs
- c5dc4c4 Introducing the donation notice into the READMEs
- def876a Extracting and introducing the QueryMaker class for assembling the SQL queries.
- 2b879f7 Extracting the query execution method into execute_query method
- 1116e12 Implementing the connection routine with a simple date string fetcher query
- db72f93 Introducing the basic MySQLController class hierarchy and it's integration
- 7ac2b51 Altering the ApplicationContext
- 83a5a81 Transferring the ApplicationContext with DB extra fields from appPgSQLxx branch
- 43b121f Introducing the libmysqlcppconn-dev as required package into the README.md
- a51e4a6 Transfering the IDBConnection class from appPgSQLxx
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

[app0.8.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.8.0)
[app0.7.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.7.0)
[app0.6.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.6.0)
[app0.5.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.5.0)
[app0.4.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.4.0)
[app0.3.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.3.0)
[app0.2.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.2.0)
[v0.1.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/v0.1.0)
