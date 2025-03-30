#include "SettingPage.h"
#include "ElaLog.h"
#include "ElaRadioButton.h"
#include "ElaScrollPageArea.h"
#include "ElaText.h"
#include "ElaTheme.h"
#include "ElaToggleSwitch.h"
#include "ElaWindow.h"
#include "ElaLog.h"
#include "ElaRadioButton.h"
#include "ElaScrollPageArea.h"
#include "ElaText.h"
#include "ElaTheme.h"
#include "ElaToggleSwitch.h"
#include "ElaWindow.h"
#include "ElaPushButton.h"
#include "qboxlayout.h"
SettingPage::SettingPage(QWidget *parent)
	: BasePage(parent)
{
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("设置");

    QVBoxLayout* centerVLayout = new QVBoxLayout(centralWidget);
    centerVLayout->setSpacing(0);
    centerVLayout->setContentsMargins(0, 0, 0, 0);
    //centerVLayout->addWidget(but);
    centerVLayout->addStretch();


    this->addCentralWidget(centralWidget);
}

SettingPage::~SettingPage()
{}
