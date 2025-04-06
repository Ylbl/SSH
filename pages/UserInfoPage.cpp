#include "UserInfoPage.h"
#include "ElaLog.h"
#include "ElaRadioButton.h"
#include "ElaScrollPageArea.h"
#include "ElaText.h"
#include "ElaTheme.h"
#include "ElaToggleSwitch.h"
#include "ElaWindow.h"
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
#include "ElaPushButton.h"


UserInfoPage::UserInfoPage(QWidget *parent)
    : BasePage(parent)
{
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("个人数据");

    QFont font;
    font.setPointSize(30);

    QWidget* text=new ElaText("敬请期待");
    //text->setFont(font);

    ElaScrollPageArea* text_area = new ElaScrollPageArea(this);
    QHBoxLayout* text_And_edit_layout1 = new QHBoxLayout(text_area);
    text_And_edit_layout1->addWidget(text);
    text_And_edit_layout1->addStretch();



    QVBoxLayout* centerVLayout = new QVBoxLayout(centralWidget);
    centerVLayout->setSpacing(0);
    centerVLayout->setContentsMargins(0, 0, 0, 0);
    centerVLayout->addWidget(text_area);
    centerVLayout->addStretch();
    this->addCentralWidget(centralWidget);
}

UserInfoPage::~UserInfoPage()
{}
