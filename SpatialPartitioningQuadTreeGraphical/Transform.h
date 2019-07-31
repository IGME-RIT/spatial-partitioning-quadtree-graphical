#pragma once

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
class Transform
{
	glm::mat4 rotMatrix;
	glm::mat4 worldMatrix;



public:
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 eulerRotation;

	Transform();
	~Transform();

	glm::mat4 GetWorldMatrix();
	void CalculateWorldMatrix();
};

