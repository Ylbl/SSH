#pragma once

#include <QObject>
#include "BasePage.h"

class ElaPushButton;

class AIPage  : public BasePage
{
	Q_OBJECT
private:
	ElaPushButton* but;
public:
	Q_INVOKABLE explicit AIPage(QWidget *parent);
	~AIPage();
};
