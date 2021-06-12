rem cmake
SET CMAKE_VAR1=CMAKE_PREFIX_PATH=%QT%/msvc2019_64
SET CMAKE_VAR2=CMAKE_INSTALL_PREFIX=./dist

cmake.exe --log-level=verbose -D%CMAKE_VAR1% -D%CMAKE_VAR2% -DCMAKE_BUILD_TYPE=%1 -G "Ninja" ..\..\YearsAgo
cmake.exe --build . --target all
cmake.exe --build . --target install
cmake.exe --build . --target package