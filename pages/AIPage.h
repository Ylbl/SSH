#pragma once

#include <QObject>
#include "BasePage.h"
#include <ElaComboBox.h>
#include <ElaMultiSelectComboBox.h>
#include <ElaToggleButton.h>
#include <QLabel>
#include <qthread.h>

class ElaPushButton;

class AIPage  : public BasePage
{
	Q_OBJECT
private:
	ElaComboBox* cbox_select_camera;
	ElaMultiSelectComboBox* mcbox_select_model;
	ElaToggleButton* tbnt_start;
	ElaPushButton* btn_select_model;
	QLabel* label_img;
	QImage* image_img = new QImage();
	int crmera_index = 0;

	QStringList* comboList;
public:
	Q_INVOKABLE explicit AIPage(QWidget *parent);
	~AIPage();

	void init_camera();
};


class Worker : public QThread
{
public:
	void run(int _crmera_index,QImage* _image_img,QStringList* _result_list);
};