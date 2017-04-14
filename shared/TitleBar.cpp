#include "TitleBar.h"
#include <QHBoxLayout>
#include <QDebug>
#include "FramelessHelper.h"

TitleBar::TitleBar(QWidget *parent) : QWidget(parent)
{
    //this->setStyleSheet("background-color:#30BA78;color: #FF0000;");

    m_titleLabel = new QLabel(this);
    m_minButton = new QPushButton(this);
    m_closeButton = new QPushButton(this);

    m_titleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_titleLabel->setContentsMargins(10,0,0,0);
    m_titleLabel->setStyleSheet("background-color:#434555;font-size: 14px;color: #FFFFFF;");
//#30BA78 #434555
    m_titleLabel->setObjectName("titleLabel");
    m_minButton->setObjectName("minimizeButton");
    m_closeButton->setObjectName("closeButton");

    m_minButton->setToolTip(tr("Minimize"));
    m_closeButton->setToolTip(tr("Close"));

    m_minButton->setStyleSheet("QPushButton{border:none;padding-right:10px;image:url(:/shared/images/min_normal.png);background-color:#434555;}"
                             "QPushButton:hover{image:url(:/shared/images/min_hover.png)},"
                             "QPushButton:pressed{image:url(:/shared/images/min_hover.png)},");

    m_closeButton->setStyleSheet("QPushButton{border:none;padding-right:10px;image:url(:/shared/images/close_normal.png);background-color:#434555;}"
                             "QPushButton:hover{image:url(:/shared/images/close_hover.png)},"
                             "QPushButton:pressed{image:url(:/shared/images/close_hover.png)},");

    QHBoxLayout *pLayout = new QHBoxLayout(this);
    pLayout->addWidget(m_titleLabel);
    pLayout->addWidget(m_minButton);
    pLayout->addWidget(m_closeButton);
    pLayout->setSpacing(0);
    pLayout->setContentsMargins(0, 0, 0, 0);

    setLayout(pLayout);

    connect(m_minButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(m_closeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));

    m_pHelper = new FramelessHelper(parent);
    //m_pHelper->activateOn(parent);
    m_pHelper->setTopTitle(true, this->height());
    m_pHelper->setWidgetMovable(true);
    m_pHelper->setWidgetResizable(true);
    m_pHelper->setRubberBandOnMove(false);
    m_pHelper->setRubberBandOnResize(false);
}

void TitleBar::init(QWidget *buddyWidget, int titleHeight, int topMargin)
{
    if (topMargin == -1)
        topMargin = buddyWidget->contentsMargins().top();

    m_pHelper->activateOn(buddyWidget);

    this->setFixedHeight(titleHeight);

    m_minButton->setFixedHeight(this->height());
    m_closeButton->setFixedHeight(this->height());
    m_titleLabel->setFixedHeight(this->height());

    m_pHelper->setTopTitle(true, this->height() + topMargin);
}

void TitleBar::setMinButtonVisible(bool visible)
{
    //m_minButtonVisible = visible;
	m_minButton->setVisible(visible);
}

bool TitleBar::minButtonVisible()
{
    //return m_minButtonVisible;
	return m_minButton->isVisible();
}

void TitleBar::setParentWidgetResizable(bool b)
{
    m_pHelper->setWidgetResizable(b);
}

bool TitleBar::parentWidgetResizable()
{
    return m_pHelper->widgetResizable();
}

void TitleBar::setTitleName(QString name)
{
    m_titleLabel->setText(name);
}

QString TitleBar::titleName()
{
    return m_titleLabel->text();
}

void TitleBar::onClicked()
{
    QPushButton *pButton = qobject_cast<QPushButton *>(sender());
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
    {
        if (pButton == m_minButton)
        {
            pWindow->showMinimized();
        }
        else if (pButton == m_closeButton)
        {
            pWindow->close();
        }
    }
}
