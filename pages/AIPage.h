#pragma once

#include <QObject>
#include "BasePage.h"
#include <ElaComboBox.h>
#include <ElaMultiSelectComboBox.h>
#include <ElaToggleButton.h>
#include <QLabel>

class ElaPushButton;

class AIPage  : public BasePage
{
	Q_OBJECT
private:
	ElaComboBox* cbox_select_camera;
	ElaMultiSelectComboBox* mcbox_select_model;
	ElaToggleButton* tbnt_start;
	ElaPushButton* btn_select_model;

	QLabel* img;
public:
	Q_INVOKABLE explicit AIPage(QWidget *parent);
	~AIPage();
};
