# OpenGL_Learning
# http://docs.gl/

Visual Studio Project Setup Properties: (All Configurations && Win32)
- C++/General/Additional Include Directories: $(SolutionDir)Dependencies\GLFW\include;$(SolutionDir)Dependencies\GLEW\include
- Linker/General/Additional Library Directories: $(SolutionDir)Dependencies\GLEW\lib\Release\Win32;$(SolutionDir)Dependencies\GLFW\lib-vc2019
- Linker/Input/Additional Dependencies: glew32s.lib;glfw3.lib;opengl32.lib;User32.lib;Gdi32.lib;Shell32.lib
- Define GLEW_STATIC in preprocessor definitions (Defines a preprocessing symbol for a source file): C++/Preprocessor/Preporcessor Definitions: GLEW_STATIC

---------------------------------------------------A Very Informal Self-Note--------------------------------------------------------

- OpenGL ~ A rendering API

OpenGL functions are not what u download, its stuff are actually in your graphic drivers. 
The OpenGL functions are implemented in your GPU drivers. So we need to go into the drivers, pull out the functions and call them. “Pulling out” here means, we need to basically just get the function declaration and then link against the function as well. Access the driver DLL files, retrieve function pointers to the functions inside those libraries. 

Modern OpenGL has a lot of functions. There are few problems: They might not be cross-platform, and furthermore if there’s TOO MANY functions or sth like dat then going thru them manually is a sick & terrible thing. So, use another library – it provides the OpenGL API specification (kinda func declarations, symbol declarations, constants, etc… ) . In other words, the implementation of the API identifies what graphics drivers u are using, find the appropriate DLL files & then load all of the func pointers. It is not magical at all, it just access the functions that are alr on your computer in binary form. 

	The library that does that for us is Glue, or GLEW – the OpenGL Extension Wrangler. 

- INITIALIZING GLEW

First you need to create a valid OpenGL rendering context and call glewInit() to initialize the extension entry points. If glewInit() returns GLEW_OK, the initialization succeeded and you can use the available extensions as well as core OpenGL functionality.(You can't use OpenGL function from GLEW until u call GLEw in it)


- Dependencies/GLEW/lib/Release/Win32
Both libs are static libraries, but glew32.lib is used if u want to link w/ the DLL, glew32s.lib is used to link w/ just the static lib 

- Vertex Buffer & layout :
Basically a buffer of memory that's stored on the GPU, so when the program/the shader actually starts to read that vertex buffer it needs to know the layout of that buffer. What is actually contained in the buffer ? --> just a bunch of floats which dictate the position of each vertex, do u also have texture coordinates, normals, etc... Have to actually tell OpenGL what is in the memory and how is its layout (i.e, like, what is its type).   

Stride: offset/amount of bytes between consecutive vertex attributes: i.e, size of a vertex attribute. 

!! To enable and disable a generic vertex attribute array, call glEnableVertexAttribArray and glDisableVertexAttribArray with index.