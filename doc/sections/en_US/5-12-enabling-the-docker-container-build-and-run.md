## Enabling the Docker container build and run

To be able to build and run the Docker container with current template project' target binary file enable it's Meson target with setting the `ENABLE_DOCKER` variable into value `ON` by using the next command:

```
# inside the project root directory

meson setup build -DENABLE_DOCKER=true
```

After that there should be available the Docker build and run Meson target `docker-single-run` which may be triggered with the command:

```
# inside the project root directory

meson compile -C build docker-single-run
```

Examine the `meson/template-project-dockerers/meson.build` file for the `docker-single-run` target details.
