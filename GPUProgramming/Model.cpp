#include "Model.h"

Model::Model(void):vertexesOfTriangles(NULL)
{
	sourceData = new Mesh3D();
}


Model::~Model(void)
{
}

void Model::GenerateVertexesFromSource()
{
	if (sourceData->num_of_vertex_list() == 0)
	{
		return;
	}

	std::vector<HE_face *> *facesList = sourceData->get_faces_list();
	for (int  i = 0; i < sourceData->num_of_face_list(); i++)
	{
		Vertex tempVertex;
		std::vector<Vertex> tempVertexVec;
		HE_face* nowFace = facesList->at(i);

		HE_edge* nowEdge = nowFace->pedge_;
		do
		{
			tempVertex.position = nowEdge->pvert_->position();
			tempVertex.color = nowEdge->pvert_->color();
			tempVertex.normal = nowEdge->pvert_->normal();
			tempVertex.texCoord = Vec2f(nowEdge->pvert_->texCoordinate()[0], nowEdge->pvert_->texCoordinate()[1]);
			tempVertexVec.push_back(tempVertex);
			nowEdge = nowEdge->pnext_;
		} while (nowEdge != nowFace->pedge_);

		for (int j = 0; j < tempVertexVec.size() - 2; j++)
		{
			vertexesOfTriangles.push_back(tempVertexVec[j]);
			vertexesOfTriangles.push_back(tempVertexVec[j + 1]);
			vertexesOfTriangles.push_back(tempVertexVec[j + 2]);
		}

	}


}
