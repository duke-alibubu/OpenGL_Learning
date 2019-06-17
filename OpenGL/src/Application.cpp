#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"


struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};


static ShaderProgramSource parseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);
	
	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	std::string line;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)  //invalid string position
		{        
			if (line.find("vertex") != std::string::npos)       //set mode to vertex
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)       //set mode to fragment
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << "\n";
		}
	}

	return { ss[0].str(), ss[1].str()};
}

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

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //i want my major version to be OpenGL 3 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //minor version to be 3 also
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //generate a core profile!!! IMPORTANT 
	// if we use core -- we have to created one ourself.
	// compatibility profile -- the default one.

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
		std::cout << "Error!" << std::endl;
	std::cout << glGetString(GL_VERSION) << std::endl;

	float positions[] = {
		-0.5f, -0.5f,   //0
		 0.5f, -0.5f,   //1
		 0.5f,  0.5f,   //2
		-0.5f, 0.5f    //3
	};

	unsigned int indices[] = {
		0, 1, 2,         //triangle 1
		2, 3, 0	         //triangle 2
	};


	unsigned int vao;    //vertex array object
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	VertexBuffer vb(positions, 4 * 2 * sizeof(float));


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, 0);         //2: cause 1 vertex takes 2 float - vec2. VERTEX LAYOUT
	// link the buffer to the VAO 

	//index buffer
	IndexBuffer ib(indices, 6);


	ShaderProgramSource source = parseShader("res/shaders/Basic.shader");
	unsigned int shader = createShader(source.VertexSource, source.FragmentSource);
	glUseProgram(shader);

	int location = glGetUniformLocation(shader, "u_Color");    //retrieve the location of the color variable? 
	glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f);

	//unbind everything
	glBindVertexArray(0);
	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	float r = 0.2f;
	float increment = 0.05f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

		//what is here! we bind our shader, we set up our uniform, we bind our vertex buffer - set up the layout of that vertex buffer and then bind the index buffer!
		glUseProgram(shader);
		glUniform4f(location, r, 0.3f, 0.8f, 1.0f);
		
		glBindVertexArray(vao);
		ib.bind();

		
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr); //draw the triangle. 6 = number of indices. Nullptr cause we have 
																   //alr bounded ibo to GL_ELEMENT_ARRAY_BUFFER
																   //If did not bound ibo to GL_ELEMENT_ARRAY_BUFFER have to specify "indices"
																   //Have to be unsigned int, because buffer's made up of unsigned int					
		if (r > 1.0f)
			increment = -0.05f;
		else if (r < 0.0f)
			increment = 0.05f;
		
		r += increment;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

	glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}