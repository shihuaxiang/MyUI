#include "QCustomLineEdit.h"
#include <QFocusEvent>

QCustomLineEdit::QCustomLineEdit(QWidget *parent) : QLineEdit(parent)
{
}

void QCustomLineEdit::setBuddyWidget(QWidget* w)
{
    buddyWidget = w;
}

void QCustomLineEdit::focusInEvent(QFocusEvent *e)
{
    emit focus(true);

    if (buddyWidget)
         buddyWidget->setStyleSheet("background-color: #1cba77");

    QLineEdit::focusInEvent(e);
}

void QCustomLineEdit::focusOutEvent(QFocusEvent *e)
{
    emit focus(false);

    if (buddyWidget)
         buddyWidget->setStyleSheet("background-color: #e7e7e7");

    QLineEdit::focusOutEvent(e);
}

