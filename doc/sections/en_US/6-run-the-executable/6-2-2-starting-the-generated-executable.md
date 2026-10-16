### Starting the generated executable

If executable compiles and is present in the build directory start it in the terminal with path found from a previous subsection by a command:

```
# inside the build root directory

./src/CppAppTemplate --docroot "_deps/wt-src;/resources" --http-listen 127.0.0.1:8000 --accesslog CppAppTemplate-http-access.log
```
 
Which effectively will start the [Wt](https://www.webtoolkit.eu/wt) web application http server with implemented project code web-site running on it for port `8000` on `loopback` network interface.

Replace the `127.0.0.1` with a general `0.0.0.0` address in order to make application listen for request outside the local machine.

The `--docroot` value names the directory that holds the [Wt](https://www.webtoolkit.eu/wt) `resources` one with the themes, the stylesheets and the images of the widgets, while the `/resources` after the semicolon tells the Wt to serve the URLs under it as static files. The `_deps/wt-src` directory holds the Wt sources the project configure fetched into the build directory. A system installed Wt keeps the `resources` directory in the `share/Wt` directory of its install prefix, e.g. `--docroot "/usr/local/share/Wt;/resources"`.

The executable handles its own `-h`/`--help`, `-v`/`--version` and `-l`/`--log-file <path>` parameters and hands every other one over to the Wt server. Refer to the [Wt C++ framework](https://www.webtoolkit.eu/wt) documentation for the available Wt command line parameters.

Press `Ctrl+C` or send the `SIGTERM` signal to the process to stop the server.
