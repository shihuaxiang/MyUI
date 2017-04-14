//
// create dialog with shadow margin out of designer
//

#include "customdialog.h"
#include "ui_customdialog.h"
#include <QVBoxLayout>
#include "../shared/TitleBar.h"
#include "../shared/QCustomLineEdit.h"
#include <QGraphicsDropShadowEffect>
#include <QFile>

#define SHADOW_MARGIN_SIZE (10)

CustomDialog::CustomDialog(QWidget *parent)
    : QDialog(parent)
    , centralWidget(new QWidget(this))
    , buttonBox(new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this))
{
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    this->setObjectName("customDialog");
    centralWidget->setObjectName("centralWidget");
    centralWidget->setFixedSize(300,300);
    //centralWidget->setStyleSheet("QWidget #centralWidget {background-color: rgba(255,255,255,255);};");

    QFile qss(":/shadowdialog/images/customdialog.qss");
    qss.open(QFile::ReadOnly);
    setStyleSheet(qss.readAll());
    qss.close();

    initMainLayout();
}

CustomDialog::~CustomDialog()
{
}

void CustomDialog::initMainLayout()
{
    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->setContentsMargins(24, 0, 24, 0);
    vLayout->setSpacing(0);
    vLayout->addLayout(initAccountRegion());
    vLayout->addSpacerItem(new QSpacerItem(0, 21, QSizePolicy::Expanding, QSizePolicy::MinimumExpanding));
    vLayout->addLayout(initPwdRegion());
    vLayout->addSpacerItem(new QSpacerItem(0, 26, QSizePolicy::Expanding, QSizePolicy::MinimumExpanding));
    vLayout->addStretch(0);
    vLayout->addWidget(buttonBox);
    centralWidget->setLayout(vLayout);

    QVBoxLayout *contentLayout = new QVBoxLayout;
    contentLayout->setSpacing(0);
    contentLayout->setContentsMargins(SHADOW_MARGIN_SIZE, SHADOW_MARGIN_SIZE, SHADOW_MARGIN_SIZE, SHADOW_MARGIN_SIZE);
    contentLayout->addWidget(initTitlebar());
    contentLayout->addWidget(centralWidget);
    this->setLayout(contentLayout);

    QGraphicsDropShadowEffect *pShadow = new QGraphicsDropShadowEffect();
    pShadow->setOffset(0, 1);
    pShadow->setColor(QColor(0, 0, 0, 127));
    pShadow->setBlurRadius(24);
    this->setGraphicsEffect(pShadow);
}

TitleBar * CustomDialog::initTitlebar()
{
    int titlebarHeight = 40;

    TitleBar * titlebarWidget = new TitleBar(this);
    titlebarWidget->setObjectName(QStringLiteral("titlebarWidget"));
    QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(titlebarWidget->sizePolicy().hasHeightForWidth());
    titlebarWidget->setSizePolicy(sizePolicy1);
    titlebarWidget->setMinimumSize(QSize(0, titlebarHeight));
    titlebarWidget->setMaximumSize(QSize(16777215, titlebarHeight));
    titlebarWidget->setStyleSheet(QStringLiteral("#titlebarWidget {background-color: #434555;}"));
    titlebarWidget->init(this, titlebarHeight, SHADOW_MARGIN_SIZE);
    titlebarWidget->setTitleName(tr("CustomDialog"));
    titlebarWidget->setMinButtonVisible(false);
    titlebarWidget->setParentWidgetResizable(false);

    return titlebarWidget;
}

QLayout *CustomDialog::initAccountRegion()
{
    m_pComboBoxZone = new QComboBox(this);
    m_pComboBoxZone->setObjectName("comboBoxZone");
    m_pComboBoxZone->setEditable(true);
    m_pComboBoxZone->lineEdit()->setAlignment(Qt::AlignCenter);
    m_pComboBoxZone->setSizeIncrement(5,5);
    m_pComboBoxZone->setMaxVisibleItems(8);
    m_pComboBoxZone->addItem("+086");
    m_pComboBoxZone->addItem("+0823");

    //m_pComboBoxZone->setPopupWidthOffset(-8);
    //m_pComboBoxZone->setPopupOffset(QPoint(0, 8));

    QRegExp regZone("[+]?[0-9]+");
    QRegExpValidator* pValidatorZone = new QRegExpValidator(this);
    pValidatorZone->setRegExp(regZone);
    m_pComboBoxZone->lineEdit()->setValidator(pValidatorZone);

//    connect(m_pComboBoxZone, SIGNAL(activated(QString)), this, SLOT(onSelectZone(QString)));
//    connect(m_pComboBoxZone->lineEdit(), SIGNAL(focus(bool)), SLOT(onAccountEditFocus(bool)));
//    connect(m_pComboBoxZone->lineEdit(), SIGNAL(textChanged(QString)), SLOT(onAccountInputChange()));
//    connect(m_pComboBoxZone, SIGNAL(currentIndexChanged(int)), this, SLOT(onAccountInputChange()));

    m_pLineEditAccount = new QCustomLineEdit(this);
    m_pLineEditAccount->setPlaceholderText(tr("Please input phone number"));

    QRegExp regAccount("[0-9]+");
    QRegExpValidator* pValidatorAccount = new QRegExpValidator(this);
    pValidatorAccount->setRegExp(regAccount);
    m_pLineEditAccount->setValidator(pValidatorAccount);

//    connect(m_pLineEditAccount, SIGNAL(focus(bool)), SLOT(onAccountEditFocus(bool)));
//    connect(m_pLineEditAccount, SIGNAL(textChanged(QString)), this, SLOT(onAccountInputChange()));

    QHBoxLayout* pLayoutAccount = new QHBoxLayout();
    pLayoutAccount->addWidget(m_pComboBoxZone);
    pLayoutAccount->addSpacerItem(new QSpacerItem(5, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
    pLayoutAccount->addWidget(m_pLineEditAccount);
    pLayoutAccount->setSpacing(0);
    pLayoutAccount->setContentsMargins(0, 0, 0, 0);

    m_pLineAccount = new QLabel(this);
    m_pLineAccount->setObjectName("labelLine");
    m_pLineAccount->setFrameStyle(QFrame::NoFrame);
    m_pLineAccount->setFixedHeight(1);

    m_pLineEditAccount->setBuddyWidget(m_pLineAccount);

    QVBoxLayout* pLayout = new QVBoxLayout();
    pLayout->addLayout(pLayoutAccount);
    pLayout->addSpacerItem(new QSpacerItem(0, 7, QSizePolicy::Expanding, QSizePolicy::Fixed));
    pLayout->addWidget(m_pLineAccount);
    pLayout->setSpacing(0);
    pLayout->setContentsMargins(0, 0, 0, 0);
    return pLayout;
}

QLayout *CustomDialog::initPwdRegion()
{
    m_pLineEditPwd = new QCustomLineEdit(this);
    m_pLineEditPwd->setPlaceholderText(tr("Set password"));
    m_pLineEditPwd->setEchoMode(QLineEdit::Password);

    m_pLinePwd = new QLabel(this);
    m_pLinePwd->setObjectName("labelLine");
    m_pLinePwd->setFrameStyle(QFrame::NoFrame);
    m_pLinePwd->setFixedHeight(1);

    m_pLineEditPwd->setBuddyWidget(m_pLinePwd);

    QVBoxLayout* pLayout = new QVBoxLayout();
    pLayout->addWidget(m_pLineEditPwd);
    pLayout->addSpacerItem(new QSpacerItem(0, 7, QSizePolicy::Expanding, QSizePolicy::Fixed));
    pLayout->addWidget(m_pLinePwd);
    pLayout->setSpacing(0);
    pLayout->setContentsMargins(0, 0, 0, 0);
    return pLayout;
}
