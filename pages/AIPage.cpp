﻿
#include "AIPage.h"
#include "SettingPage.h"
#include "ElaLog.h"
#include "ElaRadioButton.h"
#include "ElaScrollPageArea.h"
#include "ElaText.h"
#include "ElaTheme.h"
#include "ElaToggleSwitch.h"
#include "ElaWindow.h"
#include "ElaPushButton.h"
#include "qboxlayout.h"
#include "opencv2/opencv.hpp"
#include <ElaMessageBar.h>
#include <inference.h>
#include <thread>
#include <algorithm>
#include <QResizeEvent>
#include "send_email.hpp"

using namespace cv;
AIPage::AIPage(QWidget* parent)
	: BasePage(parent)
{
	if (!music.openFromFile(MyConfig::getInstance().music_path.toStdString()))
		qDebug()<<"error";
#pragma region 配置栏
#pragma region 选择框
	comboList = new QStringList();
	cbox_select_camera = new ElaComboBox(this);
	init_camera();
	cbox_select_camera->addItems(*comboList);
	QHBoxLayout* comboBoxLayout = new QHBoxLayout();
	ElaText* comboBoxText = new ElaText("选择摄像头", this);

	comboBoxText->setTextPixelSize(15);
	comboBoxLayout->addWidget(comboBoxText);
	comboBoxLayout->addWidget(cbox_select_camera);
#pragma endregion

#pragma region 选择框
	mcbox_select_model = new ElaMultiSelectComboBox(this);
	mcbox_select_model->setMinimumWidth(250);
	QStringList multiComboList{ "yolo11n","yolo11s" };
	QStringList multiSelectComboList{ "yolo11n" };
	mcbox_select_model->addItems(multiComboList);
	mcbox_select_model->setCurrentSelection(multiSelectComboList);
	mcbox_select_model->setDisabled(true);
	QHBoxLayout* multiSelectComboBoxLayout = new QHBoxLayout();
	ElaText* multiSelectComboBoxText = new ElaText("选择模型(暂不启用)", this);
	multiSelectComboBoxText->setTextPixelSize(15);
	multiSelectComboBoxLayout->addWidget(multiSelectComboBoxText);
	multiSelectComboBoxLayout->addWidget(mcbox_select_model);
#pragma endregion

#pragma region 开始按钮
	tbnt_start = new ElaToggleButton("开始", this);
	connect(tbnt_start, &ElaToggleButton::toggled, [=]() {
		//ElaMessageBar::success(ElaMessageBarType::BottomRight, "Success", QString::number(tbnt_start->getIsToggled()), 2000);
		if (tbnt_start->getIsToggled() == 0) {
			running = false;

			std::thread t_send_email([=] {
				send_email("提示","摄像头关闭");
			});
			t_send_email.detach();
		}
		if (tbnt_start->getIsToggled() == 1) {
			running = true;

			std::thread t_send_email([=] {
				send_email("提示","摄像头开启");
			});
			t_send_email.detach();

			init_ai_cpu();

			std::thread t_run_ai_cpu(&AIPage::run_ai_cpu, this);
			t_run_ai_cpu.detach();

			std::thread t_check_rest_time(&AIPage::check_rest_time, this);
			t_check_rest_time.detach();

			std::thread t_check_object(&AIPage::check_object, this);
			t_check_object.detach();
		}
		});
	tbnt_start->setFixedWidth(120);
	QHBoxLayout* toggleButtonLayout = new QHBoxLayout();
	toggleButtonLayout->addWidget(tbnt_start);
#pragma endregion

	ElaScrollPageArea* config_column_area = new ElaScrollPageArea(this);
	QHBoxLayout* config_column = new QHBoxLayout(config_column_area);

	config_column_area->setFixedHeight(60);
	config_column->addLayout(comboBoxLayout);
	config_column->addLayout(multiSelectComboBoxLayout);
	toggleButtonLayout->setContentsMargins(15, 0, 0, 0);
	config_column->addLayout(toggleButtonLayout);
	config_column->addStretch(1);
#pragma endregion

#pragma region 图像栏
	label_img = new QLabel("画面将在此处呈现", this);//定义
	label_img->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);//设置铺满
	label_img->setAlignment(Qt::AlignCenter);//设置居中

	QHBoxLayout* imgLayout = new QHBoxLayout();
	imgLayout->addWidget(label_img);


	QWidget* img_area = new QWidget(this);
	img_area->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	QVBoxLayout* img_column = new QVBoxLayout(img_area);
	img_column->addLayout(imgLayout);
#pragma endregion


	QWidget* centralWidget = new QWidget(this);
	centralWidget->setWindowTitle("学习");
	QVBoxLayout* centerVLayout = new QVBoxLayout(centralWidget);
	centerVLayout->setSpacing(5);
	//centerVLayout->setContentsMargins(0, 0, 0, 0);
	centerVLayout->addWidget(config_column_area);
	centerVLayout->addWidget(img_area, 1);//铺满
	//centerVLayout->addStretch();

	this->addCentralWidget(centralWidget);
}

AIPage::~AIPage()
{
}

void AIPage::init_camera()
{
	int i = 0;
	VideoCapture cap;
	for (i = 0; i < 10; i++)
	{
		cap.open(i);
		if (!cap.isOpened()) {
			return;
		}
		comboList->append(QString::number(i));
		cap.release();
	}
}

#pragma region cpu推理
void AIPage::init_ai_cpu()
{
	if (!cap.isOpened())
		cap.release();
	std::string projectBasePath = MyConfig::getInstance().models_path.toStdString(); // Set your ultralytics base path

	bool runOnGPU = false;

	inf_cpu = new Inference(projectBasePath + "/yolo11s.onnx", cv::Size(640, 640), projectBasePath + "classes.txt", runOnGPU);

	crmera_index = cbox_select_camera->currentText().toInt();

	cap.open(crmera_index);
}
void AIPage::run_ai_cpu()
{
	const int MODEL_INPUT_SIZE = 640;
	float scale_ratio = 1.0f;
	int pad_left = 0, pad_top = 0;

	while (running)
	{
		Mat frame;
		cap >> frame;
		if (frame.empty()) break;

		// 1. 预处理阶段（保持原始图像比例）
		Mat processed;
		int orig_w = frame.cols, orig_h = frame.rows;
		scale_ratio = std::min(MODEL_INPUT_SIZE / (float)orig_w, MODEL_INPUT_SIZE / (float)orig_h);
		cv::resize(frame, processed, cv::Size(orig_w * scale_ratio, orig_h * scale_ratio));

		// 计算填充参数
		pad_left = (MODEL_INPUT_SIZE - processed.cols) / 2;
		pad_top = (MODEL_INPUT_SIZE - processed.rows) / 2;
		cv::copyMakeBorder(processed, processed, pad_top, MODEL_INPUT_SIZE - processed.rows - pad_top,
			pad_left, MODEL_INPUT_SIZE - processed.cols - pad_left, BORDER_CONSTANT);

		// 2. 执行推理
		//auto output = inf_cpu->runInference(processed);
		std::vector<Detection> output = process_cpu(&processed);


		if (!detectedObjects->isEmpty()) {
			detectedObjects->clear();
		}

		// 3. 坐标转换（映射到原始图像坐标系）
		for (auto& detection : output)
		{
			detectedObjects->append(QString::fromStdString(detection.className));

			//qDebug()<< *detectedObjects;

			cv::Rect& box = detection.box;
			box.x = (box.x - pad_left) / scale_ratio;
			box.y = (box.y - pad_top) / scale_ratio;
			box.width /= scale_ratio;
			box.height /= scale_ratio;

			// 限制坐标范围
			box.x = std::clamp(box.x, 0, orig_w - 1);
			box.y = std::clamp(box.y, 0, orig_h - 1);
			box.width = std::min(box.width, orig_w - box.x);
			box.height = std::min(box.height, orig_h - box.y);

			// 绘制检测结果
			cv::rectangle(frame, box, detection.color, 2);
			std::string text = detection.className + " " + std::to_string(detection.confidence).substr(0, 4);
			cv::putText(frame, text, cv::Point(box.x, box.y - 5),
				FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 0), 1);
			cv::putText(frame, "rest_time: "+std::to_string(rest_time), cv::Point(0, 30),
				FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,0,255), 1);
			cv::putText(frame, "object_time: "+std::to_string(object_time), cv::Point(0, 60),
				FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,0,255), 1);
		}

		// 4. 线程安全的图像显示
		QImage img = matToQImage(frame).scaled(
			label_img->size(),
			Qt::KeepAspectRatio,
			Qt::SmoothTransformation
		);

		QMetaObject::invokeMethod(label_img, [this, img]() {
			// 使用深拷贝避免资源竞争[8](@ref)
			QPixmap pixmap = QPixmap::fromImage(img.copy());
			label_img->setPixmap(pixmap);
			});

		//delete detectedObjects;
		cv::waitKey(2);

	}
	label_img->setText(" ");

}
std::vector<Detection> AIPage::process_cpu(cv::Mat* img)
{
	return inf_cpu->runInference(*img);
}
#pragma endregion

QImage AIPage::matToQImage(const cv::Mat& mat) {
	if (mat.type() == CV_8UC3) {
		cv::Mat rgb;
		cv::cvtColor(mat, rgb, cv::COLOR_BGR2RGB);
		return QImage(rgb.data, rgb.cols, rgb.rows,
			static_cast<int>(rgb.step),
			QImage::Format_RGB888).copy();
	}
	return QImage();
}

void AIPage::resizeEvent(QResizeEvent* event)
{
	QPixmap px = QPixmap::fromImage(*image_img).scaled(event->size());
	label_img->setPixmap(px);
	label_img->resize(event->size());
	QWidget::resizeEvent(event);
}

void AIPage::check_rest_time()
{
	int i=MyConfig::getInstance().rest_time;
	while (running) {
		rest_time=i;
		if (i==0) {
			i=MyConfig::getInstance().rest_time;

			if (music.getStatus()==sf::SoundSource::Status::Playing&&running) {
				//continue;
			}else {
				music.play();
			}
		}
		i--;
		Sleep(1000);
	}
	if (music.getStatus()==sf::SoundSource::Status::Playing) {
		music.stop();
	}
}
void AIPage::check_object() {
	std::atomic<bool> t_is_send(true);

	int i = MyConfig::getInstance().object_time;
	std::thread *t_send_email = new std::thread([&] {
		while (running) {
			object_time=i;
			//qDebug() << "object_time: " << object_time;
			if (!t_is_send.load()) {
				i=MyConfig::getInstance().object_time;
				//continue;
			}
			if (i == 0 && t_is_send.load()) {
				send_email("tip","检测到可疑物体");
				i = MyConfig::getInstance().object_time;
				//continue;
			}
			i--;
			Sleep(1000);
		}
	});
	t_send_email->detach();

	while (running) {
		if (!detectedObjects->contains("person") || detectedObjects->contains(MyConfig::getInstance().target_object)) {
			t_is_send.store(true);
		} else {
			t_is_send.store(false);
		}
	}
}
