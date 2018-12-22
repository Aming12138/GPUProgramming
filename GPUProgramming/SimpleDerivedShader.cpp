#include "SimpleDerivedShader.h"
#include "Model.h"
#include "vmath.h"
#include "ArcBall.h"
#include "ArcBall.h"


SimpleDerivedShader::SimpleDerivedShader(Mesh3D * meshFromMesh3D=NULL): BaseShader(meshFromMesh3D)
{
}

SimpleDerivedShader::~SimpleDerivedShader(void)
{
}

void SimpleDerivedShader::CreateShader()
{
	const GLchar *vertexShaderSrc = 
		"#version 430\n"
		"uniform mat4 PMV;\n"
		"layout(location=0) in vec3 position;\n"
		"out vec4 ocolor;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = PMV * vec4(position,1.0);\n"
		"	ocolor = vec4(1,1,1,1.0);\n"
		"}\n";

	const GLchar *fragmentShaderSrc = 
		"#version 430\n"
		"in vec4 ocolor;\n"
		"out vec4 Fragment;\n"
		"void main()\n"
		"{\n"
		"	Fragment = ocolor;\n"
		"}\n";

	GLuint vertexShader = GenerateAndCompiler(GL_VERTEX_SHADER, vertexShaderSrc);
	GLuint fragmentShader = GenerateAndCompiler(GL_FRAGMENT_SHADER, fragmentShaderSrc);

	LinkProgram(vertexShader, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

void SimpleDerivedShader::DrawModel(Model* modelData, CArcBall *arcBall, double distance)
{
	Model::Vertex *pvertexesOfTriangles = &((modelData->vertexesOfTriangles)[0]);
	GLuint vbbo;
	Matrix4f modelView = Matrix4f::createLookAt(Vector3f(0, 0, distance), Vector3f(0, 0, 0),Vector3f(0,1,0));
	Matrix4f proj = Matrix4f::createFrustum(-1, 1, -1, 1, 1, 50);

	float modelTranArray[16];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			modelTranArray[i * 4 + j] = arcBall->GetBallMatrix()[i * 4 + j];
		}
	}
	Matrix4f modelTranMatrix(modelTranArray);
	Matrix4f combined = proj*modelView*modelTranMatrix;

	glUseProgram(program);
	glUniformMatrix4fv(glGetUniformLocation(program, "PMV"), 1, GL_FALSE, (float*)&combined);

	glGenBuffers(1, &vbbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbbo);
	glBufferData(GL_ARRAY_BUFFER, (modelData->vertexesOfTriangles.size()) * sizeof(Model::Vertex), pvertexesOfTriangles, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Model::Vertex), (void*)0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glDrawArrays(GL_TRIANGLES, 0, modelData->vertexesOfTriangles.size());
	glDeleteBuffers(1, &vbbo);


}