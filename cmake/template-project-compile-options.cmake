cmake_minimum_required(VERSION 3.13)

# -Werror sometimes fails with errors in the stdlib
# -D_FORTIFY_SOURCE=2 (needs OPT); 
# -fanalyzer causes prolonged build

set(EXTRA_COMPILE_OPTIONS 
  -Wall
  -Wextra
  -Wpedantic
  -Wshadow
  -Wnon-virtual-dtor
  -Wold-style-cast
  -Wcast-align
  -Wunused
  -Woverloaded-virtual
  -Wconversion
  -Wsign-conversion
  -Wnull-dereference
  -Wdouble-promotion
  -Wformat=2
  -Wimplicit-fallthrough
  -Wduplicated-cond
  -Wduplicated-branches
  -Wlogical-op
  -Wuseless-cast
  -Wmisleading-indentation
  -Wzero-as-null-pointer-constant
  -fstack-protector-all
  -fno-common
  -fstrict-overflow
  -pie
  -Wl,-z,relro
  -Wl,-z,now
)
