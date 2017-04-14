#ifndef QCUSTOMLINEEDIT_H
#define QCUSTOMLINEEDIT_H

#include <QLineEdit>

/**
 * @brief emit in/out focus
 */
class QCustomLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    QCustomLineEdit(QWidget* parent = 0);
    void setBuddyWidget(QWidget* w);

signals:
    void focus(bool bFocus);

protected:
    void focusInEvent(QFocusEvent* e) override;
    void focusOutEvent(QFocusEvent* e) override;

private:
    QWidget* buddyWidget = NULL;

};

#endif // QCUSTOMLINEEDIT_H
