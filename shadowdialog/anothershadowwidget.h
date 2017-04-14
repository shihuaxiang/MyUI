#ifndef ANOTHERSHADOWWIDGET_H
#define ANOTHERSHADOWWIDGET_H

#include <QWidget>

namespace Ui {
class AnotherShadowWidget;
}

class AnotherShadowWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AnotherShadowWidget(QWidget *parent = 0);
    ~AnotherShadowWidget();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::AnotherShadowWidget *ui;
};

#endif // ANOTHERSHADOWWIDGET_H
