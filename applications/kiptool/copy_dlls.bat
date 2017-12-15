﻿@echo ----------------- Deploy copy --------------
set REPOS=C:\Users\kaestner\repos
set DEST=C:\Users\kaestner\kiptool

IF NOT EXIST %DEST% mkdir %DEST%
pushd .
cd %DEST%

copy %REPOS%\Applications\QtKipTool.exe .
copy %REPOS%\lib\ImagingAlgorithms.dll .
copy %REPOS%\lib\ImagingModules.dll .
copy %REPOS%\lib\ModuleConfig.dll .
copy %REPOS%\lib\ReaderConfig.dll .
copy %REPOS%\lib\ReaderGUI.dll .
copy %REPOS%\lib\QtAddons.dll .
copy %REPOS%\lib\QtModuleConfigure.dll .
copy %REPOS%\lib\kipl.dll .
copy %REPOS%\lib\ProcessFramework.dll
copy %REPOS%\lib\AdvancedFilterModules.dll
copy %REPOS%\lib\BaseModules.dll
copy %REPOS%\lib\ClassificationModules.dll

copy %REPOS%\external\lib64\libtiff.dll .
copy %REPOS%\external\lib64\libjpeg-62.dll .
copy %REPOS%\external\lib64\zlib1.dll .
copy %REPOS%\external\lib64\libfftw3-3.dll .
copy %REPOS%\external\lib64\libfftw3f-3.dll .
copy %REPOS%\external\lib64\libxml2-2.dll .
copy %REPOS%\external\lib64\libiconv.dll .
copy %REPOS%\external\lib64\cfitsio.dll .

rem cd C:\Qt\Qt5.2.1\5.2.1\msvc2012_64_opengl\bin
cd C:\Qt\5.8\msvc2015_64\bin
windeployqt %DEST%\QtKipTool.exe
copy Qt5PrintSupport.dll %DEST%

popd