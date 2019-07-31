#include "QuadTree.h"


//Defualt constructor
QuadTree::QuadTree()
{
	topLeft = glm::vec2(-1, 1);
	botRight = glm::vec2(1, -1);
	level = 0;

}

//Constructor called on quad children
QuadTree::QuadTree( glm::vec2 tL, glm::vec2 bR, int l)
{
	topLeft = tL;
	botRight = bR;
	level = l;

}

//Recursive destructor
QuadTree::~QuadTree()
{
	if (children != nullptr)
		delete[] children;
}

//Recursive insert method for a point and a refernce to container holding quadtree render points
void QuadTree::Insert(glm::vec2 point, std::vector<glm::vec2>& linePoints)
{	
	//If the point is not contained in this quad, retrurn
	if (!InBounds(point))
		return;

	//If we have already split this quad, find it's child
	//which contains this point and insert it there
	if (children !=  nullptr)
	{
		//Get child index
		int index = ChooseChild(point);

		if (index > -1)
			children[index].Insert(point, linePoints);

		return;
	}

	//If we have not yet split this quad:
	//If we have exceeded the max number of contained points, 
	//split the quad and distribute contained points
	//Constrained by a max depth of 20
	if (pointCount == MAX_COUNT && level<20)
	{
		SplitQuad(linePoints);
		Insert(point, linePoints);
	}
	else
	{
		points.push_back(point);
		pointCount++;
		
	}

}




//Check if the quad contains the point
//Simialr to AABB checking
bool QuadTree::InBounds(glm::vec2 point)
{
	return (point.x >= topLeft.x &&
		point.x <= botRight.x &&
		point.y >= botRight.y &&
		point.y <= topLeft.y);
}

//Finds the child that contains the point
int QuadTree::ChooseChild(glm::vec2 point)
{
	for (int i = 0; i < 4; i++)
		if (children[i].InBounds(point))
			return i;

	return -1;
}

//Split a parent quad into 4 child quads
void QuadTree::SplitQuad(std::vector<glm::vec2>& linePoints)
{
	float halfWidth = abs(topLeft.x - botRight.x) / 2.0f;
	float halfHeight = abs(topLeft.y - botRight.y) / 2.0f;

	children = new QuadTree[4];

	//Top Left quad
	children[0]= QuadTree(topLeft,
						  glm::vec2(topLeft.x + halfWidth, botRight.y + halfHeight), 
						  level + 1);
	//Top Right quad
	children[1] = QuadTree(glm::vec2(topLeft.x + halfWidth, topLeft.y),
						   glm::vec2(botRight.x, botRight.y + halfHeight), 
						   level + 1);
	//Bottom Right quad
	children[2] = QuadTree(glm::vec2(topLeft.x + halfWidth, botRight.y + halfHeight),
						   botRight,
						   level + 1);
	//Bottom Left quad
	children[3] = QuadTree(glm::vec2(topLeft.x, botRight.y + halfHeight),
						   glm::vec2(topLeft.x + halfWidth, botRight.y), 
						   level + 1);

	//Vertical Line
	linePoints.push_back(glm::vec2(topLeft.x + halfWidth, topLeft.y));
	linePoints.push_back(glm::vec2(topLeft.x + halfWidth, botRight.y));

	//Horizontal Line
	linePoints.push_back(glm::vec2(topLeft.x, botRight.y + halfHeight));
	linePoints.push_back(glm::vec2(botRight.x, botRight.y + halfHeight));

	//Distribute parents points into children
	for (int i = pointCount-1; i >=0; i--)
	{
		int index = ChooseChild(points[i]);

		if (index > -1)
		{
			children[index].Insert(points[i], linePoints);
		}		
	}

	pointCount = 0;
}



