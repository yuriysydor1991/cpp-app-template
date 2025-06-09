cmake_minimum_required(VERSION 3.13)

if (ENABLE_SANITIZERS AND ENABLE_SANITIZERS_THREADS)
  message(FATAL_ERROR "Can't combine thread and regular sanitizers")
endif()

if (ENABLE_SANITIZERS)
  include(template-project-sanitizers-regular)
endif()

if (ENABLE_SANITIZERS_THREADS)
  include(template-project-sanitizers-threads)
endif()
