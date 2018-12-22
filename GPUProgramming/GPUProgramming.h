#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GPUProgramming.h"

class GPUProgramming : public QMainWindow
{
	Q_OBJECT

public:
	GPUProgramming(QWidget *parent = Q_NULLPTR);

private:
	Ui::GPUProgrammingClass ui;
};
