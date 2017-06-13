#include "calendarwidget.h"
#include "ui_calendarwidget.h"
#include <QMessageBox>

CalendarWidget::CalendarWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CalendarWidget)
{
    ui->setupUi(this);
    this->setObjectName("calendarWidget");

    QString styleSheet = QString("background-color:white;"
                                 "border-bottom-left-radius:3px;"
                                 "border-bottom-right-radius:3px;");

    this->setStyleSheet(styleSheet);
}

CalendarWidget::~CalendarWidget()
{
    delete ui;
}

void CalendarWidget::on_pushButton_clicked()
{
    this->parentWidget()->close();

    QMessageBox::information(NULL, QObject::tr("Information"), QObject::tr("lesson has been changed!"));
}
