set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS Core Gui REQUIRED)
find_package(Qt5Test REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/Src)

add_executable(ModelTest
    ${CMAKE_SOURCE_DIR}/Src/App.qrc
    ${CMAKE_SOURCE_DIR}/Src/Model.cpp
    ${CMAKE_SOURCE_DIR}/Src/Model.h
    ${CMAKE_SOURCE_DIR}/Src/SearchThread.h
    ${CMAKE_SOURCE_DIR}/Src/SearchThread.cpp
    ${CMAKE_SOURCE_DIR}/Src/SearchAlgorithm.h
    ${CMAKE_SOURCE_DIR}/Src/SearchAlgorithm.cpp
    ModelTest.h
    ModelTest.cpp
)

add_test(NAME ModelTest COMMAND ModelTest)
target_link_libraries(ModelTest PRIVATE Qt5::Test Qt5::Core Qt5::Gui)
