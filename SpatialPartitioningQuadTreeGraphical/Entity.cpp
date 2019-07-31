#include "Entity.h"





Entity::Entity()
{
	transform = new Transform();
}


Entity::~Entity()
{
	delete transform;
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Entity::Update()
{
	if (recalculateWMatrix)
	{
		transform->CalculateWorldMatrix();
		recalculateWMatrix = false;
	}

	glUniformMatrix4fv(2, 1, GL_FALSE, &transform->GetWorldMatrix()[0][0]);
}

void Entity::LoadBuffers()
{
	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &VBO);																							//Generating VBO
	glBindVertexArray(VAO);																						//Binding the VAO so we can manipulate it
	glBindBuffer(GL_ARRAY_BUFFER, VBO);																		    //Binding the VBO so we can manipulate it

	//Defining VBO data
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(glm::vec3)*vertices.size(), //The data size is the size of one vec3 multiplied by the number of vertices
		&vertices[0],					  //We want to start at the first index of the vector, so we point to it
		GL_STATIC_DRAW);

	//Defining our vertex data

	//Position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);

	// Enable the generic vertex attribute array created above using the the function glEnableVertexAttributeArray,
	// passing in the index of the vertex attribute array

	//Unbinding both our OpenGL objects
	glBindBuffer(0, VBO);
	glBindVertexArray(0);

}

void Entity::RenderEntity()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	glBindVertexArray(0);	//Unbind after we're finished drawing this entity.
}

std::vector<glm::vec3> & Entity::SetVertices()
{
	return vertices;
}
