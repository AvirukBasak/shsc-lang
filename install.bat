@echo off

REM check if nmake, bison and gcc are installed
where /q nmake
if %errorlevel% neq 0 (
  echo install.bat: error: nmake is not installed.
  exit /b 1
)

where /q bison
if %errorlevel% neq 0 (
  echo install.bat: error: bison is not installed.
  exit /b 1
)

where /q gcc
if %errorlevel% neq 0 (
  echo install.bat: error: gcc is not installed.
  exit /b 1
)

REM run nmake
nmake
if %errorlevel% neq 0 (
  echo install.bat: error: nmake failed.
  exit /b 1
)

REM installation
echo.
echo -----------------------------------------------------
echo To install run:
echo nmake install
echo -----------------------------------------------------
echo.
