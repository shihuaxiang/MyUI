#include "mainwidget.h"
#include <QDebug>
#include <QLabel>
#include <QFileDialog>
#include "shadowdialog/stackeddialog.h"
#include "shadowdialog/simpledialog.h"
#include "shadowdialog/customdialog.h"
#include "shadowdialog/anothershadowwidget.h"
#include "diffsize/leftbar.h"
#include "shared/imagefactory.h"
#include "container/containerwidget.h"
#include "container/calendarwidget.h"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    QGridLayout * gridLayout = initGridLayout();
    this->setLayout(gridLayout);

    QMetaObject::connectSlotsByName(this);
}

QGridLayout * MainWidget::initGridLayout()
{
    QGridLayout * gridLayout = new QGridLayout(this);
    gridLayout->setSpacing(6);
    gridLayout->setContentsMargins(11, 11, 11, 11);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));

    int row = 6;
    int col = 6;

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            QPushButton * pushButton = new QPushButton(this);
            pushButton->setObjectName(QString("pushButton_%1_%2").arg(i).arg(j));
            pushButton->setText(QString("%1_%2").arg(i).arg(j));

            gridLayout->addWidget(pushButton, i, j, 1, 1);
        }
    }

    QLayoutItem *layoutItem = gridLayout->itemAtPosition(1,0);
    dynamic_cast<QPushButton *>(layoutItem->widget())->setText("ContainerWidget");

    return gridLayout;
}

void MainWidget::on_pushButton_0_0_clicked()
{
    qDebug() << __FUNCTION__;

    CustomDialog dlg;
    dlg.exec();
}

void MainWidget::on_pushButton_0_1_clicked()
{
    qDebug() << __FUNCTION__;

    SimpleDialog dlg(this);
    dlg.exec();
}

void MainWidget::on_pushButton_0_2_clicked()
{
    qDebug() << __FUNCTION__;

    StackedDialog dlg;
    dlg.exec();
}

void MainWidget::on_pushButton_0_3_clicked()
{
    qDebug() << __FUNCTION__;

    AnotherShadowWidget * w = new AnotherShadowWidget();
    w->show();
}

void MainWidget::on_pushButton_0_4_clicked()
{
    qDebug() << __FUNCTION__;

    if (m_pWidget != NULL)
    {
        m_pWidget->close();
    }

    m_pWidget = new LeftBar();
    m_pWidget->show();
}

void MainWidget::on_pushButton_0_5_clicked()
{
    qDebug() << __FUNCTION__;

    QString fileName = QFileDialog::getSaveFileName(this, "Save File", "", tr("PNG File(*.png);;All File(*.*)"));
    ImageFactory::createTransparentImage(10, 10, 1, fileName);

    qDebug() << fileName;
}

void MainWidget::on_pushButton_1_0_clicked()
{
    qDebug() << __FUNCTION__;

    ContainerWidget * w = new ContainerWidget(new CalendarWidget(), "Calendar");
    w->resize(560,500);
    w->show();

}
void MainWidget::on_pushButton_1_1_clicked()
{
    qDebug() << __FUNCTION__;

}
void MainWidget::on_pushButton_1_2_clicked()
{
    qDebug() << __FUNCTION__;

}
void MainWidget::on_pushButton_1_3_clicked()
{
    qDebug() << __FUNCTION__;

}
void MainWidget::on_pushButton_1_4_clicked()
{
    qDebug() << __FUNCTION__;

}
void MainWidget::on_pushButton_1_5_clicked()
{
    qDebug() << __FUNCTION__;

}
