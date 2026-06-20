### Manual tests run

Currently tests are separated in different files named with `UTEST_*` pattern for the unit tests.

You may search for all compiled available tests by a next command:

```
# from the project root or a build directory

find -type f -executable -name 'UTEST_*'
```

After that, choose particular test of interest and execute it manually if needed. For example, for the `ApplicationFactory` class pass it's UT relative file system path from a project's root directory into the command line and hit enter (GNU/Linux based):

```
# from the project root

./build/src/app/tests/unit/ApplicationFactory/UTEST_ApplicationFactory
```
