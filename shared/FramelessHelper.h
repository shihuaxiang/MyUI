#ifndef FRAMELESSHELPER_H
#define FRAMELESSHELPER_H

#include <QObject>
#include <QMargins>

class QWidget;
class FramelessHelperPrivate;

class FramelessHelper : public QObject
{
    Q_OBJECT
public:
    explicit FramelessHelper(QObject *parent = 0);

    ~FramelessHelper();
    void activateOn(QWidget *topLevelWidget);
    void removeFrom(QWidget *topLevelWidget);
    void setWidgetMovable(bool movable);
    void setWidgetResizable(bool resizable);
    void setRubberBandOnMove(bool movable);
    void setRubberBandOnResize(bool resizable);
    void setResizableArea(QMargins m);
    void setTopTitle(bool hasTopTitle, uint topTitleHeight);
    void setLeftTitle(bool hasLeftTitle, uint leftTitleWidth);
    bool widgetResizable();
    bool widgetMovable();
    bool rubberBandOnMove();
    bool rubberBandOnResisze();
    QMargins resizableArea();

protected:
    virtual bool eventFilter(QObject *obj, QEvent *event);

private:
    FramelessHelperPrivate *d;
};

#endif // FRAMELESSHELPER_H
