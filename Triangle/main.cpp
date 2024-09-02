#include <fstream>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaderClass.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"


GLfloat vertices[] =
{ //               COORDINATES                  /     COLORS           //
	-0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.0f, 1.0f,  0.0f, // Lower left corner
	 0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower right corner
	 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,     1.0f, 0.6f,  0.32f, // Upper corner
	-0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner left
	 0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner right
	 0.0f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f  // Inner down
};

// Indices for vertices order
GLuint indices[] =
{
	0, 3, 5, // Lower left triangle
	3, 2, 4, // Lower right triangle
	5, 4, 1 // Upper triangle
};

int main()
{

    // starts glfw
    glfwInit();

    // version hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // profile hint (package of functions? apparently there's only core and compatibility
    // where compatibility has modern and legacy functions (for compatibility!)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // initializing vertices for two square diamonds next to eachother, touching on 1 corner

    // creates a window. args in order:
    // width, height, name, is fullscreen, share (not sure what share is quite yet)
    GLFWwindow* window = glfwCreateWindow(800, 800, "LearnOpenGL", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

    // context is an abstract idea of all of the opengl stuff that's happening
    glfwMakeContextCurrent(window);

    gladLoadGL(); // loads glad and connects it to the glfw stuff

    glViewport(0, 0, 800, 800); // gives opengl the window? not quite sure why it doesn't have it

    // SHADERRRRRR. Used to be all written out, now it's all done in a constructor
	// because we love OOP
	
	Shader shaderProgram("default.vert", "default.frag");

    // Vertex Array Object, Vertex Buffer Object, Index Buffer Object
    // VAO: pointer to array of pointers to VBOs
    // VBO: object to draw
    // EBO: indices that point to vertices, so we don't have to redundantly store the same one multiple times
	VAO VAO1;
	// binds the buffer to be the current array buffer. idk what an array buffer is
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));
	

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// get reference to scale uniform
	
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");


    // buffers: the way opengl works is by having two buffers - the front and back buffers.
    // When you edit and write to a buffer by using the commands above, you're writing to
    // the back buffer. To show the edited buffer, you then _swap_ the buffers, making the
    // back buffer into the front buffer.

    glfwSwapBuffers(window);

    while (!glfwWindowShouldClose(window))
    {
		glClearColor(0.00f, 0.50f, 0.00f, 1.0f); // prepares to paint the screen one colour
		glClear(GL_COLOR_BUFFER_BIT); // actually executes the clearing (not sure why these two steps need to happen seperately?)
		shaderProgram.Activate();
		glUniform
        // makes VAO the current vertex array. not necessary right now since we only have one
        // array, but when we have more, it's good to get into the habit
		VAO1.Bind();

        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);


        glfwPollEvents(); // without this line, the window will not respond to things like
                          // resizing, closing, and minimizing
    }

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
