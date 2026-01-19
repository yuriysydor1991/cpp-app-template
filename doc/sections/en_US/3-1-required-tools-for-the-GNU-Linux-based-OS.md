## Required tools for the GNU/Linux based OS

In order to build minimum template project install the GCC C++ compiler with CMake and Git.

```
sudo apt install -y git g++ cmake
```

To make the [SDL2](https://en.wikipedia.org/wiki/Simple_DirectMedia_Layer) library available system wide execute next command:

```
sudo apt install -y libsdl2-dev libsdl2-doc \
  libsdl2-image-2.0-0 libsdl2-image-dev libsdl2-mixer-2.0-0 \
  libsdl2-mixer-dev libsdl2-net-2.0-0 libsdl2-net-dev \
  libsdl2-ttf-dev
```
