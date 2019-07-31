#include <iostream>

#include <stdlib.h>
#include <time.h>
// We are using the glew32s.lib
// Thus we have a define statement
// If we do not want to use the static library, we can include glew32.lib in the project properties
// If we do use the non static glew32.lib, we need to include the glew32.dll in the solution folder
// The glew32.dll can be found here $(SolutionDir)\..\External Libraries\GLEW\bin\Release\Win32

#include "Shader.h"
#include "Entity.h"
#include "QuadTree.h"



// Variables for the Height and width of the window
const GLint WIDTH = 800, HEIGHT = 800;

int main()
{
#pragma region OpenGL_SetUp
	//Initializes the glfw
	glfwInit();

	// Setting the required options for GLFW

	// Setting the OpenGL version, in this case 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Setting the Profile for the OpenGL.
	// Option of choosing between Compat and Core.
	// We choose core, because we won't be using any deprecated function from the previous versions of OpenGL
	// In other words, no backward compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Setting the forward compatibility of the application to true
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// We don't want the window to resize as of now.
	// Therefore we will set the resizeable window hint to false.
	// To make is resizeable change the value to GL_TRUE.
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create the window object
	// The first and second parameters passed in are WIDTH and HEIGHT of the window we want to create
	// The third parameter is the title of the window we want to create

	// NOTE: Fourth paramter is called monitor of type GLFWmonitor, used for the fullscreen mode.
	//		 Fifth paramter is called share of type GLFWwindow, here we can use the context of another window to create this window
	// Since we won't be using any of these two features for the current tutorial we will pass nullptr in those fields
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Shaders Tutorial", nullptr, nullptr);

	// We call the function glfwGetFramebufferSize to query the actual size of the window and store it in the variables.
	// This is useful for the high density screens and getting the window size when the window has resized.
	// Therefore we will be using these variables when creating the viewport for the window
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	// Check if the window creation was successful by checking if the window object is a null pointer or not
	if (window == nullptr)
	{
		// If the window returns a null pointer, meaning the window creation was not successful
		// we print out the messsage and terminate the glfw using glfwTerminate()
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		// Since the application was not able to create a window we exit the program returning EXIT_FAILURE
		return EXIT_FAILURE;
	}

	// Creating a window does not make it the current context in the windows.
	// As a results if the window is not made the current context we wouldn't be able the perform the operations we want on it
	// So we make the created window to current context using the function glfwMakeContextCurrent() and passing in the Window object
	glfwMakeContextCurrent(window);

	// Enable GLEW, setting glewExperimental to true.
	// This allows GLEW take the modern approach to retrive function pointers and extensions
	glewExperimental = GL_TRUE;

	// Initialize GLEW to setup OpenGL function pointers
	if (GLEW_OK != glewInit())
	{
		// If the initalization is not successful, print out the message and exit the program with return value EXIT_FAILURE
		std::cout << "Failed to initialize GLEW" << std::endl;

		return EXIT_FAILURE;
	}

	// Setting up the viewport
	// First the parameters are used to set the top left coordinates
	// The next two parameters specify the height and the width of the viewport.
	// We use the variables screenWidth and screenHeight, in which we stored the value of width and height of the window,
	glViewport(0, 0, screenWidth, screenHeight);
#pragma endregion

	//Instantiate our entities
	int entityCount = 2000;
	std::vector<Entity*> entityList;
	std::vector< glm::vec2 > linePoints;
	//Our quadtree
	QuadTree* quad = new QuadTree();

	//seed our random number generator using the current system time
	srand(time(NULL));
	float randX;
	float randY;
	//Size of a entity quad size
	float side = 0.01f;
	for (int i = 0; i < entityCount; i++)
	{
		entityList.push_back(new Entity());
		entityList[i]->SetVertices() = {
			// Triangle 1		
			glm::vec3(-0.5f, -0.5f, 0.0f),
			glm::vec3(0.5f, -0.5f, 0.0f),
			glm::vec3(-0.5f, 0.5f, 0.0f),
			//Triangle 2
			glm::vec3(-0.5f, 0.5f, 0.0f),
			glm::vec3(0.5f, -0.5f, 0.0f),
			glm::vec3(0.5f, 0.5f, 0.0f)
		};

		randX = ((rand() % 210) - 100) / 100.0f;
		randY = ((rand() % 210) - 100) / 100.0f;
		entityList[i]->transform->position = glm::vec3(randX, randY, 0.0);
		entityList[i]->transform->scale = glm::vec3(side, side, 1.0f);
		entityList[i]->LoadBuffers();

		//Insert into our tree
		quad->Insert(entityList[i]->transform->position, linePoints);	
	}	

	//OpenGL buffer loading
	GLuint quadVAO;
	GLuint quadVBO;

	glGenVertexArrays(1, &quadVAO);

	glGenBuffers(1, &quadVBO);																						
	glBindVertexArray(quadVAO);																						
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);																		  

	//Defining VBO data
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(glm::vec2)*linePoints.size(), 
		&linePoints[0],					 
		GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), 0);
	glBindBuffer(0, quadVBO);
	glBindVertexArray(0);


	//Creating, initalizing and using our shader(s)
	Shader basicShader;
	basicShader.load();
	basicShader.use();
	
	// This is the game loop, the game logic and render part goes in here.
	// It checks if the created window is still open, and keeps performing the specified operations until the window is closed
	while (!glfwWindowShouldClose(window))
	{
		// Checking for events/inputs
		glfwPollEvents();

		// Specifies the RGBA values which will be used by glClear to clear the color buffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

		// Clears contents of a screen to a preset value, previously selected, by passing in what buffer we want to clear
		// In this case we are clearing the color buffer. Thus setting a background color to the color specified previously in glClearColor
		glClear(GL_COLOR_BUFFER_BIT);

		
		//Render entities
		for (int i = 0; i < entityCount; i++)
		{
			entityList[i]->Update();
			entityList[i]->RenderEntity();
		}

		//Draw the quadtree
		glUniformMatrix4fv(2, 1, GL_FALSE, &glm::scale(glm::vec3(1, 1, 1))[0][0]);
		glBindVertexArray(quadVAO);
		glDrawArrays(GL_LINES, 0, linePoints.size());
		glBindVertexArray(0);


		// Swaps the front and back buffers of the specified window
		glfwSwapBuffers(window);
	}

	for (int i = 0; i < entityCount; i++)
	{
		delete entityList[i];
	}
	delete quad;
	// Terminate all the stuff related to GLFW and exit the program using the return value EXIT_SUCCESS
	glfwTerminate();

	return EXIT_SUCCESS;
}