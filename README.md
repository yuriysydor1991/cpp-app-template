**Your C++ Application template project**

# Goal of the template project

Project is designed to increase the speed of the application creation process at the project startup by providing templated application structure. So developer may just jump straight into implementing a particular application with no or minimum project start structure set up.

**Just fork it and implement your application straight away!**

Examine available branches to find your most applicable variant of the template (**currently a single branch available only**).

Alter current `README.md` file to match your implementation introduced into the template project.

See more at the [kytok.org.ua](http://www.kytok.org.ua/)

# Requirements

This section contains list of required packages and/or tools that must be present in the system in order to build templated project.

## Required tools for the GNU/Linux based OS

In order to build minimum template project install the GCC C++ compiler with CMake and Git.

```
sudo apt install -y g++ cmake gtest git
```

# Cloning the C++ template project

In order to fast-start implementing a new application clone this project into your local directory by executing next command in the terminal (GNU/Linux based):

```
git clone https://github.com/yuriysydor1991/cpp-app-template.git
```

After this command executes you should find a directory named `cpp-app-template` inside your current one. So enter it by calling `cd cpp-app-template`.

# Forking and replacing the origin

In order to copy all the template project into your new clean repository (**clean repository with no** `README.md`, `.gitignore` or `LICENCE` files) clone it into your local directory and perform origin setup command from inside to project root:

```
# REPLACE next URL with yours
git remote add origin https://github.com/yuriysydor1991/cpp-app-template.git

git push --set-upstream origin main
```

Replace the `https://github.com/yuriysydor1991/cpp-app-template.git` URL with one of your newly created project repository URL.

Forking may be performed in git Web interface panel.

# Project structure

## Implement code straight away!

To proceed the application implementation right away look for the `Application` class' `Application.cpp` file which is designed to accept initial code of the application. Specifically, new code may be placed into the `int Application::run(std::shared_ptr<ApplicationContext> ctx)` method.

**But do not forget about the SOLID principles and code decomposing!**

It's preferable to create other directories which would contain implemented components of the application and include them into the `Application` class implementation, rather than put all the code inside the `Application` class itself.

## Changing the project and executable name

Change the name of the project in the project's root `CMakeLists.txt` file by introducing a new value for the the `PROJECT_NAME` variable. It is recommended to do so the executable will represent your new application name instead of templated default one - the `CppAppTemplate`.

## Introducing custom command line parameters

In order to introduce some additional command line parameters for the binary look for the `CommandLineParser` class implementation. It contains command line parsing routines that are passed by `ApplicationFactory` class after the `main` function was called.

Add some additional custom fields into the `ApplicationContext` class in order to pass some custom command line flags and/or data to the `IApplication` interface abstract class descendants that will be created by the `ApplicationFactory` during command line arguments parse.

## Implement your own IApplication descendants

You may implement another custom `IApplication` descendant classes in order to support high level variety of the application behavior to not to mess original `Application` class with irrelevant `if`-s statements and mixing up code (remember about the SOLID's single responsibility principle).

You may accomplish `IApplication` subclassing by directly creating an `IApplication` subclass in a new file or extend existing `IApplication` descendant like `Application`, `ApplicationHelpPrinter` or a `ApplicationVersionPrinter`.

Register newly created custom `IApplication` descendant in the `ApplicationFactory`'s `create_application` method which is responsible to create appropriate application instance with accordance of a provided data through the command line parameters.

That may be accomplished by implementing a custom `ApplicationFactory` descendant and overriding it's create methods like `create_application` and/or others (call appropriate static member in the `main` function of the `main.cpp` file).

## Version tracking and other project parameters

The project's `CMakeLists.txt` files are tracking of a current project git repository commit, project name, configure date and projects version that are forwarded into the projects's configure header file located at `src/app/project-global-decls.h.in`. The `project-global-decls.h.in` will be compiled into the build directory as `project-global-decls.h`. The `ApplicationVersionPrinter` class includes this project's configure file and uses the information provided to print appropriate version info. Usually, this code is executed by calling generated executable with a `-v` or `--version` command line flag. After the version is printed, the default implementation cause the application's `ApplicationVersionPrinter` instance to return zero value and cause the executable to stop it's execution.

## Extensions

There will be introduced some Doxygen documentation auto generation with a `cppcheck` code analyzer in the future, etc.

# Project build

## IDE build

Of course if your IDE supports CMake build system integration you may just press the `Build` and/or `Run` button somewhere in the IDE window with opened project and it's done! No need to perform a search and execute commands.

## Command line build

The project uses the CMake build system so a build command should be familiar with most of the C++ developers around the world!

Of course, project needs to be `git clone`-ed and it's root directory must be opened in the terminal or in your IDE first. After that you may execute next commands:

```
mkdir -vp build && cd build && cmake ../ && cmake --build . --target all
```

Which effectively will create a directory named `build` (it's already added to the `.gitignore` list), configure project using the CMake available in the system (see the [Requirements](#Requirements) section of this `README.md` file) and finally builds all the targets available in the project.

# Run the executable

## IDE run

Of course, if your IDE supports CMake build system integration you may just press the `Build` and/or `Run` button somewhere in the IDE window with opened project and it's done! No need to perform a search and execute commands.

## Command line run

### Searching for the generated executable

To find executable in the project build directory execute the `find` command:

```
find . -name 'CppCppAppTemplate'
```

The `CppCppAppTemplate` is a default executable name. Replace it with your custom one if you change the name of the project in the root `CMakeLists.txt` file (the `PROJECT_NAME` variable).

### Starting the generated executable

If executable compiles and is present in the build directory start it in the terminal with path found from a previous subsection by a command:

```
# from the build dir
./src/CppAppTemplate
```

Once again, the `CppAppTemplate` is the **default** name of the project. Replace it with our own custom one if it was changed in the project's root `CMakeLists.txt` file (the `PROJECT_NAME` variable).
