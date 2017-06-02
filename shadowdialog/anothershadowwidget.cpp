#include "anothershadowwidget.h"
#include "ui_anothershadowwidget.h"
#include <QPainter>
#include <qdrawutil.h>
#include <QtMath>

//const QMargins gShadowMargins(4,4,4,4);
//const QMargins gShadowMargins(10,10,10,10);

#define SHADOW_MARGIN_SIZE  10

const QMargins gShadowMargins(SHADOW_MARGIN_SIZE,SHADOW_MARGIN_SIZE,SHADOW_MARGIN_SIZE,SHADOW_MARGIN_SIZE);

AnotherShadowWidget::AnotherShadowWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnotherShadowWidget)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    this->setContentsMargins(gShadowMargins);

    ui->titlebarWidget->init(this, 40);
    ui->titlebarWidget->setTitleName("AnotherShadowWidget");
    ui->titlebarWidget->setParentWidgetResizable(true);
}

AnotherShadowWidget::~AnotherShadowWidget()
{
    delete ui;
}

void AnotherShadowWidget::paintEvent(QPaintEvent *event)
{
    //way 1
//    QWidget::paintEvent(event);

//    QPainter painter(this);
//    painter.fillRect(this->rect() - gShadowMargins,Qt::white);
//    qDrawBorderPixmap(&painter, this->rect(), gShadowMargins, QPixmap(":/shared/images/shadow.png"));

    //way 2
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(10, 10, this->width()-20, this->height()-20);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(path, QBrush(Qt::white));

    QColor color(0, 0, 0, 76);
    for(int i=0; i<10; i++)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRect(10-i, 10-i, this->width()-(10-i)*2, this->height()-(10-i)*2);
        //color.setAlpha(150 - qSqrt(i)*50);
        //color.setAlpha(18 - i*2);
        if(i==0)
            color.setAlpha(76);
        else
            color.setAlpha(9-i);

        painter.setPen(color);
        painter.drawPath(path);
    }
}
