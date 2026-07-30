## Required PGPLOT packages

The project uses the C binding (the `cpgplot.h` header and the `cpgplot` library) of the [PGPLOT](https://sites.astro.caltech.edu/~tjp/pgplot/) graphics subroutine library. In order to make the PGPLOT development files available install next packages into the system:

```
sudo apt install -y pgplot5-dev
```

Keep in mind that the original PGPLOT is distributed under a non-free license, so it resides in the `multiverse` component of the Ubuntu repositories (and in the `non-free` one of the Debian's) and it may be absent in your GNU/Linux distribution at all.

The [giza](https://danieljprice.github.io/giza/) library provides a free software drop-in replacement of the very same PGPLOT/`cpgplot` interface (a cairo based one) and is accepted by the project's CMake probe as well:

```
sudo apt install -y giza-dev
```

Or compile the giza replacement manually by commands that may look like next:

```
# clone the project into current directory
git clone https://github.com/danieljprice/giza.git giza

# configure the project
cd giza && ./configure --prefix=/usr

# build all the project contents
make -j$(nproc)

# install it into the system
sudo make install
```

In case the library is installed into a custom (non default) prefix, point the project's CMake probe to it by the `TEMPLATE_APP_PGPLOT_ROOT` variable:

```
cmake -S . -B build -DTEMPLATE_APP_PGPLOT_ROOT=/your/pgplot/prefix
```

The whole integration may be turned off by the `-DENABLE_PGPLOT=OFF` CMake parameter, but in such a case the `src/pgplot` subdirectory must be dropped from the `src/CMakeLists.txt` file too, since the `pgploti::PGPLOTController` class implementation requires the library.
