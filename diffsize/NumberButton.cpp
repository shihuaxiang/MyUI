#include "numberbutton.h"
#include <QDebug>
#include <QPainter>
#include "ImageOp.h"

IconButton::IconButton(QWidget *parent)
    : QPushButton(parent)
{
    connect(this, &QPushButton::toggled, this, &IconButton::onToggled);

    //this->setStyleSheet("QPushButton {border: none;}");
}

void IconButton::setNormalPixmap(const QString fileName)
{
	m_normalPixmap = fileName;
}

void IconButton::setHoverPixmap(const QString fileName)
{
	m_hoverPixmap = fileName;
}

void IconButton::setCheckedPixmap(const QString fileName)
{
	m_checkedPixmap = fileName;
}

void IconButton::setPressedPixmap(const QString fileName)
{
	m_pressedPixmap = fileName;
}

void IconButton::onToggled(bool checked)
{
    updateIcon();
}

void IconButton::enterEvent(QEvent *event)
{
    QPushButton::enterEvent(event);

    status = HOVER;
    updateIcon();
}

void IconButton::leaveEvent(QEvent *event)
{
    QPushButton::leaveEvent(event);

    status = NORMAL;
    updateIcon();
}

void IconButton::mousePressEvent(QMouseEvent * event)
{
	QPushButton::mousePressEvent(event);

	status = PRESSED;
	updateIcon();
}

void IconButton::mouseReleaseEvent(QMouseEvent * event)
{
	QPushButton::mouseReleaseEvent(event);

	status = NORMAL;
	updateIcon();
}

void IconButton::updateIcon()
{
    if (this->isChecked())
    {
        this->setIcon(makeSvgIcon(m_checkedPixmap));
    }
    else
    {
        if (status == HOVER)
            this->setIcon(makeSvgIcon(m_hoverPixmap));
        else if (status == PRESSED)
            this->setIcon(makeSvgIcon(m_pressedPixmap));
        else
            this->setIcon(makeSvgIcon(m_normalPixmap));
    }

//    if (this->isChecked())
//    {
//        this->setIcon(QIcon(m_checkedPixmap));
//    }
//    else
//    {
//        if (status == HOVER)
//            this->setIcon(QIcon(m_hoverPixmap));
//		else if (status == PRESSED)
//			this->setIcon(QIcon(m_pressedPixmap));
//        else
//            this->setIcon(QIcon(m_normalPixmap));
//    }
}

QIcon IconButton::makeSvgIcon(const QString fileName)
{
    return QIcon(ImageOp::makeSvgPixmap(fileName, this->iconSize()));
}

NumberButton::NumberButton(QWidget *parent)
    : IconButton(parent)
{
}

void NumberButton::paintEvent(QPaintEvent *event)
{
    IconButton::paintEvent(event);

    // draw unread number
    if (m_number > 0)
    {
        QPainter painter(this);

        QFont font = painter.font();
        font.setPointSize(m_fontSize);

        //qDebug() << "current font" << painter.font();

        QString numberText = (m_number > 99) ? QString("99+") : QString::number(m_number);
        QFontMetrics fm(font);
        int textWidth = fm.width(numberText);
        int textHeight = fm.height();
        textWidth = (textWidth < textHeight) ? textHeight : textWidth;

        QPoint point = this->rect().center();
        QRectF rect(point.x() + m_leftMargin, m_topMargin, textWidth, textHeight);
        painter.setPen(QPen(Qt::NoPen));
        painter.setBrush(QBrush(QColor("#FF6741")));
        painter.drawEllipse(rect);

        painter.setPen(QColor(Qt::white));
        painter.setFont(font);
        painter.drawText(rect, Qt::AlignCenter | Qt::AlignHCenter, numberText);
    }
}

ChatNumberButton::ChatNumberButton(QWidget *parent)
    : NumberButton(parent)
{
    m_leftMargin = 6;
    m_topMargin = 6;

    //connect(EeoEngine::ChatEngine::instance(), &EeoEngine::ChatEngine::updateUnreadCount, this, &NumberButton::numberChanged);
}

//void ChatNumberButton::numberChanged(const EeoEngine::ContactsID& id)
//{
//    this->m_number = 4;//EeoEngine::ChatEngine::instance()->getAllUnreadCount();

//    update();
//}

NoticeNumberButton::NoticeNumberButton(QWidget *parent)
    : NumberButton(parent)
{
    m_leftMargin = 6;
    //connect(EeoEngine::NoticeEngine::instance(), &EeoEngine::NoticeEngine::updateUnreadNoticeCount, this, &NoticeNumberButton::numberChanged);
}

void NoticeNumberButton::numberChanged()
{
    this->m_number = 5;//EeoEngine::NoticeEngine::instance()->getUnreadNoticeCount();

    update();
}
