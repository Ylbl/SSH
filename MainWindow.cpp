#include "MainWindow.h"
#include <ElaMessageBar.h>
#include <ElaTheme.h>

MainWindow::MainWindow(QWidget *parent)
    : ElaWindow(parent)
{
    initWindow();
    initContent();
}

MainWindow::~MainWindow()
{}

void MainWindow::initWindow()
{
    //test1();
    // setIsEnableMica(true);
    // setIsCentralStackedWidgetTransparent(true);
    //setWindowIcon(QIcon(":/include/Image/Cirno.jpg"));
    resize(1200, 740);
    // ElaLog::getInstance()->initMessageLog(true);
    eTheme->setThemeMode(ElaThemeType::Dark);
    // setIsNavigationBarEnable(false);
    // setNavigationBarDisplayMode(ElaNavigationType::Compact);
    // setWindowButtonFlag(ElaAppBarType::MinimizeButtonHint, false);
    setUserInfoCardPixmap(QPixmap(":/Resource/OpenSource.png"));
    setUserInfoCardTitle("SSH");
    setUserInfoCardSubTitle("欢迎使用");
    setWindowTitle("主页");
    // setIsStayTop(true);
    // setUserInfoCardVisible(false);
}

void MainWindow::initContent()
{
    _AIPage = new AIPage(this);
    _HomePage = new HomePage(this);
    _WQBPage = new WQBPage(this);
    _SettingPage = new SettingPage(this);

    addPageNode("主页", _HomePage, ElaIconType::House);

    addPageNode("学习", _AIPage, ElaIconType::Bolt);

    addPageNode("错题本", _WQBPage, ElaIconType::Book);

    addFooterNode("设置", _SettingPage, _settingKey, 0, ElaIconType::GearComplex);

    //page.h 声明  page.cpp实现  此处连接
    connect(_HomePage, &HomePage::signal_go_to_AIPage, this, [=]() {
        this->navigation(_AIPage->property("ElaPageKey").toString());
        });
    connect(_HomePage, &HomePage::signal_go_to_WQBPage, this, [=]() {
        this->navigation(_WQBPage->property("ElaPageKey").toString());
        });
}

