### Starting the generated executable

If executable compiles and is present in the build directory start it in the terminal with path found from a previous subsection by a command:

```
# inside the build root directory

./src/CppAppTemplate --docroot ".;/resources" --http-listen 127.0.0.1:8000 --accesslog CppAppTemplate-http-access.log
```
 
Which effectively will start the [Wt](https://www.webtoolkit.eu/wt) web application http server with implemented project code web-site running on it for port `8000` on `loopback` network interface.

Replace the `127.0.0.1` with a general `0.0.0.0` address in order to make application listen for request outside the local machine.

The `resources` folder should be copied from the used [Wt](https://www.webtoolkit.eu/wt) source code to the application run directory in order to [Wt](https://www.webtoolkit.eu/wt) display properly. Not included into the current template project to reduce it's `git` repository size. Refer for the [Wt C++ framework](https://www.webtoolkit.eu/wt) documentation on how to obtain the `resources` directory.

Refer to the [Wt C++ framework](https://www.webtoolkit.eu/wt) documentation for the available Wt executable command line parameters.
