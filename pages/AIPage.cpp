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
using namespace cv;
AIPage::AIPage(QWidget *parent)
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
    QStringList multiComboList{ "yolo11n","yolo11s"};
    QStringList multiSelectComboList{ "yolo11n"};
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
    connect(tbnt_start,&ElaToggleButton::toggled,[=](){
        //ElaMessageBar::success(ElaMessageBarType::BottomRight, "Success", QString::number(tbnt_start->getIsToggled()), 2000);
        //crmera_index = QString::number((cbox_select_camera->currentText()));
        crmera_index = cbox_select_camera->currentText().toInt();
        //ElaMessageBar::success(ElaMessageBarType::BottomRight, "Success", QString::number(crmera_index), 2000);

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
    centerVLayout->addWidget(img_area,1);//铺满
    //centerVLayout->addStretch();
    
    this->addCentralWidget(centralWidget);
}

AIPage::~AIPage()
{}

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
