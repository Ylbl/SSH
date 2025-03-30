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
    but = new ElaPushButton("测试按钮", this);

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("学习");

    QVBoxLayout* centerVLayout = new QVBoxLayout(centralWidget);
    centerVLayout->setSpacing(0);
    centerVLayout->setContentsMargins(0, 0, 0, 0);
    centerVLayout->addWidget(but);
    centerVLayout->addStretch();


    this->addCentralWidget(centralWidget);
}

AIPage::~AIPage()
{}
