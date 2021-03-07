cmake_minimum_required(VERSION 3.5)

project(YearsAgo LANGUAGES CXX
    VERSION 0.1.0.0
    DESCRIPTION "Years ago"
    HOMEPAGE_URL "dilishes.de")

set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR}/dist CACHE STRING "Install path prefix." FORCE)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(Src)

if(WIN32)
    # FIXME: android: add_custom_target cannot create target "aab"/"apk" because another target exists
    enable_testing(true)
    add_subdirectory(Test)
endif()
