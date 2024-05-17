@echo off

IF "%1"=="" (
    SET arg1=vs2022
	echo Generating solution for default: vs2022
) ELSE (
    SET arg1=%1
)

git submodule init
git submodule update

.\vendor\premake5\premake5.exe %arg1%
