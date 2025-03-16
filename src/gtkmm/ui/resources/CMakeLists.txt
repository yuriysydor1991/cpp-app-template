cmake_minimum_required(VERSION 3.13)

set(RANDOM_LOGO_FILEPATH ${CMAKE_CURRENT_SOURCE_DIR}/kytok.org.ua-logo.png)

file(READ ${RANDOM_LOGO_FILEPATH} RANDOM_LOGO_DATA_HEX HEX)
file(SIZE ${RANDOM_LOGO_FILEPATH} RANDOM_LOGO_DATA_SIZE)

string(
  REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1, "  
  RANDOM_LOGO_DATA_SINGLELINE ${RANDOM_LOGO_DATA_HEX}
)

string(
  REGEX REPLACE
  "(0x[0-9a-f][0-9a-f], 0x[0-9a-f][0-9a-f], 0x[0-9a-f][0-9a-f], 0x[0-9a-f][0-9a-f], 0x[0-9a-f][0-9a-f],) "
  "\t\t\\1\n"
  RANDOM_LOGO_DATA
  ${RANDOM_LOGO_DATA_SINGLELINE}
)

configure_file(
  random-logo.h.in
  ${CMAKE_BINARY_DIR}/random-logo.h
)
