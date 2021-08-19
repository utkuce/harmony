# Build
## Windows
- Install C++ Build Tools (Desktop Development with C++ in the Visual Studio Installer) and make sure to include include 
    - Windows 10 SDK
    - C++ CMake Tools for Windows
- Install [vcpkg](https://vcpkg.io/en/getting-started.html)
- Install dependencies `./vcpkg install redis-plus-plus fmt --triplet x64-windows`
- Run `build.bat` after modifying the path variables in the file as needed

An executable will be created under `build\Debug\`

**Note:** For Visual Studio Code following extensions are required
- C/C++
- CMake Tools