## Version tracking and other project parameters

The project's `CMakeLists.txt` files are tracking of a current project git repository commit, project name, configure date and projects version that are forwarded into the projects's configure header file located at `src/app/project-global-decls.h.in`. The `project-global-decls.h.in` will be compiled into the build directory as `project-global-decls.h`.
