#include "WQBPage.h"
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


WQBPage::WQBPage(QWidget *parent)
	: BasePage(parent)
{
    but = new ElaPushButton("测试按钮", this);

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("错题本");


    


    QVBoxLayout* centerVLayout = new QVBoxLayout(centralWidget);
    centerVLayout->setSpacing(0);
    centerVLayout->setContentsMargins(0, 0, 0, 0);
    //centerVLayout->addWidget(but);
    centerVLayout->addStretch();
    this->addCentralWidget(centralWidget);
}

WQBPage::~WQBPage()
{}
