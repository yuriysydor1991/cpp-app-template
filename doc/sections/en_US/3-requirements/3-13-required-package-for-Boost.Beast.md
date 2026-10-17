## Required package for Boost.Beast

To make the Boost.Beast HTTP builtin-server available in destination OS installation and for the implemented application install the Boost libs by executing the command (GNU/Linux based OS):

```
sudo apt install -y libboost-all-dev
```

The Beast and the Asio libraries are header only, so the `libboost-dev` package with the Boost headers alone is enough as well, and the built executable needs no Boost package to run.

### HTTP server settings

The server listens on the `127.0.0.1:8080` address by default and answers the `GET` and the `HEAD` requests of the `/` path with the demo page (the `HEAD` ones with no body). Any other path gets the `404 Not Found` status and any other method the `405 Method Not Allowed` one. The `PROJECT_HTTP_LISTEN_ADDRESS` and the `PROJECT_HTTP_LISTEN_PORT` CMake cache variables change the address and the port at the configure time, for example:

```
cmake -S . -B build -DPROJECT_HTTP_LISTEN_ADDRESS=0.0.0.0 -DPROJECT_HTTP_LISTEN_PORT=8000
```

The connection and request limits are described in the [HTTP server hardening constraints](/doc/sections/en_US/5-project-build/security/5-50-the-HTTP-server-hardening-constraints.md) section. While waiting for a connection the server checks the stop flag of the application every 100 ms, so the `Ctrl+C`, the `kill` command or the `docker stop` one end it right away.
