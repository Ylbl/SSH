#pragma once

#include <QObject>
#include "BasePage.h"

class ElaPushButton;

class UserInfoPage  : public BasePage
{
    Q_OBJECT
private:

public:
    Q_INVOKABLE explicit UserInfoPage(QWidget *parent);
    ~UserInfoPage();
};
