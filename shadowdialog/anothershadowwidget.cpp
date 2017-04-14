#include "anothershadowwidget.h"
#include "ui_anothershadowwidget.h"
#include <QPainter>
#include <qdrawutil.h>

const QMargins gShadowMargins(4,4,4,4);

AnotherShadowWidget::AnotherShadowWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnotherShadowWidget)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
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
    qDrawBorderPixmap(&painter, this->rect(), gShadowMargins, QPixmap(":/shared/images/shadow.png"));
}
