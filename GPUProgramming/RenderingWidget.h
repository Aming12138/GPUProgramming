#pragma once
#include <glew.h>
#include <QtOpenGL\QGLWidget>
#include <glut.h>

class BaseShader;
class CArcBall;
class Model;
class QMouseEvent;

class RenderingWidget : public QGLWidget
{
public:
	RenderingWidget(QWidget* parent =0);
	~RenderingWidget(void);

	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();

	void mousePressEvent(QMouseEvent* e);
	void mouseMoveEvent(QMouseEvent* e);
	void mouseReleaseEvent(QMouseEvent* e);
	void wheelEvent(QWheelEvent* e);

	void Open();
	void Save();

private:
	CArcBall* arcBall;
	Model* modelData;
	BaseShader* shader;
	double distance;

};

