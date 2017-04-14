#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class FramelessHelper;

class TitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit TitleBar(QWidget *parent);

    /**
     * @brief init
     * @param buddyWidget : the titlebar is buddyWidget's titlebar
     * @param titleHeight : the titlebar height
     */
    void init(QWidget *buddyWidget, int titleHeight, int topMargin = -1);

    void setMinButtonVisible(bool visible);
    bool minButtonVisible();

    void setParentWidgetResizable(bool b);
    bool parentWidgetResizable();

    void setTitleName(QString name);
    QString titleName();

signals:

public slots:
    void onClicked();

private:
    void init(QString title, bool isParentWidgetResizable, QWidget *parent);

    FramelessHelper *m_pHelper;

    QLabel      *m_titleLabel;
    QPushButton *m_minButton;
    QPushButton *m_closeButton;
    //bool        m_minButtonVisible = true;
    QWidget*     m_buddyWidget = Q_NULLPTR;
};

#endif // TITLEBAR_H
