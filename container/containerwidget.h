#ifndef CONTAINERWIDGET_H
#define CONTAINERWIDGET_H

#include <QIcon>
#include <QLabel>
#include <QMouseEvent>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>

class DarkTitlebar : public QWidget
{
    Q_OBJECT

private:
    QLabel      *m_titleLabel;
    QPushButton *m_minButton;
    QPushButton *m_closeButton;

    QPoint      pressPoint;
    bool        isMoving    = false;

public:
    DarkTitlebar( QWidget* parent );
    ~DarkTitlebar();

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

signals:
    void closeParent();

public slots:

};

class ContainerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ContainerWidget(QWidget* contentWidget, const QString & title, QWidget *parent = 0);
    ~ContainerWidget();

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *event);

private:
    DarkTitlebar* titlebar = NULL;
    QWidget* contentWidget = NULL;

};

#endif // CONTAINERWIDGET_H
