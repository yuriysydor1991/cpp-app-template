cmake_minimum_required(VERSION 3.13)

include(template-project-load-file-into-h)

load_file_data(
  ${CMAKE_CURRENT_SOURCE_DIR}/kytok.org.ua-logo.png 
  RANDOM_LOGO_DATA_SIZE 
  RANDOM_LOGO_DATA
)

configure_file(
  random-logo.h.in
  ${CMAKE_BINARY_DIR}/random-logo.h
)
