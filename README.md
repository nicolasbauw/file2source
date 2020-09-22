# file2source
A graphical tool to create C arrays from binary files.

An easy way to include binary data to your source code, if you want to distribute you app in a single file.

This repo is an exhumation of an old tool I wrote in my SDL / OpenGL / CodeBlocks / mingw learning and coding times.
At that time SDL transparency was handled by a mask, and then, when I switched to OpenGL, I needed a RGB -> RGBA conversion to convert my SDL bitmaps with a green back to more conventional RGBA bitmaps.

As of 1.2.0, the (very) old source has been relatively untouched, but reworked to be a little less ugly, and to be compiled with clang on Windows and Mac with the latest release of imgui. I also removed features I don't need any more.

Dependency : the GLFW libs (3.3)

![Screenshot](data/screenshot.png)
