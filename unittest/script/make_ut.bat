@echo off
set ARCH=x64
set LOG=OFF
set MODE=%1

if "%MODE%" == "" (
    set MODE=Release
)
if not "%MODE%" == "Debug" (
    if not "%MODE%" == "Release" (
        echo Usage: %0 Debug or Release
        goto end
    )
)
set LOGLABEL=
if "%LOG%" == "ON" (
    set LOGLABEL=_log
) else (
    set LOGLABEL=_nolog
)

set CMAKE_OPTION=
if "%ARCH%" == "x86" (
   set CMAKE_OPTION="Visual Studio 15 2017"
) else if "%ARCH%" == "x64" (
   set CMAKE_OPTION="Visual Studio 15 2017 Win64"
)

set DIRNAME=build_%ARCH%
set OUTNAME=%MODE%_%ARCH%

if exist "%DIRNAME%\" (
   goto exec_make
)

mkdir %DIRNAME%
cd %DIRNAME%

if "%LOG%" == "ON" (
    cmake -G %CMAKE_OPTION% ..  -DDEBUG_CMAKE=1 -DCMAKE_WINDOWS_EXPORT_ALL_SYMBOLS=TRUE -DBUILD_SHARED_LIBS=TRUE
) else (
    cmake -G %CMAKE_OPTION% -DNOLOG=1 ..
)
cd ..

:exec_make
cmake --build %DIRNAME% --config %MODE%
copy %DIRNAME%\%MODE%\unittest_rba.exe unittest_rba.exe /Y

:end
echo done.
