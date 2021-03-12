#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>

#include <GLFW/glfw3.h>
GLFWwindow* window;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 

#include <common/shader.hpp>
using namespace glm;

int main(void)
{
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(1024, 768, "HW1", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile

	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);


	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint programID = LoadShaders("SimpleTransform.vertexshader", "SingleColor.fragmentshader");

	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	glm::mat4 Projection = glm::perspective(glm::radians(30.0f), 4.0f / 3.0f, 0.1f, 100.0f);


	static const GLfloat g_vertex_buffer_data[] = {
		//	Основание
		0.0f, 0.0f, 0.0f,
		-0.5f, -0.02f, 0.0f,
		-0.25f, -0.45f, 0.0f,
		
		0.0f, 0.0f, 0.0f,
		-0.25f, -0.45f, 0.0f,
		0.25f, -0.45f, 0.0f,

		0.0f, 0.0f, 0.0f,
		0.25f, -0.45f, 0.0f,
		0.5f, -0.01f, 0.0f,

		0.0f, 0.0f, 0.0f,
		0.5f, -0.01f, 0.0f,
		0.24f, 0.42f, 0.0f,

		0.0f, 0.0f, 0.0f,
		0.24f, 0.42f, 0.0f,
		-0.26f, 0.42f, 0.0f,

		0.0f, 0.0f, 0.0f,
		-0.26f, 0.42f, 0.0f,
		-0.5f, -0.02f, 0.0f,

		//Веришина
		0.0f, 0.0f, 1.0f,
		-0.5f, -0.02f, 0.0f,
		-0.25f, -0.45f, 0.0f,

		0.0f, 0.0f, 1.0f,
		-0.25f, -0.45f, 0.0f,
		0.25f, -0.45f, 0.0f,

		0.0f, 0.0f, 1.0f,
		0.25f, -0.45f, 0.0f,
		0.5f, -0.01f, 0.0f,

		0.0f, 0.0f, 1.0f,
		0.5f, -0.01f, 0.0f,
		0.24f, 0.42f, 0.0f,

		0.0f, 0.0f, 1.0f,
		0.24f, 0.42f, 0.0f,
		-0.26f, 0.42f, 0.0f,

		0.0f, 0.0f, 1.0f,
		-0.26f, 0.42f, 0.0f,
		-0.5f, -0.02f, 0.0f,
	};
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	GLfloat g_color_buffer_data[] = {
		255, 0, 51,
		255, 0, 51,
		255, 0, 51,

		255, 0, 51,
		255, 0, 51,
		255, 0, 51,
		
		255, 0, 51,
		255, 0, 51,
		255, 0, 51,

		255, 0, 51,
		255, 0, 51,
		255, 0, 51,

		255, 0, 51,
		255, 0, 51,
		255, 0, 51,

		255, 0, 51,
		255, 0, 51,
		255, 0, 51,

		255, 255, 0,
		255, 0, 51,
		255, 0, 51,

		255, 255, 0,
		255, 0, 51,
		255, 0, 51,

		255, 255, 0,
		255, 0, 51,
		255, 0, 51,

		255, 255, 0,
		255, 0, 51,
		255, 0, 51,

		255, 255, 0,
		255, 0, 51,
		255, 0, 51,

		255, 255, 0,
		255, 0, 51,
		255, 0, 51,
	};
	for (int i = 0; i < 36 * 3; i++) {
		g_color_buffer_data[i] = g_color_buffer_data[i] / 255;
	}
	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(programID);

		const float radius = 5.0f;
		float camX = sin(glfwGetTime()) * radius;
		float camY = sin(glfwGetTime()) * radius;
		float camZ = cos(glfwGetTime()) * radius;

		glm::mat4 View = glm::lookAt(
			glm::vec3(camX, camY, camZ),
			glm::vec3(0, 0, 0),
			glm::vec3(0, 1, 0)
		);
		
		glm::mat4 Model = glm::mat4(1.0f);

		
		glm::mat4 MVP = Projection * View * Model;


		
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,      
			3,      
			GL_FLOAT,
			GL_FALSE,
			0,       
			(void*)0 
		);
		
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glVertexAttribPointer(
			1,  
			3,      
			GL_FLOAT,
			GL_FALSE,
			0,       
			(void*)0 
		);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		glDisableVertexAttribArray(0);
		// Draw nothing, see you in tutorial 2 !

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}