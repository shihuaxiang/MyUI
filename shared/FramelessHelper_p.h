#ifndef FRAMELESSHELPERPRIVATE_H
#define FRAMELESSHELPERPRIVATE_H

#include <QPoint>
#include <QRect>
#include <QRubberBand>
#include <QMouseEvent>

class QWidget;
class WidgetData;

/*****
 * FramelessHelperPrivate
*****/
class FramelessHelperPrivate
{
public:
    QHash<QWidget*, WidgetData*> m_widgetDataHash;
    bool m_bWidgetMovable        : true;
    bool m_bWidgetResizable      : true;
    bool m_bRubberBandOnResize   : true;
    bool m_bRubberBandOnMove     : true;
};

/*****
 * TitlePos
 * title position: on top or left of the window
*****/
class TitlePosition
{
public:
    explicit TitlePosition();
    bool isPointOnTitle(const QPoint &globalMousePos);

    bool m_bHasTopTitle;
    bool m_bHasLeftTitle;
    int m_nTopTitleHeight;
    int m_nLeftTitleWidth;
};

/*****
 * CursorPosCalculator
*****/
class CursorPosCalculator
{
public:
    explicit CursorPosCalculator();
    void reset();
    void recalculate(const QPoint &globalMousePos, const QRect &frameRect);

public:
    bool m_bOnEdges              : true;
    bool m_bOnLeftEdge           : true;
    bool m_bOnRightEdge          : true;
    bool m_bOnTopEdge            : true;
    bool m_bOnBottomEdge         : true;
    bool m_bOnTopLeftEdge        : true;
    bool m_bOnBottomLeftEdge     : true;
    bool m_bOnTopRightEdge       : true;
    bool m_bOnBottomRightEdge    : true;

    static QMargins m_margins;

    static TitlePosition    m_titlePosition;
};

/*****
 * WidgetData
 * cursor style, move widget & scale widget
*****/
class WidgetData
{
public:
    explicit WidgetData(FramelessHelperPrivate *d, QWidget *pTopLevelWidget);
    ~WidgetData();
    QWidget* widget();
    void handleWidgetEvent(QEvent *event);
    void updateRubberBandStatus();

private:
    void updateCursorShape(const QPoint &globalMousePos, const QPoint &mousePos);
    void resizeWidget(const QPoint &globalMousePos);
    void moveWidget(const QPoint &globalMousePos);
    void handleMousePressEvent(QMouseEvent *event);
    void handleMouseReleaseEvent(QMouseEvent *event);
    void handleMouseMoveEvent(QMouseEvent *event);
    void handleLeaveEvent(QEvent *event);
    void handleHoverMoveEvent(QHoverEvent *event);

private:
    FramelessHelperPrivate *d;
    QRubberBand *m_pRubberBand;
    QWidget *m_pWidget;
    QPoint m_ptDragPos;
    CursorPosCalculator m_pressedMousePos;
    CursorPosCalculator m_moveMousePos;
    bool m_bLeftButtonPressed;
    bool m_bCursorShapeChanged;
    bool m_bPressedOnTitle;
    Qt::WindowFlags m_windowFlags;
};

#endif // FRAMELESSHELPERPRIVATE_H
