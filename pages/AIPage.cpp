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
	ElaText* multiSelectComboBoxText = new ElaText("选择启用的模型", this);
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
		}
		if (tbnt_start->getIsToggled() == 1) {
			running = true;
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
	//10是随意写的一个数字，根据实际项目，最多可达到多少摄像头数目
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
	std::string projectBasePath = "C:/Users/O/source/repos/Program/SSH/out/build/release/models"; // Set your ultralytics base path

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

}
void AIPage::check_object()
{
	qDebug() << "2";

	std::atomic<bool> t_running(true);

	std::thread* t_send_email = new std::thread([&] {
		int i = 0;
		while (true) {
			if (!t_running.load()) {
				continue;
			}
			qDebug() << "1";
			if (i == 0 || !detectedObjects->contains("person")) {
				qDebug() << "s1";
				send_email();
				qDebug() << "s";
				break;
			}
			i--;
			//Sleep(1000);
		}
		});
	t_send_email->detach();
	
	while (running) {
		/*if (!detectedObjects->contains("person") || detectedObjects->contains("bottle")) {
			running = true;
		}
		else {
			running = false;
		}*/
		//running = true;
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}
//void Worker::run()
//{
//    while (true)
//    {
//        if (!running) {
//            break;
//        }
//        // 获取新的一帧;
//        Mat frame;
//        cap >> frame;
//        if (frame.empty())
//            return;
//
//        std::vector<Detection> output = inf->runInference(frame);
//
//        int detections = output.size();
//
//        for (int i = 0; i < detections; ++i)
//        {
//            Detection detection = output[i];
//
//            cv::Rect box = detection.box;
//            cv::Scalar color = detection.color;
//
//            // Detection box
//            cv::rectangle(frame, box, color, 2);
//
//            // Detection box text
//            std::string classString = detection.className + ' ' + std::to_string(detection.confidence).substr(0, 4);
//            cv::Size textSize = cv::getTextSize(classString, cv::FONT_HERSHEY_DUPLEX, 1, 2, 0);
//            cv::Rect textBox(box.x, box.y - 40, textSize.width + 10, textSize.height + 20);
//
//            cv::rectangle(frame, textBox, color, cv::FILLED);
//            cv::putText(frame, classString, cv::Point(box.x + 5, box.y - 10), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(0, 0, 0), 2, 0);
//        }
//        // Inference ends here...
//
//        // This is only for preview purposes
//        float scale = 0.8;
//        cv::resize(frame, frame, cv::Size(frame.cols * scale, frame.rows * scale));
//        cv::imshow("Inference", frame);
//        waitKey(10);
//    }
//}
//
//void Worker::init(QImage* _image_img, QStringList* _result_list, int* _crmera_index)
//{
//    image_img = _image_img;
//    result_list = _result_list;
//    crmera_index = _crmera_index;
//
//    if (cap.isOpened()) {
//        cap.release();
//    }
//
//    cap.open(*crmera_index);
//
//    std::string projectBasePath = "C:/Users/O/source/repos/Program/SSH/out/build/release/models"; // Set your ultralytics base path
//
//    bool runOnGPU = false;
//
//    inf=new Inference(projectBasePath + "/yolo11s.onnx", cv::Size(640, 640), projectBasePath + "/classes.txt", runOnGPU);
//}
// BottomWidget.cpp
//void AIPage::resizeEvent(QResizeEvent* event) {
//    QWidget::resizeEvent(event); // 必须调用父类实现[3](@ref)
//
//    // 动态计算label尺寸（示例：保持label为父容器的80%大小）
//    const float scale = 0.8f;
//    QSize newSize = event->size() * scale;
//
//    // 两种定位方式任选其一：
//
//    // 方式1：保持居中
//    label_img->setFixedSize(newSize);
//    label_img->move((width() - newSize.width()) / 2,
//        (height() - newSize.height()) / 2);
//
//    // 方式2：贴底边距10像素
//    // label->setFixedWidth(width() - 20);
//    // label->move(10, height() - label->height() - 10);
//
//    qDebug() << "Resized to:" << event->size(); // 调试输出[7](@ref)
//}
//void AIPage::run_ai()
//{
//    while(running)
//    {
//        Mat frame;
//        cap >> frame;
//        if (frame.empty())
//            return;
//
//        std::vector<Detection> output = inf->runInference(frame);
//
//        int detections = output.size();
//
//        for (int i = 0; i < detections; ++i)
//        {
//            Detection detection = output[i];
//
//            cv::Rect box = detection.box;
//            cv::Scalar color = detection.color;
//
//            // Detection box
//            cv::rectangle(frame, box, color, 2);
//
//            // Detection box text
//            std::string classString = detection.className + ' ' + std::to_string(detection.confidence).substr(0, 4);
//            cv::Size textSize = cv::getTextSize(classString, cv::FONT_HERSHEY_DUPLEX, 1, 2, 0);
//            cv::Rect textBox(box.x, box.y - 40, textSize.width + 10, textSize.height + 20);
//
//            cv::rectangle(frame, textBox, color, cv::FILLED);
//            cv::putText(frame, classString, cv::Point(box.x + 5, box.y - 10), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(0, 0, 0), 2, 0);
//        }
//        // Inference ends here...
//
//        // This is only for preview purposes
//        float scale = 1;
//        cv::resize(frame, frame, cv::Size(frame.cols * scale, frame.rows * scale));
//        //cv::imshow("Inference", frame);
//
//
//        cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
//        QImage img(frame.data,
//            frame.cols,
//            frame.rows,
//            frame.step,
//            QImage::Format_RGB888);
//
//        // 深拷贝图像数据
//        QPixmap pixmap = QPixmap::fromImage(img.copy());
//
//        label_img->setPixmap(pixmap);
//        waitKey(2);
//    }
//}
//void AIPage::run_ai()
//{
//    const int MODEL_INPUT_SIZE = 640;
//    float scale_ratio = 1.0f;
//    int pad_left = 0, pad_top = 0;
//
//    while (running)
//    {
//        Mat frame;
//        cap >> frame;
//        if (frame.empty()) break;
//
//        // 1. 保持比例的预处理
//        Mat processed;
//        int orig_w = frame.cols, orig_h = frame.rows;
//        scale_ratio = std::min(
//            MODEL_INPUT_SIZE / (float)orig_w,
//            MODEL_INPUT_SIZE / (float)orig_h
//        );
//        cv::resize(frame, processed, cv::Size(), scale_ratio, scale_ratio); // 等比例缩放
//
//        // 计算填充参数（网页3）
//        pad_left = (MODEL_INPUT_SIZE - processed.cols) / 2;
//        pad_top = (MODEL_INPUT_SIZE - processed.rows) / 2;
//        cv::copyMakeBorder(processed, processed, pad_top,
//            MODEL_INPUT_SIZE - processed.rows - pad_top,
//            pad_left, MODEL_INPUT_SIZE - processed.cols - pad_left,
//            BORDER_CONSTANT);
//
//        // 2. 执行推理
//        auto output = inf->runInference(processed);
//
//        // 3. 精准坐标映射（网页4）
//        for (auto& detection : output)
//        {
//            cv::Rect& box = detection.box;
//            // 显式转换为float类型并统一参数类型[2,3](@ref)
//            float x = (box.x - pad_left) / scale_ratio;
//            float y = (box.y - pad_top) / scale_ratio;
//            float w = box.width / scale_ratio;
//            float h = box.height / scale_ratio;
//
//            // 统一参数类型为float并添加epsilon防止溢出[6](@ref)
//            const float epsilon = 1e-6f;
//            box.x = std::clamp(x, 0.0f, static_cast<float>(orig_w - 1) - epsilon);
//            box.y = std::clamp(y, 0.0f, static_cast<float>(orig_h - 1) - epsilon);
//            box.width = std::clamp(w, epsilon, static_cast<float>(orig_w) - box.x - epsilon);
//            box.height = std::clamp(h, epsilon, static_cast<float>(orig_h) - box.y - epsilon);
//
//            // 绘制检测结果
//            cv::rectangle(frame, box, detection.color, 2);
//            std::string text = detection.className + " " + std::to_string(detection.confidence).substr(0, 4);
//            cv::putText(frame, text, cv::Point(box.x, box.y - 5),
//                FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 0), 1);
//        }
//
//        // 4. 线程安全显示（网页2、网页5）
//        QImage displayImg = matToQImage(frame).copy(); // 深拷贝避免资源竞争
//        QMetaObject::invokeMethod(label_img, [this, displayImg]() {
//            QPixmap pixmap = QPixmap::fromImage(displayImg);
//            // 动态适应窗口尺寸的缩放（网页7）
//            pixmap = pixmap.scaled(
//                label_img->size(),
//                Qt::KeepAspectRatio,  // 强制保持宽高比
//                Qt::SmoothTransformation // 平滑缩小处理
//            );
//            label_img->setPixmap(pixmap);
//            });
//
//        cv::waitKey(2);
//    }
//}