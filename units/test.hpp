#pragma once
#include "opencv2/opencv.hpp"
#include <inference.h>
using namespace cv;
int test1() {
    std::string projectBasePath = "C:/Users/O/source/repos/Program/SSH/out/build/release/models"; // Set your ultralytics base path

    bool runOnGPU = false;

    Inference inf(projectBasePath + "/yolo11s.onnx", cv::Size(640, 640), projectBasePath+"classes.txt", runOnGPU);

    std::vector<std::string> imageNames;
    imageNames.push_back(projectBasePath + "/bus.jpg");
    imageNames.push_back(projectBasePath + "/zidane.jpg");


    // 1.创建视频采集对象;
    VideoCapture cap;

    // 2.打开默认相机;
    cap.open(0);

    // 3.判断相机是否打开成功;
    if (!cap.isOpened())
        return -1;

    for (;;)
    {
        // 获取新的一帧;
        Mat frame;
        cap >> frame;
        if (frame.empty())
            return 0;

        std::vector<Detection> output = inf.runInference(frame);

        int detections = output.size();

        for (int i = 0; i < detections; ++i)
        {
            Detection detection = output[i];

            cv::Rect box = detection.box;
            cv::Scalar color = detection.color;

            // Detection box
            cv::rectangle(frame, box, color, 2);

            // Detection box text
            std::string classString = detection.className + ' ' + std::to_string(detection.confidence).substr(0, 4);
            cv::Size textSize = cv::getTextSize(classString, cv::FONT_HERSHEY_DUPLEX, 1, 2, 0);
            cv::Rect textBox(box.x, box.y - 40, textSize.width + 10, textSize.height + 20);

            cv::rectangle(frame, textBox, color, cv::FILLED);
            cv::putText(frame, classString, cv::Point(box.x + 5, box.y - 10), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(0, 0, 0), 2, 0);
        }
        // Inference ends here...

        // This is only for preview purposes
        float scale = 0.8;
        cv::resize(frame, frame, cv::Size(frame.cols * scale, frame.rows * scale));
        cv::imshow("Inference", frame);
        waitKey(10);
    }

    return 0;
}