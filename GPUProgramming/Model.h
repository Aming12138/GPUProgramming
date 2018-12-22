#pragma once
#include "Mesh3D.h"

class Model
{
public:
	typedef struct Vertex
	{
		Vertex()
		{
			position = Vec3f(0, 0, 0);
			texCoord = Vec2f(0, 0);
			normal = Vec3f(0, 0, 0);
			color = Vec4f(0, 0, 0, 0);
		}
		Vec3f position;
		Vec2f texCoord;
		Vec3f normal;
		Vec4f color;
	}Vertex;

public:
	Model();
	~Model();
	void GenerateVertexesFromSource();

public:
	Mesh3D *sourceData;
	std::vector<Vertex> vertexesOfTriangles;

};

