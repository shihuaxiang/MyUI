#include "mainwidget.h"
#include <QDebug>
#include <QLabel>
#include <QToolButton>
#include <QFileDialog>
#include "shadowdialog/stackeddialog.h"
#include "shadowdialog/simpledialog.h"
#include "shadowdialog/customdialog.h"
#include "shadowdialog/anothershadowwidget.h"
#include "diffsize/leftbar.h"
#include "shared/imagefactory.h"
#include "container/containerwidget.h"
#include "container/calendarwidget.h"
#include <QMainWindow>
#include <QVBoxLayout>
#include <QPainter>
#include <QSvgRenderer>
#include "diffsize/numberbutton.h"
#include "ImageOp.h"

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

//label using svg: high quality
void MainWidget::on_pushButton_1_1_clicked()
{
	qDebug() << __FUNCTION__;	

    QMainWindow * w = new QMainWindow();

    QLabel * label = new QLabel();
    QSize size(400, 400);
    label->setFixedSize(size);
	label->setPixmap(ImageOp::makeSvgPixmap(":/svgbutton/images/icq.svg", size));

    w->setCentralWidget(label);
	w->setStyleSheet("QMainWindow{background-color: white;}");

    w->show();
}

//label using svg in three ways: low quality or high quality
void MainWidget::on_pushButton_1_2_clicked()
{
    qDebug() << __FUNCTION__;

	QSize size(400, 400);

	QMainWindow * mainWindow = new QMainWindow();

	QWidget * w = new QWidget();
	QHBoxLayout * layout = new QHBoxLayout();

	for (int i = 0; i < 3; i++)
	{	
		QLabel * label = new QLabel();
		label->setFixedSize(size);

		if (i % 3 == 0)
		{
			//scale with loss quality
			QPixmap pixmap(":/svgbutton/images/icq.svg");
			label->setPixmap(pixmap.scaledToWidth(size.width()));
		}
		else if (i % 3 == 1)
		{
			//scale with loss quality
			label->setStyleSheet("border-image: url(:/svgbutton/images/icq.svg)");
		}
		else
		{
			//high quality
			QPixmap pixmap = ImageOp::makeSvgPixmap(":/svgbutton/images/icq.svg", size);
			label->setPixmap(pixmap);
		}
		

		layout->addWidget(label);
	}

	w->setLayout(layout);

	mainWindow->setCentralWidget(w);
	mainWindow->setStyleSheet("QMainWindow{background-color: #434555;}");
	mainWindow->show();
}

//IconButton derived from QPushButton use svg, high quality
void MainWidget::on_pushButton_1_3_clicked()
{
    qDebug() << __FUNCTION__;

	QSize size(400, 400);

	QMainWindow * mainWindow = new QMainWindow();

	QWidget * w = new QWidget();
	QHBoxLayout * layout = new QHBoxLayout();

	for (int i = 0; i < 2; i++)
	{
		IconButton * button = new IconButton(NULL);
		button->setObjectName("chatButton");
		button->setCheckable(true);
		button->setChecked(true);
		button->setAutoExclusive(true);
		button->setFixedSize(size);
		button->setIconSize(size);
		button->setNormalPixmap(":/svgbutton/images/contacts-normal.svg");
		button->setHoverPixmap(":/svgbutton/images/contacts-hover.svg");
		button->setCheckedPixmap(":/svgbutton/images/contacts-selected.svg");

		layout->addWidget(button);
	}

	w->setLayout(layout);

	mainWindow->setCentralWidget(w);
	mainWindow->setStyleSheet("QMainWindow{background-color: #434555;}");
	mainWindow->show();
}

//QPushButton or QToolButton using svg in two ways: low quality or high quality
void MainWidget::on_pushButton_1_4_clicked()
{
    qDebug() << __FUNCTION__;

	QSize size(300, 300);

	QMainWindow * mainWindow = new QMainWindow();

	QWidget * w = new QWidget();
	QHBoxLayout * layout = new QHBoxLayout();

	QIcon icon;
	//icon.addPixmap(QPixmap(":/svgbutton/images/copy.png"), QIcon::Normal, QIcon::Off);
	//icon.addPixmap(QPixmap(":/svgbutton/images/cut.png"), QIcon::Active, QIcon::Off);
	//icon.addPixmap(QPixmap(":/svgbutton/images/help.png"), QIcon::Disabled, QIcon::Off);
	//icon.addPixmap(QPixmap(":/svgbutton/images/about.png"), QIcon::Selected, QIcon::Off);
	//icon.addPixmap(QPixmap(":/svgbutton/images/paste.png"), QIcon::Normal, QIcon::On);
	//icon.addPixmap(QPixmap(":/svgbutton/images/redo.png"), QIcon::Active, QIcon::On);
	//icon.addPixmap(QPixmap(":/svgbutton/images/undo.png"), QIcon::Disabled, QIcon::On);
	//icon.addPixmap(QPixmap(":/svgbutton/images/settings.png"), QIcon::Selected, QIcon::On);

	icon.addPixmap(ImageOp::makeSvgPixmap(":/svgbutton/images/contacts-normal.svg", size), QIcon::Normal, QIcon::Off);
	icon.addPixmap(ImageOp::makeSvgPixmap(":/svgbutton/images/contacts-selected.svg", size), QIcon::Active, QIcon::Off);

	for (int i = 0; i < 2; i++)
	{
		QPushButton * button = new QPushButton();

		button->setFixedSize(size);
		button->setIconSize(size);

		if (i % 2 == 0)
		{
			//scale with loss quality
			button->setStyleSheet("QPushButton{border-image:url(:/svgbutton/images/contacts-normal.svg);}"
				"QPushButton:hover{border-image:url(:/svgbutton/images/contacts-hover.svg);}"
				"QPushButton:pressed{border-image:url(:/svgbutton/images/contacts-selected.svg);}");
		}
		else
		{
			//high quality
			button->setIcon(icon);
		}

		layout->addWidget(button);
	}

	for (int i = 0; i < 2; i++)
	{
		QToolButton * button = new QToolButton();

		button->setFixedSize(size);
		button->setIconSize(size);

		if (i % 2 == 0)
		{
			//scale with loss quality
			button->setStyleSheet("QToolButton{border-image:url(:/svgbutton/images/contacts-normal.svg);}"
				"QToolButton:hover{border-image:url(:/svgbutton/images/contacts-hover.svg);}"
				"QToolButton:pressed{border-image:url(:/svgbutton/images/contacts-selected.svg);}");
		}
		else
		{
			//high quality
			button->setIcon(icon);
		}

		layout->addWidget(button);
	}

	w->setLayout(layout);

	mainWindow->setCentralWidget(w);
	mainWindow->setStyleSheet("QMainWindow{background-color: #434555;}");
	mainWindow->show();
}

void MainWidget::on_pushButton_1_5_clicked()
{
	qDebug() << __FUNCTION__;
}

void MainWidget::on_pushButton_2_0_clicked()
{
	qDebug() << __FUNCTION__;
}

void MainWidget::on_pushButton_2_1_clicked()
{
	qDebug() << __FUNCTION__;
}

void MainWidget::on_pushButton_2_2_clicked()
{
	qDebug() << __FUNCTION__;
}

void MainWidget::on_pushButton_2_3_clicked()
{
	qDebug() << __FUNCTION__;
}

void MainWidget::on_pushButton_2_4_clicked()
{
	qDebug() << __FUNCTION__;
}

void MainWidget::on_pushButton_2_5_clicked()
{
	qDebug() << __FUNCTION__;
}
