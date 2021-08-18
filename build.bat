set VCPKG_PATH="C:\vcpkg\scripts\buildsystems\vcpkg.cmake"
set MSBUILD_PATH="C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\MSBuild\Current\Bin\amd64\MSBuild.exe"

cmake . -B build -G "Visual Studio 16 2019" -A x64 -DCMAKE_TOOLCHAIN_FILE=%VCPKG_PATH% 
%MSBUILD_PATH% build\harmony.sln