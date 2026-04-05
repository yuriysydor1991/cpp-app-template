## Required PLplot packages

In order to make available the PLplot development library install next packages into the system:

```
sudo apt install -y libplplot-dev
```

Or compile it manually by commands that may look like next:

```
# clone the project into current directory
git clone https://git.code.sf.net/p/plplot/plplot plplot

# configure CMake project 
cmake -B plplot-build -S plplot -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr -DENABLE_fortran=OFF

# build all the project contents
cmake --build plplot-build -j$(nproc)

# install it into the system
sudo cmake --install plplot-build --prefix /usr
```
