# TheEscape
3D game. 

Written with C++<br>
dependency use glfw and stb

Base on Legecy Opengl or Classic Opengl

Warning!!! 
* It not the worthest way to learn opengl with immediately function. if you want best practice I suggest you to use mordern opengl function for that because it flexible than classic function. to make you figure out in this present age all we used base on mordern opengl. But if you want to understand how people in 1992 made the graphics. Maybe it's good way to learn classic opengl.

Build with C Make
* already check can build on Linux and Windows.
* if you want to build on MacOS. you have to change CMakeList.txt before build this project.

How to build it?

clone the repositiory
```sh
git clone --depth 1  https://github.com/NIZE2001/TheEscape.git
```
clone submodules
```sh
git submodule init
```
```sh
git submodule update
```
<br>

or just use this command 
```sh
git clone --depth 1 --recurse-submodules --shallow-submodules  https://github.com/NIZE2001/TheEscape.git
```

then build generator file with CMake.

