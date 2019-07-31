//2D Entity

#pragma once


#define GLEW_STATIC
#include <vector>
#include "Transform.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

//GLM provides new data types and math helper functions for any vector math we want to do.
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

class Entity
{
	


	std::vector<glm::vec3> vertices;
	GLuint VAO;
	GLuint VBO;

	bool recalculateWMatrix = true;


public:
	Entity();
	virtual ~Entity();

	Transform* transform;

	void Update();
	void LoadBuffers();
	void RenderEntity();
	std::vector<glm::vec3>& SetVertices();

	
};

