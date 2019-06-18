#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"


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

	VertexBuffer vb(positions, 4 * 2 * sizeof(float));
	VertexArray va;
	VertexBufferLayout layout;
	layout.push<float>(2);
	va.addBuffer(vb, layout);
	//va.bind();

 

	//index buffer
	IndexBuffer ib(indices, 6);

	Shader shader("res/shaders/Basic.shader");
	shader.bind();

	shader.setUniform4f("u_Color" ,0.2f, 0.3f, 0.8f, 1.0f);
	//unbind everything
	va.unbind();
	vb.unbind();
	ib.unbind();
	shader.unbind();
	
	float r = 0.2f;
	float increment = 0.05f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

		//what is here! we bind our shader, we set up our uniform, we bind our vertex buffer - set up the layout of that vertex buffer and then bind the index buffer!
		shader.bind();

		shader.setUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
		
		va.bind();
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


    glfwTerminate();
    return 0;
}