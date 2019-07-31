#pragma once
#define GLEW_STATIC
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
//Define how many entites a quad cand hold before it splits
#define MAX_COUNT 5


class QuadTree
{
	//Children of this quad
	QuadTree* children = nullptr;

	//Points stored in this quad
	std::vector<glm::vec2> points;
	int pointCount = 0;

	//Depth level
	int level = 0;

	//"min" and "max" of this quad
	glm::vec2 topLeft;
	glm::vec2 botRight;

	bool InBounds(glm::vec2 point);
	int ChooseChild(glm::vec2 point);
	void SplitQuad(std::vector<glm::vec2>& linePoints);

public:
	QuadTree();
	QuadTree(glm::vec2 tL, glm::vec2 bR, int l);
	~QuadTree();


	void Insert(glm::vec2 point, std::vector<glm::vec2>& linePoints);


};


