# Windows build recipe

```bash
mkdir build-imagingsuite
mkdir install
mkdir install\applications
mkdir install\lib
mkdir install\tests
mkdir deployed
cd build-imagingsuite
conan install ..\imagingsuite\ --profile:host ..\imagingsuite\profiles\windows_msvc_16_release --profile:build ..\imagingsuite\profiles\windows_msvc_16_release
activate.bat
C:\Qt\Tools\Cmake_64\bin\cmake.exe ..\imagingsuite\ -DCMAKE_PREFIX_PATH=C:\Qt\6.2.4\msvc2019_64\lib\cmake\ -DCMAKE_INSTALL_PREFIX=../install/ -G="Visual Studio 16 2019"
cmake --build . --target install --config Release
deactivate.bat
cd ../imagingsuite/deploy/win
deploymuhrec_cmake.bat

```