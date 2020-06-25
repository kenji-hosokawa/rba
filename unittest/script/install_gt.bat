@echo off
set ARCH=x64
set MODE=%1

set URL=https://github.com/google/googletest.git
set GITTAG=release-1.8.1

IF NOT EXIST googletest\. (
   git clone -b %GITTAG% %URL%
)

if "%MODE%" == "" (
    set MODE=Release
)
if not "%MODE%" == "Debug" (
    if not "%MODE%" == "Release" (
        echo Usage: %0 Debug or Release
        goto end
    )
)
set CMAKE_OPTION=
if "%ARCH%" == "x86" (
   set CMAKE_OPTION="Visual Studio 15 2017"
) else if "%ARCH%" == "x64" (
   set CMAKE_OPTION="Visual Studio 15 2017 Win64"
)

set DIRNAME=build_%ARCH%
set OUTNAME=%MODE%_%ARCH%

cd googletest\googletest
if exist "%DIRNAME%\" (
   rd /s /q %DIRNAME%
)

mkdir %DIRNAME%
cd %DIRNAME%

if exist ..\CMakeCache.txt (
   del ..\CMakeCache.txt
)

cmake .. -DBUILD_GTEST=ON -DBUILD_GMOCK=OFF -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY=.. -G %CMAKE_OPTION%
cd ..
cmake --build %DIRNAME% --config %MODE%
cd ..\..

:end
echo done.
