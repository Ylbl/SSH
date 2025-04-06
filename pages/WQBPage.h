#pragma once

#include <QObject>
#include "BasePage.h"

class ElaPushButton;

class WQBPage  : public BasePage
{
	Q_OBJECT
private:

public:
	Q_INVOKABLE explicit WQBPage(QWidget *parent);
	~WQBPage();
};
