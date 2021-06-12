:: build tools

SET NINJA=c:\3rdParty\Ninja\1.10.0
SET CMAKE=c:\3rdParty\CMake\3.19.2
rem needed bei CMake QtIFW Module (CPackIFW)
SET QTIFWDIR=C:\3rdParty\Qt\Tools\QtInstallerFramework\3.2

SET PATH=%NINJA%;%CMAKE%\x64\bin;%QTIFWDIR%\bin;%PATH%;

:: libraries and runtime

SET QT=C:\3rdParty\Qt\5.15.2

SET PATH=%QT%\msvc2019_64\bin;%QT%\msvc2019_64\lib;%PATH%;

:: project

SET QT_MESSAGE_PATTERN=%%{if-category}%%{category}.%%{endif}%%{type} %%{function}: %%{message}
SET QT_LOGGING_CONF=D:\bin\qtlogging.ini
SET QT_LOGGING_DEBUG=1

:: msvc compiler

SET MSVC=c:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Auxiliary/Build/vcvarsall.bat
call "%MSVC%" x64 -vcvars_ver=14.2
