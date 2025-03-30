﻿#pragma once

#include <QtWidgets/QWidget>
#include "ElaWindow.h"
#include "AIPage.h"
#include "HomePage.h"
#include "WQBPage.h"

#include "SettingPage.h"

class AIPage;
class HomePage;
class WQBPage;
class AboutPage;
class SettingPage;

class MainWindow : public ElaWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initWindow();
    void initContent();

    AIPage* _AIPage{ nullptr };
    HomePage* _HomePage{ nullptr };
    WQBPage* _WQBPage{ nullptr };
    AboutPage* _AboutPage{ nullptr };
    SettingPage* _SettingPage{ nullptr };

    QString _settingKey{ "" };

};
