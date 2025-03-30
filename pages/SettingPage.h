#pragma once

#include <QObject>
#include "BasePage.h"


class SettingPage  : public BasePage 
{
	Q_OBJECT

public:
	Q_INVOKABLE explicit SettingPage(QWidget *parent);
	~SettingPage();
};
