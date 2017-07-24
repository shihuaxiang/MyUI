//
// create dialog with shadow margin in designer
// 1 create a QWidget
// 2 set background-color to white for the QWidget
// 3 dialog is covered with the QWidget in a verticalLayout
//


#include "simpledialog.h"
#include "ui_simpledialog.h"
#include "../shared/TitleBar.h"
#include <QFile>
#include <QGraphicsDropShadowEffect>
#include <QCalendarWidget>
#include <QStyledItemDelegate>

#define SHADOW_MARGIN_SIZE (10)

SimpleDialog::SimpleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SimpleDialog)
{
    ui->setupUi(this);

    QFile qss(":/shadowdialog/images/simpledialog.qss");
    qss.open(QFile::ReadOnly);
    setStyleSheet(qss.readAll());
    qss.close();

    QStyledItemDelegate *delegate = new QStyledItemDelegate(this);
    ui->comboBox->setItemDelegate(delegate);

    initMainLayout();
}

SimpleDialog::~SimpleDialog()
{
    delete ui;
}

void SimpleDialog::initMainLayout()
{
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    TitleBar * titlebarWidget = initTitlebar();
    ui->verticalLayout->insertWidget(0, titlebarWidget);

    ui->verticalLayout->setContentsMargins(SHADOW_MARGIN_SIZE, SHADOW_MARGIN_SIZE, SHADOW_MARGIN_SIZE, SHADOW_MARGIN_SIZE);
    ui->verticalLayout->setSpacing(0);

    //ui->widget->setStyleSheet("#widget{background-color:rgba(255,255,255,255)}");

    QCalendarWidget *calendarWidget=new QCalendarWidget;
    calendarWidget->setObjectName("calendarWidget");
    calendarWidget->setFixedSize(260, 32);
    calendarWidget->setGridVisible(false);
    calendarWidget->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    calendarWidget->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
    calendarWidget->setHorizontalHeaderFormat(QCalendarWidget::ShortDayNames);

    ui->dateEdit->setFixedSize(260,32);
    ui->dateEdit->setCalendarPopup(true);
    ui->dateEdit->setCalendarWidget(calendarWidget);
    ui->dateEdit->setDisplayFormat("yyyy-MM-dd");

    QGraphicsDropShadowEffect *pShadow = new QGraphicsDropShadowEffect();
    pShadow->setOffset(0, 1);
    pShadow->setColor(QColor(0, 0, 0, 76));
    pShadow->setBlurRadius(SHADOW_MARGIN_SIZE);
    this->setGraphicsEffect(pShadow);
}

TitleBar * SimpleDialog::initTitlebar()
{
    int titlebarHeight = 40;

    TitleBar * titlebarWidget = new TitleBar(this);
    titlebarWidget->setObjectName(QStringLiteral("titlebarWidget"));
    QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(titlebarWidget->sizePolicy().hasHeightForWidth());
    titlebarWidget->setSizePolicy(sizePolicy1);
    titlebarWidget->setFixedHeight(titlebarHeight);
    titlebarWidget->setStyleSheet(QStringLiteral("#titlebarWidget {background-color: #434555;}"));
    titlebarWidget->init(this, titlebarHeight, SHADOW_MARGIN_SIZE);
    titlebarWidget->setTitleName(tr("SimpleDialog"));
    titlebarWidget->setMinButtonVisible(false);
    titlebarWidget->setParentWidgetResizable(false);

    return titlebarWidget;
}
