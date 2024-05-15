@echo off
git submodule init
git submodule update
.\vendor\premake5\premake5.exe %1
