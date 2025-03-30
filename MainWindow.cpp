#include "MainWindow.h"
#include <ElaMessageBar.h>

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
    // setIsEnableMica(true);
    // setIsCentralStackedWidgetTransparent(true);
    //setWindowIcon(QIcon(":/include/Image/Cirno.jpg"));
    resize(1200, 740);
    // ElaLog::getInstance()->initMessageLog(true);
    // eTheme->setThemeMode(ElaThemeType::Dark);
    // setIsNavigationBarEnable(false);
    // setNavigationBarDisplayMode(ElaNavigationType::Compact);
    // setWindowButtonFlag(ElaAppBarType::MinimizeButtonHint, false);
    setUserInfoCardPixmap(QPixmap(":/Resource/me.png"));
    setUserInfoCardTitle("XiaoMing");
    setUserInfoCardSubTitle("oym700814@gmail.com");
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

    connect(_HomePage, &HomePage::test1, this, [=]() {
        ElaMessageBar::success(ElaMessageBarType::BottomRight, "Success", "初始化成功!", 2000);
        });
}

