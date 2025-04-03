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
AIPage::AIPage(QWidget *parent)
	: BasePage(parent)
{
#pragma region 配置栏
#pragma region 选择框
    cbox_select_camera = new ElaComboBox(this);
    QStringList comboList{ };
    cbox_select_camera->addItems(comboList);
    QHBoxLayout* comboBoxLayout = new QHBoxLayout();
    ElaText* comboBoxText = new ElaText("选择摄像头", this);
    comboBoxText->setTextPixelSize(15);
    comboBoxLayout->addWidget(comboBoxText);
    comboBoxLayout->addWidget(cbox_select_camera);
#pragma endregion

#pragma region 选择框
    mcbox_select_model = new ElaMultiSelectComboBox(this);
    mcbox_select_model->setMinimumWidth(250);
    QStringList multiComboList{ "Medieapipe","YOLO"};
    QStringList multiSelectComboList{ };
    mcbox_select_model->addItems(multiComboList);
    mcbox_select_model->setCurrentSelection(multiSelectComboList);
    QHBoxLayout* multiSelectComboBoxLayout = new QHBoxLayout();
    ElaText* multiSelectComboBoxText = new ElaText("选择启用的模型", this);
    multiSelectComboBoxText->setTextPixelSize(15);
    multiSelectComboBoxLayout->addWidget(multiSelectComboBoxText);
    multiSelectComboBoxLayout->addWidget(mcbox_select_model);
#pragma endregion

#pragma region 开始按钮
    tbnt_start = new ElaToggleButton("开始", this);
    tbnt_start->setFixedWidth(120);
    QHBoxLayout* toggleButtonLayout = new QHBoxLayout();
    toggleButtonLayout->addWidget(tbnt_start);
#pragma endregion

    ElaScrollPageArea* config_column_area = new ElaScrollPageArea(this);
    QHBoxLayout* config_column = new QHBoxLayout(config_column_area);
    config_column->addLayout(comboBoxLayout);
    config_column->addLayout(multiSelectComboBoxLayout);
    toggleButtonLayout->setContentsMargins(15, 0, 0, 0);
    config_column->addLayout(toggleButtonLayout);
    config_column->addStretch(1);
#pragma endregion



    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("学习");
    QVBoxLayout* centerVLayout = new QVBoxLayout(centralWidget);
    centerVLayout->setSpacing(0);
    centerVLayout->setContentsMargins(0, 0, 0, 0);
    centerVLayout->addWidget(config_column_area);
    centerVLayout->addStretch();
    this->addCentralWidget(centralWidget);
}

AIPage::~AIPage()
{}
