# CopyRVAPlugin
CopyRVAPlugin is a [Cutter](https://github.com/rizinorg/cutter) plugin that streamlines the process of getting the Relative Virtual Address of a function or instruction. 

### Install
Copy to your Cutter native plugin directory.  
You can find this directory in Cutter via `edit` -> `preferences` -> `Plugins` -> `Plugins are loaded from ...`

### Usage
Right click an instuction or function -> `plugins` -> `Copy RVA`

### Compiling:
Add `[cutter install dir]/lib/cmake` to CMAKE_PREFIX_PATH
Add QT5 cmake dir to CMAKE_PREFIX_PATH ( `Qt/[version]/[compiler]/lib/cmake/Qt5` on my machine)
```
md build
cd build
cmake ..
```
Compile using your compiler (compile in `release` mode if you want it to work with release builds of Cutter)