#pragma once
#include "BaseShader.h"


class SimpleDerivedShader:public BaseShader
{
public:
	SimpleDerivedShader(Mesh3D *meshFromMesh3D = NULL);
	~SimpleDerivedShader(void);
	void CreateShader();
	void DrawModel(Model *modelData, CArcBall *arcBall, double distance);
};

