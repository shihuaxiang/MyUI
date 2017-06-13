#include "containerwidget.h"
#include <QDebug>
#include <QPainter>
#include <qdrawutil.h>

#define BORDER_RADIUS   3

#define SHADOW_MARGIN_SIZE  4

const QMargins gShadowMargins(SHADOW_MARGIN_SIZE,SHADOW_MARGIN_SIZE,SHADOW_MARGIN_SIZE,SHADOW_MARGIN_SIZE);

DarkTitlebar::DarkTitlebar( QWidget* parent )
    : QWidget(parent)
{
    qDebug() << __FUNCTION__ << this;
    this->setObjectName("darkTitlebar");

    m_titleLabel = new QLabel(parent->windowTitle());
    m_minButton = new QPushButton();
    m_closeButton = new QPushButton();

    m_titleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_titleLabel->setContentsMargins(10,0,0,0);

    m_titleLabel->setStyleSheet(QString("background-color:#434555;font-size: 14px;color: #FFFFFF;border-top-left-radius:%1px;").arg(BORDER_RADIUS));
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

    m_minButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_closeButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QHBoxLayout* layout = new QHBoxLayout( this );
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    layout->addWidget(m_titleLabel, 1);
    layout->addWidget(m_minButton);
    layout->addWidget(m_closeButton);

    QWidget * rightWidget = new QWidget();
    rightWidget->setFixedWidth(BORDER_RADIUS);
    rightWidget->setStyleSheet(QString("background-color:#434555;border-top-right-radius:%1px;").arg(BORDER_RADIUS));

    layout->addWidget(rightWidget);

    this->setFixedHeight(40);

    connect(m_closeButton, SIGNAL(clicked()), this, SIGNAL(closeParent()));
}

DarkTitlebar::~DarkTitlebar()
{
    qDebug() << __FUNCTION__ << this;
}

void DarkTitlebar::mousePressEvent(QMouseEvent* e)
{
    this->pressPoint = e->pos();
    this->isMoving = true;

    QWidget::mousePressEvent(e);
}

void DarkTitlebar::mouseMoveEvent(QMouseEvent* e)
{
    if((e->buttons() == Qt::LeftButton) && this->isMoving)
    {
        int dx = e->x() - this->pressPoint.x();
        int dy = e->y() - this->pressPoint.y();

        //emit moving(dx,dy);

        QPoint point = parentWidget()->pos();
        point.setX(point.x() + dx);
        point.setY(point.y() + dy);
        parentWidget()->move(point);
    }

    QWidget::mouseMoveEvent(e);
}

void DarkTitlebar::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->isMoving)
    {
        this->isMoving = false;
    }

    QWidget::mouseReleaseEvent(e);
}

ContainerWidget::ContainerWidget(QWidget* contentWidget, const QString & title, QWidget *parent)
    : QWidget(parent)
{
    qDebug() << __FUNCTION__ << this;

    this->setWindowTitle(title);
    this->setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setContentsMargins(gShadowMargins);

    //this->setAttribute(Qt::WA_DeleteOnClose, true);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);

    this->titlebar = new DarkTitlebar(this);
    layout->addWidget(this->titlebar);

    connect(titlebar, SIGNAL(closeParent()), this, SLOT(close()));

    this->contentWidget = contentWidget;
    //this->contentWidget->setObjectName("contentWidget");
    layout->addWidget(this->contentWidget);
}

ContainerWidget::~ContainerWidget()
{
    qDebug() << __FUNCTION__ << this;
}

void ContainerWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.fillRect(this->rect() - gShadowMargins,Qt::white);
    qDrawBorderPixmap(&painter, this->rect(), gShadowMargins, QPixmap(":/shared/images/shadow.png"));
}
