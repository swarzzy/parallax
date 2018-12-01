@echo off
rem Local path to MsBuild and CMake
set msbuild_path="C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\MSBuild\15.0\Bin\msbuild.exe"
set cmake_path="C:\Program Files\CMake\bin\cmake.exe"

rem Building GLFW
echo ===================================== BUILDING GLFW ========================================================
cd "vendor\glfw-3.2.1"
mkdir prx_build_tmp
cd prx_build_tmp
del CMakeCache.txt /Q
rmdir CMakeFiles /s /Q
@echo on
cmake -G "Visual Studio 15 2017 Win64" ../ || %cmake_path% -G "Visual Studio 15 2017 Win64" ../
cd src
msbuild glfw.vcxproj /p:configuration=Release || %msbuild_path% glfw.vcxproj /p:configuration=Release
@echo off
copy Release\glfw3.lib ..\..\..\..\parallax\lib\

rem Building GLFW
echo ===================================== BUILDING FREETYPE2 ===================================================
@echo off
cd..
cd..
cd..
cd "freetype-2.9.1"
mkdir prx_build_tmp
cd prx_build_tmp
del CMakeCache.txt /Q
rmdir CMakeFiles /s /Q
@echo on
cmake -G "Visual Studio 15 2017 Win64" ../ || %cmake_path% -G "Visual Studio 15 2017 Win64" ../
msbuild freetype.vcxproj /p:configuration=Release || %msbuild_path% freetype.vcxproj /p:configuration=Release
@echo off
copy Release\freetype.lib ..\..\..\parallax\lib

rem Building GLFW
echo ===================================== BUILDING GL3W ========================================================

cd..
cd..
cd gl3w
@echo on
gl3w_gen.py
@echo off

PAUSE