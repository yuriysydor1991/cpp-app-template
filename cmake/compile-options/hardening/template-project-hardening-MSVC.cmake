cmake_minimum_required(VERSION 3.13)

# The MSVC toolchain only warns about the options it does not know (the D9002
# and the LNK4044 ones), so an older or a non x86 toolchain drops what it
# misses instead of failing the build.
set(
  EXTRA_COMPILE_OPTIONS
  ${EXTRA_COMPILE_OPTIONS}
  /GS
  /guard:cf
  /Qspectre
)

set(
  EXTRA_LINK_OPTIONS
  ${EXTRA_LINK_OPTIONS}
  /GUARD:CF
  /DYNAMICBASE
  /NXCOMPAT
  /HIGHENTROPYVA
  /CETCOMPAT
)
