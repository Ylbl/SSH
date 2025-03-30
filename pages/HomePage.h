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

    Q_SIGNAL void test1();
    Q_SIGNAL void elaScreenNavigation();
    Q_SIGNAL void elaBaseComponentNavigation();
    Q_SIGNAL void elaSceneNavigation();
    Q_SIGNAL void elaCardNavigation();
    Q_SIGNAL void elaIconNavigation();
};
