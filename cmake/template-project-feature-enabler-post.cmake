cmake_minimum_required(VERSION 3.13)

if (ENABLE_DOCKER)
  include(template-project-dockerers)
endif()

include (template-project-libxml2-enabler)
