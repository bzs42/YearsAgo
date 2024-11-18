set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 COMPONENTS Core Gui REQUIRED)
find_package(Qt6Test REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/Src)

add_executable(ModelTest
    ${CMAKE_SOURCE_DIR}/Src/App.qrc
    ${CMAKE_SOURCE_DIR}/Src/Model.h
    ${CMAKE_SOURCE_DIR}/Src/Model.cpp
    ${CMAKE_SOURCE_DIR}/Src/SearchAlgorithm.cpp
    ${CMAKE_SOURCE_DIR}/Src/SearchAlgorithm.h
    ${CMAKE_SOURCE_DIR}/Src/SearchThread.cpp
    ${CMAKE_SOURCE_DIR}/Src/SearchThread.h
    ModelTest.cpp
    ModelTest.h
)
add_test(NAME ModelTest COMMAND ModelTest)
target_link_libraries(ModelTest PRIVATE Qt6::Test Qt6::Core Qt6::Gui)

add_executable(CacheTest
    ${CMAKE_SOURCE_DIR}/Src/App.qrc
    ${CMAKE_SOURCE_DIR}/Src/Cache.cpp
    ${CMAKE_SOURCE_DIR}/Src/Cache.h
    CacheTest.cpp
    CacheTest.h
)
add_test(NAME CacheTest COMMAND CacheTest)
target_link_libraries(CacheTest PRIVATE Qt6::Test Qt6::Core Qt6::Gui)
