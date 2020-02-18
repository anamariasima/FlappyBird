#include "Object2D.h"

#include <Core/Engine.h>



Mesh* Object2D::CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };
	
	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}

Mesh* Object2D::CreateRectangle(std::string name, glm::vec3 leftBottomCorner, float length, float height, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, height, 0), color),
		VertexFormat(corner + glm::vec3(0, height, 0), color)
	};

	Mesh* rectangle = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };
	
	if (!fill) {
		rectangle->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		
		indices.push_back(0);
		indices.push_back(2);
	}

	rectangle->InitFromData(vertices, indices);
	return rectangle;
}

Mesh* Object2D::CreateTriangle(std::string name, glm::vec3 leftBottomCorner, float length, float height, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, height/2, 0), color),
		VertexFormat(corner + glm::vec3(0, height, 0), color),
		
	};

	Mesh* triangle = new Mesh(name);
	std::vector<unsigned short> indices = {0, 1, 2};
	
	if (!fill) {
		triangle->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		
		indices.push_back(0);
		indices.push_back(2);
	}

	triangle->InitFromData(vertices, indices);
	return triangle;
}

Mesh* Object2D::CreateCircle(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;


	std::vector<VertexFormat> vertices;

	vertices.push_back(VertexFormat(corner + glm::vec3(length, 0, 0), color));
	for (int i = 0; i < 3600; i++) {
		vertices.push_back(VertexFormat(corner + glm::vec3(cos(i / 3600.0 * 2 * 3.14) * length, sin(i / 3600.0 * 2 * 3.14) * length, 0), color));
	}

	Mesh* circle = new Mesh(name);

	std::vector<unsigned short> indices;
	for (int i = 0; i <= 3600 - 1; i++) {
		indices.push_back(0);
		indices.push_back(i + 1);
		indices.push_back(i);
	}

	if (!fill) {
		circle->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		
		indices.push_back(0);
		indices.push_back(2);
	}

	circle->InitFromData(vertices, indices);
	return circle;
}
