#pragma once

#include <ElaPushButton.h>
#include <QObject>
#include "BasePage.h"
#include "ElaPlainTextEdit.h"

class SettingPage  : public BasePage 
{
	Q_OBJECT
private:
	ElaPlainTextEdit * rest_time;
	ElaPlainTextEdit * object_time;
	ElaPlainTextEdit * my_email;
	ElaPlainTextEdit * key;
	ElaPlainTextEdit * to_email;
	ElaPlainTextEdit * models_path;
	ElaPlainTextEdit * music_path;
	ElaPushButton * confirm;
	ElaPlainTextEdit * target_object;
public:
	Q_INVOKABLE explicit SettingPage(QWidget *parent);
	~SettingPage();
};
