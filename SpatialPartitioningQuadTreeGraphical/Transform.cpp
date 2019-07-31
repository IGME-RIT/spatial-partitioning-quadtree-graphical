#include "Transform.h"



Transform::Transform()
{
	scale = glm::vec3(1.f, 1.f, 1.f);
	position = glm::vec3();
	eulerRotation = glm::vec3();
}


Transform::~Transform()
{
}

glm::mat4 Transform::GetWorldMatrix()
{
	return worldMatrix;
}

void Transform::CalculateWorldMatrix()
{
	rotMatrix = glm::yawPitchRoll(glm::radians(eulerRotation.y), glm::radians(eulerRotation.x), glm::radians(eulerRotation.z));//creates a rotation matrix based on a yaw(y rotation), pitch (x rotation) and roll (z rotation)

	//WORLD MATRIX CALCULATION
		//We want to create a 4x4 matrix for our triangle
		//This matrix will have 3 main components
		//Translation matrix - tells us where to move our vertices
		//Rotation matrix -	tells us how to rotate the model
		//Scale matrix - tells us the size of the model
		//World Matrix = Translation Matrix* Rotation Matrix *Scale Matrix  ***IN ORDER***
		//With matrix multiplication, order matters.
		//Otherwise we manipulate vertices incorrectly
	worldMatrix = glm::translate(position) *													//creates a translation matrix taking our position as the parameter
		rotMatrix*
		glm::scale(scale);															//creates a scale matrix taking our scale vector


}
