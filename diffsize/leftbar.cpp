#include "leftbar.h"
#include "shared/FramelessHelper.h"
#include "numberbutton.h"
#include <QFile>
#include <QPushButton>
#include <QVBoxLayout>
#include <QToolButton>

LeftBar::LeftBar(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

    this->setObjectName("leftBar");
    this->setMinimumHeight(620);
    this->setFixedWidth(66);

    QWidget * avatarWidget = createAvatarWidget();
    QWidget * middleWidget = createMiddleWidget();
    QWidget * bottomWidget = createBottomWidget();

    QVBoxLayout * verticalLayout = new QVBoxLayout(this);
    verticalLayout->setContentsMargins(0, 0, 0, 18);
    verticalLayout->addSpacerItem(new QSpacerItem(0, 28, QSizePolicy::Expanding, QSizePolicy::Fixed));
    verticalLayout->addWidget(avatarWidget);
    verticalLayout->addSpacerItem(new QSpacerItem(0, 26, QSizePolicy::Expanding, QSizePolicy::Fixed));
    verticalLayout->addWidget(middleWidget);
    verticalLayout->addStretch(0);
    verticalLayout->addWidget(bottomWidget);

    QFile qss(":/leftbar.qss");
    qss.open(QFile::ReadOnly);
    setStyleSheet(qss.readAll());
    qss.close();

    FramelessHelper * m_pHelper = new FramelessHelper(NULL);
    m_pHelper->activateOn(this);
    m_pHelper->setTopTitle(true, 620);
    m_pHelper->setWidgetMovable(true);
    m_pHelper->setWidgetResizable(true);
    m_pHelper->setRubberBandOnMove(false);
    m_pHelper->setRubberBandOnResize(false);
}

QWidget * LeftBar::createAvatarWidget()
{
    QWidget * avatarWidget = new QWidget(this);
    avatarWidget->setObjectName("avatarWidget");
    avatarWidget->setFixedSize(QSize(66, 50));

    QHBoxLayout * avatarLayout = new QHBoxLayout(avatarWidget);
    avatarLayout->setContentsMargins(0, 0, 0, 0);
    avatarLayout->setSpacing(0);

    QPushButton * avatarButton = new QPushButton(avatarWidget);
    avatarButton->setObjectName("avatarButton");
    avatarButton->setFixedSize(QSize(50, 50));
    avatarButton->setIconSize(QSize(44, 44));
    connect(avatarButton, &QPushButton::clicked, this, &LeftBar::avatarButtonClicked);
    avatarLayout->addWidget(avatarButton);

    return avatarWidget;
}

QWidget * LeftBar::createMiddleWidget()
{
    QWidget * middleWidget = new QWidget(this);
    middleWidget->setObjectName("middleWidget");
    middleWidget->setFixedSize(QSize(66, 222));

    QVBoxLayout * verticalLayout = new QVBoxLayout(middleWidget);
    verticalLayout->setContentsMargins(0, 0, 0, 0);
    verticalLayout->setSpacing(0);

    ChatNumberButton * chatButton = new ChatNumberButton(middleWidget);
    chatButton->setObjectName("chatButton");
    chatButton->setCheckable(true);
    chatButton->setChecked(true);
    chatButton->setAutoExclusive(true);
    chatButton->setFixedSize(QSize(66, 58));
    chatButton->setIconSize(QSize(28, 28));
    chatButton->setNormalPixmap(":/images/chat-normal.png");
    chatButton->setHoverPixmap(":/images/chat-hover.png");
    chatButton->setCheckedPixmap(":/images/chat-selected.png");
    connect(chatButton, &QPushButton::clicked, this, &LeftBar::chatButtonClicked);
    verticalLayout->addWidget(chatButton);

    IconButton * contactButton = new IconButton(middleWidget);
    contactButton->setObjectName("contactButton");
    contactButton->setCheckable(true);
    contactButton->setAutoExclusive(true);
    contactButton->setFixedSize(QSize(66, 58));
    contactButton->setIconSize(QSize(28, 26));
    contactButton->setNormalPixmap(":/images/contacts-normal.png");
    contactButton->setHoverPixmap(":/images/contacts-hover.png");
    contactButton->setCheckedPixmap(":/images/contacts-selected.png");
    connect(contactButton, &QPushButton::clicked, this, &LeftBar::contactButtonClicked);
    verticalLayout->addWidget(contactButton);

    IconButton * courseButton = new IconButton(middleWidget);
    courseButton->setObjectName("courseButton");
    courseButton->setCheckable(true);
    courseButton->setAutoExclusive(true);
    courseButton->setFixedSize(QSize(66, 50));
    courseButton->setIconSize(QSize(26, 22));
    courseButton->setNormalPixmap(":/images/course-normal.png");
    courseButton->setHoverPixmap(":/images/course-hover.png");
    courseButton->setCheckedPixmap(":/images/course-selected.png");
    connect(courseButton, &QPushButton::clicked, this, &LeftBar::courseButtonClicked);
    verticalLayout->addWidget(courseButton);

    IconButton * cloudButton = new IconButton(middleWidget);
    cloudButton->setObjectName("cloudButton");
    cloudButton->setCheckable(true);
    cloudButton->setAutoExclusive(true);
    cloudButton->setFixedSize(QSize(66, 50));
    cloudButton->setIconSize(QSize(28, 18));
    cloudButton->setNormalPixmap(":/images/clouddisk-normal.png");
    cloudButton->setHoverPixmap(":/images/clouddisk-hover.png");
    cloudButton->setCheckedPixmap(":/images/clouddisk-selected.png");
    connect(cloudButton, &QPushButton::clicked, this, &LeftBar::cloudButtonClicked);
    verticalLayout->addWidget(cloudButton);

	return middleWidget;
}

QWidget * LeftBar::createBottomWidget()
{
    QWidget * bottomWidget = new QWidget(this);
    bottomWidget->setObjectName("bottomWidget");
    bottomWidget->setFixedSize(QSize(66, 116));

	QVBoxLayout * verticalLayout = new QVBoxLayout(bottomWidget);
    verticalLayout->setContentsMargins(0, 0, 0, 0);
    verticalLayout->setSpacing(0);

	NoticeNumberButton * noticeCenterButton = new NoticeNumberButton(bottomWidget);
    noticeCenterButton->setObjectName("noticeCenterButton");
    noticeCenterButton->setFixedSize(QSize(66, 29));
    noticeCenterButton->setIconSize(QSize(18, 18));
    noticeCenterButton->setNormalPixmap(":/images/notice-normal.png");
    noticeCenterButton->setHoverPixmap(":/images/notice-hover.png");
    noticeCenterButton->setPressedPixmap(":/images/notice-pressed.png");
    connect(noticeCenterButton, &QPushButton::clicked, this, &LeftBar::noticeCenterButtonClicked);
    verticalLayout->addWidget(noticeCenterButton);

    IconButton * boardEditorButton = new IconButton(bottomWidget);
    boardEditorButton->setObjectName("boardEditorButton");
    boardEditorButton->setFixedSize(QSize(66, 29));
    boardEditorButton->setIconSize(QSize(18, 18));
    boardEditorButton->setNormalPixmap(":/images/boardeditor-normal.png");
    boardEditorButton->setHoverPixmap(":/images/boardeditor-hover.png");
    boardEditorButton->setPressedPixmap(":/images/boardeditor-pressed.png");
    connect(boardEditorButton, &QPushButton::clicked, this, &LeftBar::boardEditorButtonClicked);
    verticalLayout->addWidget(boardEditorButton);

    IconButton * deviceCheckButton = new IconButton(bottomWidget);
    deviceCheckButton->setObjectName("deviceCheckButton");
    deviceCheckButton->setFixedSize(QSize(66, 29));
    deviceCheckButton->setIconSize(QSize(18, 18));
    deviceCheckButton->setNormalPixmap(":/images/devicecheck-normal.png");
    deviceCheckButton->setHoverPixmap(":/images/devicecheck-hover.png");
    deviceCheckButton->setPressedPixmap(":/images/devicecheck-pressed.png");
    connect(deviceCheckButton, &QPushButton::clicked, this, &LeftBar::deviceCheckButtonClicked);
    verticalLayout->addWidget(deviceCheckButton);

    IconButton * settingButton = new IconButton(bottomWidget);
    settingButton->setObjectName("settingButton");
    settingButton->setFixedSize(QSize(66, 29));
    settingButton->setIconSize(QSize(18, 18));
    settingButton->setNormalPixmap(":/images/set-normal.png");
    settingButton->setHoverPixmap(":/images/set-hover.png");
    settingButton->setPressedPixmap(":/images/set-pressed.png");
    connect(settingButton, &QPushButton::clicked, this, &LeftBar::settingButtonClicked);
    verticalLayout->addWidget(settingButton);

    return bottomWidget;
}
