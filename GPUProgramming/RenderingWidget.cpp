#include "RenderingWidget.h"
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qstring.h>
#include <qtextcodec.h>
#include "Model.h"
#include "ArcBall.h"
#include "vmath.h"
#include "SimpleDerivedShader.h"
#include <qmouseevent.h>
#define DELETE_PTR(ptr)\
	if(ptr != NULL)\
	{\
		delete ptr;\
		ptr = NULL;\
	}\


RenderingWidget::RenderingWidget(QWidget * parent):QGLWidget(parent),distance(2.0)
{
	arcBall = new CArcBall(width(), height());
	modelData = new Model();
}

RenderingWidget::~RenderingWidget()
{
	DELETE_PTR(arcBall);
	DELETE_PTR(modelData);
	DELETE_PTR(shader);
}

void RenderingWidget::initializeGL()
{
	glewInit();
	glClearColor(0.3, 0.3, 0.3, 0.0);
	glEnable(GL_DEPTH_TEST);
	glLineWidth(2.3);
	
	shader = new SimpleDerivedShader(NULL);
	shader->CreateShader();
}

void RenderingWidget::resizeGL(int w, int h)
{
	int m = w;
	if (h < w)
		m = h;
	glViewport(0, 0, m, m);
	arcBall->reSetBound(w, h);
}

void RenderingWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (modelData->vertexesOfTriangles.empty)
	{
		return;
	}
	shader->DrawModel(modelData, arcBall, distance);
}

void RenderingWidget::mousePressEvent(QMouseEvent * e)
{
	switch (e->button())
	{
	case Qt::LeftButton:
		arcBall->MouseDown(e->pos());
		break;
	default:
		break;
	}
	updateGL();
}

void RenderingWidget::mouseMoveEvent(QMouseEvent * e)
{
	switch (e->buttons())
	{
		setCursor(Qt::ClosedHandCursor);
	case Qt::LeftButton:
		arcBall->MouseMove(e->pos());
		break;
	default:
		break;
	}
	updateGL();
}

void RenderingWidget::mouseReleaseEvent(QMouseEvent * e)
{
	switch (e->button())
	{
	case Qt::LeftButton:
		arcBall->MouseUp(e->pos());
		setCursor(Qt::ArrowCursor);
		break;
	default:
		break;
	}
}

void RenderingWidget::wheelEvent(QWheelEvent * e)
{
	distance += e->delta()*0.001;
	distance = distance < 0 ? 0 : distance;
	updateGL();
}

void RenderingWidget::Open()
{
	QString fileName = QFileDialog::getOpenFileName(this, "Open", "Obj Files(*.obj)", NULL);
	if (fileName.isEmpty())
		return;
	QTextCodec* code = QTextCodec::codecForName("gd18030");
	QTextCodec::setCodecForLocale(code);

	QByteArray byfilename = fileName.toLocal8Bit();
	modelData->sourceData->LoadFromOBJFileWithNormal(byfilename.data());

	modelData->GenerateVertexesFromSource();
}

void RenderingWidget::Save()
{
	if (modelData->sourceData->num_of_vertex_list() == 0)
	{
		emit(QString("The Mesh is Empty !"));
		return;
	}
	QString filename = QFileDialog::getSaveFileName(this, tr("Write Mesh"), "..", tr("Mesh (*.obj)"));
	if (filename.isEmpty())
		return;
	modelData->sourceData->WriteToOBJFileWithNormal(filename.toLatin1().data());

}
