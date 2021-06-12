cmake_minimum_required(VERSION 3.5)

project(YearsAgo LANGUAGES CXX
    VERSION 0.1.0.0
    DESCRIPTION "Years ago"
    HOMEPAGE_URL "dilishes.de")

set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR}/Dist CACHE STRING "Install path prefix." FORCE)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(Src)

enable_testing(TRUE)
add_subdirectory(Test)
