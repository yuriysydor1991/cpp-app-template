### Run tests by the meson

If enabled by the developer through the `ENABLE_UNIT_TESTS` variable and successfully build, the one may run all available test by the `meson test` command from a project build directory (GNU/Linux based):

```
# run from the project build directory

meson test
```

Alternatively, run the `meson test` command from any location by specifying the test dir (GNU/Linux based):

```
meson test -C build
```

In order to run particular test execute the `meson test` command with test's name after the `--suite` command line flag. For example, for the `UTEST_ApplicationFactory` test it'll look something like this:

```
# from the project root directory 

meson test -C build --suite UTEST_ApplicationFactory
```
