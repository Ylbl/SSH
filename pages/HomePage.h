#pragma once

#include <QObject>
#include "BasePage.h"
class HomePage  : public BasePage
{
	Q_OBJECT

public:
	Q_INVOKABLE explicit HomePage(QWidget *parent);
    ~HomePage();

Q_SIGNALS:

    //Q_SIGNAL void test1();

	Q_SIGNAL void signal_go_to_AIPage();
	Q_SIGNAL void signal_go_to_WQBPage();
	Q_SIGNAL void signal_go_to_UserInfoPage();
};
