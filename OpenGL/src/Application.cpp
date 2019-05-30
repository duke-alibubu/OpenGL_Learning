#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

static unsigned int compileShader(const std::string& source, unsigned int type)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str(); //or &source[0]   // pointer to the actual source character data
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	//Error handling 
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result); //i for integer, v for vector
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));        //alocate size on stack DYNAMICALLY
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile shader!"  << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;

}
static unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader) 
{
	unsigned int program = glCreateProgram();
	unsigned int vs = compileShader(vertexShader, GL_VERTEX_SHADER);
	unsigned int fs = compileShader(fragmentShader, GL_FRAGMENT_SHADER);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);       //after successfully got the program, delete the shader
	glDeleteShader(fs);

	return program;
}


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

	


    /* Make the window's context current */
    glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		std::cout << "Error!" << std::endl;
	std::cout << glGetString(GL_VERSION) << std::endl;

	float positions[6] = {
		-0.5f, -0.5f, 0.0f,   0.5f, 0.5f, -0.5f
	};

	unsigned int buffer; //buffer id
	glGenBuffers(1, &buffer); //1 = no of buffers required. Generate Buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffer); //bind the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*6, positions, GL_STATIC_DRAW); //creates and initializes a buffer object's data store

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, 0);         //2: cause 1 vertex takes 2 float - vec2

	std::string vertexShader =
		"#version 330 core\n"
		"\n"
		"layout(location = 0) in vec4 position;\n"        //0 is the INDEX of our attribute. Vec4 is because OpenGL position is eventually a vec4
		"\n"
		"void main()\n"
		"{\n"
		"	gl_Position = position;\n"
		"}\n";
	std::string fragmentShader =
		"#version 330 core\n"
		"\n"
		"layout(location = 0) out vec4 color;\n"        //0 is the INDEX of our attribute. Vec4 is because OpenGL position is eventually a vec4
		"\n"
		"void main()\n"
		"{\n"
		"	color = vec4(1.0, 0.5 , 0.2 , 1.0);\n"    //color is actually float between 0 and 1 - 0:B, 1:W
		"}\n";
	unsigned int shader = createShader(vertexShader, fragmentShader);
	glUseProgram(shader);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3); //draw the triangle

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}