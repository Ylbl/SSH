#pragma once

#include <QObject>
#include "BasePage.h"
#include <ElaComboBox.h>
#include <ElaMultiSelectComboBox.h>
#include <ElaToggleButton.h>
#include <QLabel>
#include <qthread.h>
#include "opencv2/opencv.hpp"
#include "inference.h"


class AIPage  : public BasePage
{
	Q_OBJECT
private:
	ElaComboBox* cbox_select_camera;
	ElaMultiSelectComboBox* mcbox_select_model;
	ElaToggleButton* tbnt_start;
	QLabel* label_img;
	QImage* image_img = new QImage();
	int crmera_index = 0;
	cv::VideoCapture cap;
	Inference* inf;
	QStringList* result_list;
	QStringList* comboList;

	bool running;
public:
	Q_INVOKABLE explicit AIPage(QWidget *parent);
	~AIPage();

	void init_camera();

	void init_ai();
	void run_ai();

	QImage matToQImage(const cv::Mat& mat);

protected:
	void resizeEvent(QResizeEvent* event);
};
