# OpenGL_Learning

Visual Studio Project Setup Properties:
- C++/General/Additional Include Directories: $(SolutionDir)Dependencies\GLFW\include
- Linker/General/Additional Library Directories: $(SolutionDir)Dependencies\GLFW\lib-vc2019
- Linker/Input/Additional Dependencies: glfw3.lib;opengl32.lib;User32.lib;Gdi32.lib;Shell32.lib

---------------------------------------------------A Very Informal Self-Note--------------------------------------------------------

OpenGL ~ A rendering API

OpenGL functions are not what u download, its stuff are actually in your graphic drivers. 
The OpenGL functions are implemented in your GPU drivers. So we need to go into the drivers, pull out the functions and call them. “Pulling out” here means, we need to basically just get the function declaration and then link against the function as well. Access the driver DLL files, retrieve function pointers to the functions inside those libraries. 

Modern OpenGL has a lot of functions. There are few problems: They might not be cross-platform, and furthermore if there’s TOO MANY functions or sth like dat then going thru them manually is a sick & terrible thing. So, use another library – it provides the OpenGL API specification (kinda func declarations, symbol declarations, constants, etc… ) . In other words, the implementation of the API identifies what graphics drivers u are using, find the appropriate DLL files & then load all of the func pointers. It is not magical at all, it just access the functions that are alr on your computer in binary form. 

	The library that does that for us is Glue, or GLEW – the OpenGL Extension Wrangler. 
