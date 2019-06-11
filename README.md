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

- Shader:

A program that runs on your GPU.
We need to be able to program the GPU.
Because even in the form of drawing the simplest form, I still want to be able to tell the GPU how to to draw that triangle ?Like, where do the vertex positions go, what color should the triangle be, how should it be drawn, v..v 
We need to tell the GPU what to do with the data we've sent it --> What a shader fundamentally is.

- The rendering pipeline: https://www.geeksforgeeks.org/opengl-rendering-pipeline-overview/

- Vertex Shader and Fragment Shader - 2 main types of shader : 
  Vertex Shader: get called for every vertex that we are trying to render. Primary purpose: tell OpenGL where u want that vertex to be in your screen space. 
  Fragment Shader a.k.a Pixel Shader: run once for every pixel that needs to be rasterized. [Rasterisation is the task of taking an image described in a vector graphics format (shapes) and converting it into a raster image (a series of pixels, dots or lines, which, when displayed together, create the image which was represented via shapes).] Decide what color each pixel should be. 

Everything is like, made of triangles. A square can be made by putting 2 triangles tgt.

- Index Buffer:
Allow us to use existing vertices.


Later should use index buffer & glDrawElements often, rather than glDrawArrays. 

- EVERY BUFFER HAS TO BE MADE UP OF UNSIGNED INT, NOT INT

-------------------------------------ERROR CHECKING IN OPENGL---------------------------------------------------------------------------

2 main ways to check error in OpenGL :
- glGetError(): A callable function. However, this func. is only able to return a "flag" of the most recent error --> In case off multiple errors, have to call it multiple times.    
If more than one flag has recorded an error, glGetError() returns and clears an arbitrary error flag value. Thus, glGetError() should always be called in a loop, until it returns GL_NO_ERROR, if all error flags are to be reset.

This function should return an error code in int --> E.g; 1280. Actual error code in the header files is in hexadecimal: So, 1280 -> 0x0500. Search for the error code in the header file <glew.h>. 
- glDebugMessageCallback() : A new func only in GL 4.3 and above, but is generally better. 

----------------------------------------------Uniform in OpenGL------------------------------------------------------------------------
- A way to actually get data from the CPU side into our shader so that we can actually use it like a variable
- Uniform are set per draw, while attribute is set to per vertex.
----------------------------------------------Vertex Arrays----------------------------------------------------------------------------
- A way to bind vertex buffers with a certain 'specification' for the layout of that actual vertex buffer.
