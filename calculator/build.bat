
set BUILD_DIR="build"
set GENERATOR=""

cmake %GENERATOR% -S . -B %BUILD_DIR%&&cmake --build %BUILD_DIR% --config Release 

