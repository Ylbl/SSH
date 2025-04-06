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
#include "MyConfig.h"
#include "qboxlayout.h"
SettingPage::SettingPage(QWidget *parent)
	: BasePage(parent) {
	QWidget* centralWidget = new QWidget(this);
	//centralWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	centralWidget->setWindowTitle("设置");

	QFont font;
	font.setPointSize(15);

	rest_time = new ElaPlainTextEdit(QString::number(MyConfig::getInstance().rest_time));
	object_time = new ElaPlainTextEdit(QString::number(MyConfig::getInstance().object_time));
	my_email = new ElaPlainTextEdit(MyConfig::getInstance().my_email);
	key = new ElaPlainTextEdit(MyConfig::getInstance().key);
	to_email = new ElaPlainTextEdit(MyConfig::getInstance().to_email);
	models_path = new ElaPlainTextEdit(MyConfig::getInstance().models_path);
	music_path = new ElaPlainTextEdit(MyConfig::getInstance().music_path);
	target_object = new ElaPlainTextEdit(MyConfig::getInstance().target_object);
	confirm = new ElaPushButton("确认");

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
	models_path->setMaximumHeight(40);
	models_path->setFont(font);
	music_path->setMaximumHeight(40);
	music_path->setFont(font);
	target_object->setMaximumHeight(40);
	target_object->setFont(font);

	confirm->setMinimumHeight(40);
	confirm->setFont(font);

	connect(confirm, &ElaPushButton::clicked, this, [&]() {
		MyConfig::getInstance().rest_time=rest_time->toPlainText().toInt();
		MyConfig::getInstance().object_time=object_time->toPlainText().toInt();
		MyConfig::getInstance().my_email=my_email->toPlainText();
		MyConfig::getInstance().key=key->toPlainText();
		MyConfig::getInstance().to_email=to_email->toPlainText();
		MyConfig::getInstance().models_path=models_path->toPlainText();
		MyConfig::getInstance().music_path=music_path->toPlainText();
		MyConfig::getInstance().target_object=target_object->toPlainText();
		MyConfig::getInstance().mysave();
		//qDebug()<<MyConfig::getInstance().rest_time;
	});

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

	ElaScrollPageArea* setting_layout_area6 = new ElaScrollPageArea(this);
	QHBoxLayout* text_And_edit_layout6 = new QHBoxLayout(setting_layout_area6);
	text_And_edit_layout6->addWidget(new ElaText("模型路径"));
	text_And_edit_layout6->addStretch();
	text_And_edit_layout6->addWidget(models_path);

	ElaScrollPageArea* setting_layout_area7 = new ElaScrollPageArea(this);
	QHBoxLayout* text_And_edit_layout7 = new QHBoxLayout(setting_layout_area7);
	text_And_edit_layout7->addWidget(new ElaText("音乐路径"));
	text_And_edit_layout7->addStretch();
	text_And_edit_layout7->addWidget(music_path);

	ElaScrollPageArea* setting_layout_area8 = new ElaScrollPageArea(this);
	QHBoxLayout* text_And_edit_layout8 = new QHBoxLayout(setting_layout_area8);
	text_And_edit_layout8->addWidget(new ElaText("目标名称"));
	text_And_edit_layout8->addStretch();
	text_And_edit_layout8->addWidget(target_object);

	ElaScrollPageArea* setting_layout_area9 = new ElaScrollPageArea(this);
	QHBoxLayout* confirm_layout9 = new QHBoxLayout(setting_layout_area9);
	confirm_layout9->addWidget(confirm);


	QVBoxLayout* centerVLayout = new QVBoxLayout(centralWidget);
	//centerVLayout->setSpacing(0);
	//centerVLayout->setContentsMargins(0, 0, 0, 0);
	centerVLayout->addWidget(setting_layout_area1);
	centerVLayout->addWidget(setting_layout_area2);
	centerVLayout->addWidget(setting_layout_area3);
	centerVLayout->addWidget(setting_layout_area4);
	centerVLayout->addWidget(setting_layout_area5);
	centerVLayout->addWidget(setting_layout_area6);
	centerVLayout->addWidget(setting_layout_area7);
	centerVLayout->addWidget(setting_layout_area8);
	centerVLayout->addWidget(setting_layout_area9);
	centerVLayout->addStretch();
	this->addCentralWidget(centralWidget);
}

SettingPage::~SettingPage()
{}
