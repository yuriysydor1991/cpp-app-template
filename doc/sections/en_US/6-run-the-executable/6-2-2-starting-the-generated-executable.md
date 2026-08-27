### Starting the generated executable

If executable compiles and is present in the build directory start it in the terminal with path found from a previous subsection by a command:

```
# from the build dir
./src/CppAppTemplate
```

The `appCFITSIO` branch executable reads a FITS image and reports about it, so point it at one with the `--image` (or `-i`) parameter:

```
# from the build dir
./src/CppAppTemplate --image /path/to/an-image.fits
```

It reports the HDUs count, the image size, the pixel type and the range the pixels span, and adds the sky coordinates of the image centre as long as the header carries the world coordinate system keywords. Without the parameter it only says which one to pass.

Once again, the `CppAppTemplate` is the **default** name of the project. Replace it with our own custom one if it was changed in the project's root `CMakeLists.txt` file (the `CMAKE_PROJECT_NAME` and/or `PROJECT_BINARY_NAME` variable).
