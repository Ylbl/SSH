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
	: BasePage(parent) {
	QWidget* centralWidget = new QWidget(this);
	//centralWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	centralWidget->setWindowTitle("设置");

	QFont font;
	font.setPointSize(20);

	rest_time = new ElaPlainTextEdit();
	object_time = new ElaPlainTextEdit();
	my_email = new ElaPlainTextEdit();
	key = new ElaPlainTextEdit();
	to_email = new ElaPlainTextEdit();

	rest_time->setMaximumHeight(40);
	rest_time->setFont(font);
	object_time->setMaximumHeight(40);
	object_time->setFont(font);
	my_email->setMaximumHeight(40);
	my_email->setFont(font);
	key->setMaximumHeight(40);
	key->setFont(font);
	to_email->setMaximumHeight(40);
	to_email->setFont(font);

	ElaScrollPageArea* setting_layout_area1 = new ElaScrollPageArea(this);
	QHBoxLayout* text_And_edit_layout1 = new QHBoxLayout(setting_layout_area1);
	text_And_edit_layout1->addWidget(new ElaText("休息时间"));
	text_And_edit_layout1->addStretch();
	text_And_edit_layout1->addWidget(rest_time);

	ElaScrollPageArea* setting_layout_area2 = new ElaScrollPageArea(this);
	QHBoxLayout* text_And_edit_layout2 = new QHBoxLayout(setting_layout_area2);
	text_And_edit_layout2->addWidget(new ElaText("上报时间"));
	text_And_edit_layout2->addStretch();
	text_And_edit_layout2->addWidget(object_time);

	ElaScrollPageArea* setting_layout_area3 = new ElaScrollPageArea(this);
	QHBoxLayout* text_And_edit_layout3 = new QHBoxLayout(setting_layout_area3);
	text_And_edit_layout3->addWidget(new ElaText("本人邮箱"));
	text_And_edit_layout3->addStretch();
	text_And_edit_layout3->addWidget(my_email);

	ElaScrollPageArea* setting_layout_area4 = new ElaScrollPageArea(this);
	QHBoxLayout* text_And_edit_layout4 = new QHBoxLayout(setting_layout_area4);
	text_And_edit_layout4->addWidget(new ElaText("邮箱秘钥"));
	text_And_edit_layout4->addStretch();
	text_And_edit_layout4->addWidget(key);

	ElaScrollPageArea* setting_layout_area5 = new ElaScrollPageArea(this);
	QHBoxLayout* text_And_edit_layout5 = new QHBoxLayout(setting_layout_area5);
	text_And_edit_layout5->addWidget(new ElaText("目标邮箱"));
	text_And_edit_layout5->addStretch();
	text_And_edit_layout5->addWidget(to_email);




	QVBoxLayout* centerVLayout = new QVBoxLayout(centralWidget);
	//centerVLayout->setSpacing(0);
	//centerVLayout->setContentsMargins(0, 0, 0, 0);
	centerVLayout->addWidget(setting_layout_area1);
	centerVLayout->addWidget(setting_layout_area2);
	centerVLayout->addWidget(setting_layout_area3);
	centerVLayout->addWidget(setting_layout_area4);
	centerVLayout->addWidget(setting_layout_area5);
	centerVLayout->addStretch();
	this->addCentralWidget(centralWidget);
}

SettingPage::~SettingPage()
{}
