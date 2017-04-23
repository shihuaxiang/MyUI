#include "anothershadowwidget.h"
#include "ui_anothershadowwidget.h"
#include <QPainter>
#include <qdrawutil.h>

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
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.fillRect(this->rect() - gShadowMargins,Qt::white);
    qDrawBorderPixmap(&painter, this->rect(), gShadowMargins, QPixmap(":/shared/images/shadow.png"));
}
