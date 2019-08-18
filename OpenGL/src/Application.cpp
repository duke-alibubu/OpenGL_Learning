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
#include "Renderer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

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
		-0.5f, -0.5f, 0.0f, 0.0f,   //0
		 0.5f, -0.5f, 1.0f, 0.0f,  //1
		 0.5f,  0.5f, 1.0f, 1.0f,  //2
		-0.5f,  0.5f, 0.0f, 1.0f    //3
	};

	unsigned int indices[] = {
		0, 1, 2,         //triangle 1
		2, 3, 0	         //triangle 2
	};

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	VertexBuffer vb(positions, 4 * 4 * sizeof(float));        //4 float per vertex
	VertexArray va;
	VertexBufferLayout layout;
	layout.push<float>(2);
	layout.push<float>(2);
	va.addBuffer(vb, layout);
	//va.bind();

 

	//index buffer
	IndexBuffer ib(indices, 6);

	glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);     //By default on a 4:3 ratio --> Set it to 1:1
		 
	Shader shader("res/shaders/Basic.shader");
	shader.bind();

	shader.setUniform4f("u_Color" ,0.2f, 0.3f, 0.8f, 1.0f); 
	shader.setUniformMat4f("u_MVP", proj);
	//unbind everything

	Texture texture("res/Textures/Tree.png");
	texture.bind();   //if bind 2 - which means slot 2 - need to set uniform location to slot 2 also
	shader.setUniform1i("u_Texture", 0);   //0 becuz we bound our texture to slot 0 by default

	va.unbind();
	vb.unbind();
	ib.unbind();
	shader.unbind();

	Renderer renderer;
	
	float r = 0.2f;
	float increment = 0.05f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
		renderer.clear();

		//what is here! we bind our shader, we set up our uniform, we bind our vertex buffer - set up the layout of that vertex buffer and then bind the index buffer!
		shader.bind();
		shader.setUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

		renderer.draw(va, ib, shader);
						
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