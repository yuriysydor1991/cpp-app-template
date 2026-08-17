# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [appSDL20.8.0] - 2026-08-17

- aaa2e38 Introducing the InsertNewlineAtEOF clang-format option
- 5bf1ed6 Introducing the appCURLChatGPT branch info into the READMEs
- 997c240 Hiding the ApplicationContext fields and adding the atomic stop flag
- 51cb0a7 Moving the linker hardening options out of the compile options
- 91dc8ca Split the DefaultLogger into a static proxy and a real logger instance
- c88d519 Introducing the appCURLClaude branch info into the READMEs
- 965473d Introducing the external documentation URLs check into the Jenkins pipeline
- 026e264 Correcting the docker modules path of the documentation
- 57061cd Introducing the quick build and the docker starter scripts
- a3acb68 Introducing the quick build and the docker starter scripts
- 1517c06 Making the docker containers run under unprivileged users
- c9512bc Formatting the sources with the clang-format
- 1c3d128 Repairing the pipeline code check stages
- b68a39e Introducing the appPGPLOT branch info into the READMEs
- 28e9ed7 Fixing the Jenkinsfile
- 0ceecb7 Fix broken cppcheck link in section 5 index
- 5435456 Fix Groovy escape sequences in markdown link checker stage
- 3a1a6bd Rework markdown link checker stage to pure bash
- 5043a87 Add Jenkinsfile stage to detect broken markdown links; fix pre-existing broken links
- 9496142 Reorganize doc/sections into section dirs with category grouping
- 1b84e37 Add an OpenSSL cmake enabler module with SHA-256, HMAC-SHA256 and HTTPS/TLS client code samples
- 6e2df61 Group the enabler documentation under subsections in the READMEs
- 3e9fd00 Group the compression branches under a dedicated README section
- 790f680 Introducing the appLZMA branch info into the READMEs
- e0560e2 Add a liblzma (XZ Utils) compression library enabler module
- 4924762 Introducing the appZlib branch info into the READMEs
- fe15584 Add zlib compression usage examples to its enabler documentation
- 341a4a4 Replace the redundant PROJECT_NAME CMake variable with CMAKE_PROJECT_NAME
- b5120fb Introducing the appGtkmm4Vulkan branch info into the READMEs
- 96e0d9a Removing the appGtkmm4Vulkan branch info from the READMEs
- da0e12a Introducing the appQt6Vulkan and appGtkmm4Vulkan branches info into the READMEs
- aa5efe8 Simplifying root CMakeLists.txt
- 910455b Introducing the appFirebird branch info into the READMEs
- 83b01e9 Introducing the appGtkmm4GDBusClient branch info into the READMEs
- 90f3602 Introducing the appQt6GLArea branch info into the READMEs
- e79f02a Introducing the appGtkmm4GLArea branch info into the READMEs
- 2a1fc8e Splitting the Data Visualization README category into Plots/Graphs and Maps
- b2232ad Introducing the applibMeson branch info into the READMEs
- 9c717e7 Introducing the zlib and image format cmake enablers with docs
- cdf0a0a Introducing the appSFML branch info into the READMEs
- 4f096b5 Introducing the appwxWidgets branch info into the READMEs
- 16636b6 Introducing the appQt6QtDBusClient branch info into the READMEs
- 2c1ec37 Introducing the appQt6QtLocation branch info into the READMEs
- 82efaf5 Introducing the appQt6ChartView branch into the READMEs
- dc30d70 Introducing the appGtkmm4LeafLet and appQt6LeafLet branches info into the READMEs
- 8dd3ea1 Introducing the COMPONENTS arg for template_project_default_3rdparty_enabler
- e746803 Refining the SDL2 enabler
- 429dfd6 Introducing information about the SDL3 branch in the READMEs
- 3fa0d58 Registering missing tests in the Jenkinsfile
- 40a447e Replacing faulty SimpleLogger mention with the DefaultLogger
- 8c402eb Rename the simple logger to DefaultLogger and add top-level log.h tests
- 4c6c6f3 Removing faulty simple_logger mention in the log.h
- 7dd0ef2 Add template-specific packager, documentation and registration checks
- b0f312d Introducing the appSDBusCxxClient and appSDBusCxxServer branches info into the READMEs
- c81b1b1 Moving Dockerfiles and packagers files into separate subdirs in the misc
- fbd5fbc Adding .claude dir to .gitignore
- 7ec3a3b Introducing project structure section Будь ласка, зверніться до адміністратора subsection
- 468c6be Extracting the SDL2 setup into a dedicated cmake enabler
- a7a8a0c Fixing flatpak build, extracting SDL2 packages doc and adding SDL2 tests
- 2446f0c Introducing the libMeson branch info into the READMEs
- bdc8403 Introducing info about newly created branch appOpenCV into READMEs with it's cmake enabler.
- 653aee4 Introducing the CPack's RPM package generator integration
- de2aff4 Removing unmerged lines in the doc/README.uk_UA.md
- 08e24f8 Introducing the MS Windows WIX package generation through CPack integration
- 47e4c53 Introducing the project's FreeBSD pkg package generation support through CPack. Works only on FreeBSD.
- 05ef866 Deleting REQUIRED marking from the snapcraft's find_program
- 69a2b28 By default disabling the snap package manager
- 61abe38 Introducing the snap packager integration with documentation
- e2bc76b Introducing and migrating to the template_project_default_3rdparty_enabler cmake function. Making enablers git sources variables modifiable.
- 4c90c44 Moving all CMake variables declarations into their respectful enablers.
- 5220971 Moving Doxygen related CMake variables into doc/CMakeLists.txt file
- 1dde36c Introducing the libxml2 enabler cmake module
- d036756 Enhancing the cmake files fs structure
- 10fd3be Making docker base image configurable through CMake variables
- 7faa909 Introducing the appPLplot branch info into the READMEs
- e4d79ba Introducing the MatPlot++ appMatPlotxx branch into the READMEs
- b1b7032 Making the clang-tidy Jenkinsfile stage optional for the pipeline
- f492d06 Making the cppcheck stage optional due to unstable results
- 105cc3d Fixing clang-tidy conf misspell
- 217ba78 Switching off the clang-tydy's unrecognizable AnalyzeTemporaryDtors config param
- d60885e Loggging README's misspell refine
- 67aa477 Grouping and categorising available template flavors links in the READMEs
- 6b5a160 Renaming properly Nlohmann JSON library CMake enabler file
- 1e3ab09 Introducing the forgottent Nlohmann JSON library enabler info into the READMEs
- 7184b1a Decomposing READMEs
- b56bdf9 Introducing the ENABLE_LOGS_MICROSECONDS_TIME CMake option in order to be able to disable microseconds in the log messages.
- 6cd3da1  Introducing the --branch cmd line flag for git clone command in the READMEs
- 9fc23bd Introducing explicit template altering notice in the READMEs headers
- 2ab3862 Optimizing some CMake commands in the README.md
- 7c97331 Introducing the appGtkmm4 branch info into the READMEs
- 828fb72 Introducing the PlantUML app component diagram into the READMEs
- ec4f3b2 Fixing app CT
- 5eb027f Enabling GTest during for CTs
- 9dd66b5 Pointing Jenkins configurable port into standart in-container 8080
- 48af5ff Making the Jenkins pipeline container and image names configurable
- 7e68903 Introducing basic app CTs samples
- 44240f4 Introducing basic SimpleLogger CTs with CMake and Jenkins integration
- e1e7bcf Refining the branches link in the READMEs, introducing gitlab links also
- 6ca94dd Specifying the Jenkins container run target in the READMEs
- 3f5bc71 Introducing basic Jenkins pipeline CMake target and Jenkinsfile conf
- 3221fcf Fixing typo in the README.md
- 8fddf95 Introducing the valgrind callgrind profiler target for the project
- 978572d Introducing the gprof profiling target
- e66064f Adding money emoji to donation notice in the READMEs
- 62081ab Introducing the appCURL branch info into the READMEs
- 38d9413 Introducing the enabling libcurl section into the READMEs
- 07a770f Introducing the libcurl cmake enabler script
- c954a44 Moving the DEFAULT_LOG_FILE_PATH macro declaration into severity-macro-consts.h
- 5e6b753 Refining unit tests to match the new log code
- c16b303 Introducing a custom log file cmd param for the executable
- 0fb0e6e Introducing the DEFAULT_LOG_FILE_PATH cmake var and cpp macro to specify default dst log file location
- e844b7f Introducing the CMDParamNames class to encapsulate CMD params names
- 1937295 Introducing some marketing sentences in the README's goal section
- 2219cc4 Introducing the cmake/enablers subdirectory to locate the 3rd-party dependencies
- 24892b2 Renaming emplate-project-make-GTest-available - template-project-GTest-enabler
- 337160d Introducing the NLohmann JSON library enabler cmake module
- fc71032 Fixing the sanitizers cmake file in the READMEs
- 7d9414f Avoiding unnecessary badly portable localtime_r usage
- 7802f20 Introducing the thread id into simple logger
- 7ac182f Avoiding backward time in the simple logs
- e857259 Avoiding final log multiple str fetches
- 63f6147 Refining the log current timestamp method, increasing thread safety
- b16b987 Introducing the CMake configurable log severity messages compilation switch
- fb592a0 Introducing the appBoostLog branch info into the READMEs
- 30135d1 Hiding the compile options cmake files under separate directory
- cbebdc3 Enhancing sanitizers combinations and new cmake dir for ones
- bb97629 Introducing the sanitizers enabling info into the READMEs
- 4cf71cf Removing redundant cmake traces messages
- 00758d2 Introducing the GCC compiler sanitizers
- 6a19647 Refined issues in the Docker READMEs doc
- d60de04 Refining the Docker target for the SDL2
- e638e87 Separating the Docker single container build and run targets
- ae2a35d Introducing the Docker single run container target.
- 0ce70bf Adding project neatness to the READMEs
- 351628d Introducing the appLog4Cpp5 branch info into the READMEs
- 62a1e86 Implementing the logging macros and a simple logger to perform log messaging
- d7dc0ff Introducing the appMongoDBCpp4 branch info into the READMEs
- 370c5f4 Fixing the cppcheck non explicit constructor warning
- 02de04e Introducing misc/.cppcheck-suppress file to list cppcheck suppressions of the false positives
- c489308 Reparing the cppcheck virtual call in the constructor warning
- 109c905 Refining the flatpak reverse URL for SDL2
- 48859d8 Making the flatpak source json conf file configurable during cmake conf stage
- c2bc499 Introducing the SDL2 dependencies into the deb variables for the cpack
- 4e3b9bc Refining the deb cmake info for cpack
- 9c7e00b Introducing the appSQLiteCpp3 branch info into the READMEs
- c3951d2 Refining the ApplicationContext mock
- 18ca64e Introducing the gitlab mirror into the READMEs
- 2f6d937 Introducing the appMySQLCppConn branch info into the READMEs
- 6230269 Introducing the appBoostBeast branch info into the READMEs
- 3b71ee7 Explicitly specifying the combining of the template branches
- 826f284 introducing the appPgSQLxx branch into the READMEs
- 1e11040 Introducing a new appWt4 branch info into the READMEs
- 7879110 Moving the SDL_Init call to the SDL2Initer
- 610b0ee Decomposing and introducing the OpenGLIniter class
- dea82d3 Introducing the SDL2ContextBuilder and decomposing SDL2Initer
- 1758d09 clang-format applied
- e852e67 Introducing the SDL2Context and eventing subsystem decomposed
- 221ab38 Applying clang-format
- 271f853 Decomposing drawing routine into separate component and class Painter
- 4f46ddb Introducing the error exit code for a cppcheck target
- 782c533 Refinining the cppcheck target
- 1a98688 Introducing the donation notice into the READMEs
- bf88cc6 Adding a screen sharing for the flatpak target install
- 4d54662 Refining the flatpak target
- c744985 Refining Application UTs
- 7dbd0ba Introducing the appMeson branch info into the READMEs
- ae8fa5c Refining the top branch info in the READMEs
- 1ccd451 Introducing the flatpak sections into the READMEs
- bf321cd Introducing the flatpak package creation from the template source.
- c57728a Erasing the /analyze from the default MSVC compile options
- a15b724 Introducing the DEB package gen info in the READMEs
- baaca18 Introducing the cpack configuration for the deb package generation
- 4f260e6 Introducing the LICENSE file with free of use license and notice
- 376a662 Introducing clang-tidy
- 7f6ef31 Marging the appSDL2 as current branch in the READMEs
- 9ae8967 Introducing the SDL2 required packages into the READMEs
- d89a71c Introducing the appSDL2 branch into the READMEs
- f976432 Changing the SDL context and window destroy order
- 17f89e9 Decomposing SDL2 event handler into separate method.
- c285c6e Introducing the SDL2Initer class
- 29532bc Erasing redundat libraries installation info
- 41450f5 Introducing the FreeGlut/OpenGL appFreeGlut branch info into READMEs
- 6cdefed Incrementing version to 0.8.0
- b2ae262 Release app0.7.0 2025-03-17

## [app0.7.0] - 2025-03-17

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

[app0.7.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.7.0)
[app0.6.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.6.0)
[app0.5.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.5.0)
[app0.4.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.4.0)
[app0.3.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.3.0)
[app0.2.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/app0.2.0)
[v0.1.0](https://github.com/yuriysydor1991/cpp-app-template/releases/tag/v0.1.0)
