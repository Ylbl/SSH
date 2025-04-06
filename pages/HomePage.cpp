#include "HomePage.h"

#include <QDebug>
#include <QDesktopServices>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QPainter>
#include <QVBoxLayout>

#include "ElaAcrylicUrlCard.h"
#include "ElaFlowLayout.h"
#include "ElaImageCard.h"
#include "ElaMenu.h"
#include "ElaMessageBar.h"
#include "ElaNavigationRouter.h"
#include "ElaPopularCard.h"
#include "ElaScrollArea.h"
#include "ElaText.h"
#include "ElaToolTip.h"
#include <ElaNavigationBar.h>
#include <ElaWindow.h>




HomePage::HomePage(QWidget *parent)
	: BasePage(parent)
{
    // 预览窗口标题
    setWindowTitle("Home");

    setTitleVisible(false);
    setContentsMargins(2, 2, 0, 0);
    // 标题卡片区域
    ElaText* desText = new ElaText("Student Studying Helper", this);
    desText->setTextPixelSize(18);
    ElaText* titleText = new ElaText("新型的学习工具", this);
    titleText->setTextPixelSize(35);

    QVBoxLayout* titleLayout = new QVBoxLayout();
    titleLayout->setContentsMargins(30, 60, 0, 0);
    titleLayout->addWidget(desText);
    titleLayout->addWidget(titleText);

    ElaImageCard* backgroundCard = new ElaImageCard(this);
    backgroundCard->setBorderRadius(10);
    backgroundCard->setFixedHeight(400);
    backgroundCard->setMaximumAspectRatio(1.7);
    backgroundCard->setCardImage(QImage(":/Resource/Image/Home_Background.png"));

    ElaAcrylicUrlCard* urlCard1 = new ElaAcrylicUrlCard(this);
    urlCard1->setCardPixmapSize(QSize(62, 62));
    urlCard1->setFixedSize(195, 225);
    urlCard1->setTitlePixelSize(17);
    urlCard1->setTitleSpacing(25);
    urlCard1->setSubTitleSpacing(13);
    urlCard1->setUrl("https://github.com/Ylbl/SSH");
    urlCard1->setCardPixmap(QPixmap(":/Resource/Image/github.png"));
    urlCard1->setTitle("开源地址");
    urlCard1->setSubTitle("SSH 遵守宽松的 MIT 开源协议");
    ElaToolTip* urlCard1ToolTip = new ElaToolTip(urlCard1);
    urlCard1ToolTip->setToolTip("https://github.com/Liniyous/ElaWidgetTools");

    ElaAcrylicUrlCard* urlCard2 = new ElaAcrylicUrlCard(this);
    urlCard2->setCardPixmapSize(QSize(62, 62));
    urlCard2->setFixedSize(195, 225);
    urlCard2->setTitlePixelSize(17);
    urlCard2->setTitleSpacing(25);
    urlCard2->setSubTitleSpacing(13);
    urlCard2->setUrl("https://qm.qq.com/cgi-bin/qm/qr?k=mlA6AvjkRdQrYiIqNxa1qlwFhPLz6Pfr");
    urlCard2->setCardPixmap(QPixmap(":/Resource/me.png"));
    urlCard2->setTitle("联系方式");
    urlCard2->setSubTitle("QQ:1278309552");

    ElaAcrylicUrlCard* urlCard3 = new ElaAcrylicUrlCard(this);
    urlCard3->setCardPixmapSize(QSize(62, 62));
    urlCard3->setFixedSize(195, 225);
    urlCard3->setTitlePixelSize(17);
    urlCard3->setTitleSpacing(25);
    urlCard3->setSubTitleSpacing(13);
    urlCard3->setUrl("https://space.bilibili.com/1548845715");
    urlCard3->setCardPixmap(QPixmap(":/Resource/b.png"));
    urlCard3->setTitle("个人频道");
    urlCard3->setSubTitle("其实没发过啥");

    ElaScrollArea* cardScrollArea = new ElaScrollArea(this);
    cardScrollArea->setWidgetResizable(true);
    cardScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    cardScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    cardScrollArea->setIsGrabGesture(true, 0);
    cardScrollArea->setIsOverShoot(Qt::Horizontal, true);
    QWidget* cardScrollAreaWidget = new QWidget(this);
    cardScrollAreaWidget->setStyleSheet("background-color:transparent;");
    cardScrollArea->setWidget(cardScrollAreaWidget);
    QHBoxLayout* urlCardLayout = new QHBoxLayout();
    urlCardLayout->setSpacing(15);
    urlCardLayout->setContentsMargins(30, 0, 0, 6);
    urlCardLayout->addWidget(urlCard1);
    urlCardLayout->addWidget(urlCard2);
    urlCardLayout->addWidget(urlCard3);
    urlCardLayout->addStretch();


    QVBoxLayout* cardScrollAreaWidgetLayout = new QVBoxLayout(cardScrollAreaWidget);
    cardScrollAreaWidgetLayout->setContentsMargins(0, 0, 0, 0);
    cardScrollAreaWidgetLayout->addStretch();
    cardScrollAreaWidgetLayout->addLayout(urlCardLayout);

    QVBoxLayout* backgroundLayout = new QVBoxLayout(backgroundCard);
    backgroundLayout->setContentsMargins(0, 0, 0, 0);
    backgroundLayout->addLayout(titleLayout);
    backgroundLayout->addWidget(cardScrollArea);

    // 推荐卡片
    ElaText* flowText = new ElaText("快速开始", this);
    flowText->setTextPixelSize(20);
    QHBoxLayout* flowTextLayout = new QHBoxLayout();
    flowTextLayout->setContentsMargins(33, 0, 0, 0);
    flowTextLayout->addWidget(flowText);

    // ElaFlowLayout
    ElaPopularCard* homeCard = new ElaPopularCard(this);
    connect(homeCard, &ElaPopularCard::popularCardButtonClicked, this, [=]() {Q_EMIT signal_go_to_AIPage();});
    homeCard->setCardPixmap(QPixmap(":/Resource/Image/control/IconElement.png"));
    homeCard->setTitle("开始学习");
    homeCard->setSubTitle("5.0⭐ 实用工具");
    homeCard->setInteractiveTips("免费使用");
    homeCard->setDetailedText("SSH致力于解决无人值守的学习监督问题");
    homeCard->setCardFloatPixmap(QPixmap(":/Resource/Image/IARC/IARC_3+.svg.png"));

    ElaPopularCard* homeCard1 = new ElaPopularCard(this);
    connect(homeCard1, &ElaPopularCard::popularCardButtonClicked, this, [=]() {  Q_EMIT signal_go_to_WQBPage();});
    homeCard1->setCardPixmap(QPixmap(":/Resource/Image/control/InputValidation.png"));
    homeCard1->setTitle("开始整理错题");
    homeCard1->setSubTitle("5.0⭐ 实用工具");
    homeCard1->setInteractiveTips("免费使用");
    homeCard1->setDetailedText("SSH致力于提供一站式学习服务");
    homeCard1->setCardFloatPixmap(QPixmap(":/Resource/Image/IARC/IARC_3+.svg.png"));

    ElaFlowLayout* flowLayout = new ElaFlowLayout(0, 5, 5);
    flowLayout->setContentsMargins(30, 0, 0, 0);
    flowLayout->setIsAnimation(true);
    flowLayout->addWidget(homeCard);
    flowLayout->addWidget(homeCard1);

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("Home");
    QVBoxLayout* centerVLayout = new QVBoxLayout(centralWidget);
    centerVLayout->setSpacing(0);
    centerVLayout->setContentsMargins(0, 0, 0, 0);
    centerVLayout->addWidget(backgroundCard);
    centerVLayout->addSpacing(20);
    centerVLayout->addLayout(flowTextLayout);
    centerVLayout->addSpacing(10);
    centerVLayout->addLayout(flowLayout);
    centerVLayout->addStretch();
    addCentralWidget(centralWidget);


    
    // 初始化提示
    ElaMessageBar::success(ElaMessageBarType::BottomRight, "Success", "初始化成功!", 2000);
    qDebug() << "初始化成功";
}

HomePage::~HomePage()
{}