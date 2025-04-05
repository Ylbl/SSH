#pragma once

#include <QObject>
#include "BasePage.h"
#include <ElaComboBox.h>
#include <ElaMultiSelectComboBox.h>
#include <ElaToggleButton.h>
#include <QLabel>
#include <QMutex>
#include <qthread.h>
#include <SFML/Audio/Music.hpp>

#include "opencv2/opencv.hpp"
#include "inference.h"
#include "qtimer.h"

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
	Inference* inf_cpu;
	QStringList* result_list;
	QStringList* comboList;
	QStringList* detectedObjects = new QStringList();
	sf::Music music;
	int rest_time = 0;
	int object_time=0;



	bool running;
	//std::atomic<bool> running{true};
	std::atomic<bool> is_play{false};
public:
	Q_INVOKABLE explicit AIPage(QWidget *parent);
	~AIPage();

	void init_camera();

	void init_ai_cpu();
	void run_ai_cpu();
	std::vector<Detection> process_cpu(cv::Mat* img);

	QImage matToQImage(const cv::Mat& mat);
	void resizeEvent(QResizeEvent* event);

	void check_rest_time();
	void check_object();
};
