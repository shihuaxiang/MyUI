#include "FramelessHelper.h"
#include "FramelessHelper_p.h"
#include <QDebug>

QMargins CursorPosCalculator::m_margins = QMargins(5, 5, 5, 5);
TitlePosition CursorPosCalculator::m_titlePosition = TitlePosition();

/***** TitlePosition *****/
TitlePosition::TitlePosition()
{
    m_bHasTopTitle      = true;
    m_bHasLeftTitle     = false;
    m_nTopTitleHeight   = 30;
    m_nLeftTitleWidth   = 30;
}

/***** CursorPosCalculator *****/
CursorPosCalculator::CursorPosCalculator()
{
    reset();
}

void CursorPosCalculator::reset()
{
    m_bOnEdges = false;
    m_bOnLeftEdge = false;
    m_bOnRightEdge = false;
    m_bOnTopEdge = false;
    m_bOnBottomEdge = false;
    m_bOnTopLeftEdge = false;
    m_bOnBottomLeftEdge = false;
    m_bOnTopRightEdge  = false;
    m_bOnBottomRightEdge = false;
}

bool TitlePosition::isPointOnTitle(const QPoint &globalMousePos)
{
    if (m_bHasTopTitle && globalMousePos.y() < m_nTopTitleHeight)
        return true;

    if (m_bHasLeftTitle && globalMousePos.x() < m_nLeftTitleWidth)
        return true;

    return false;
}

void CursorPosCalculator::recalculate(const QPoint &globalMousePos, const QRect &frameRect)
{
    int globalMouseX = globalMousePos.x();
    int globalMouseY = globalMousePos.y();

    int frameX = frameRect.x();
    int frameY = frameRect.y();

    int frameWidth = frameRect.width();
    int frameHeight = frameRect.height();

    m_bOnLeftEdge = (globalMouseX >= frameX &&
                  globalMouseX <= frameX + m_margins.left() );

    m_bOnRightEdge = (globalMouseX >= frameX + frameWidth - m_margins.right() &&
                   globalMouseX <= frameX + frameWidth);

    m_bOnTopEdge = (globalMouseY >= frameY &&
                 globalMouseY <= frameY + m_margins.top() );

    m_bOnBottomEdge = (globalMouseY >= frameY + frameHeight - m_margins.bottom() &&
                    globalMouseY <= frameY + frameHeight);

    m_bOnTopLeftEdge = m_bOnTopEdge && m_bOnLeftEdge;
    m_bOnBottomLeftEdge = m_bOnBottomEdge && m_bOnLeftEdge;
    m_bOnTopRightEdge = m_bOnTopEdge && m_bOnRightEdge;
    m_bOnBottomRightEdge = m_bOnBottomEdge && m_bOnRightEdge;

    m_bOnEdges = m_bOnLeftEdge || m_bOnRightEdge || m_bOnTopEdge || m_bOnBottomEdge;
}


/***** WidgetData *****/
WidgetData::WidgetData(FramelessHelperPrivate *_d, QWidget *pTopLevelWidget)
{
    d = _d;
    m_pWidget = pTopLevelWidget;
    m_bLeftButtonPressed = false;
    m_bCursorShapeChanged = false;
    m_bPressedOnTitle = false;
    m_pRubberBand = NULL;

    m_windowFlags = m_pWidget->windowFlags();
    m_pWidget->setMouseTracking(true);
    m_pWidget->setAttribute(Qt::WA_Hover, true);

    updateRubberBandStatus();
}

WidgetData::~WidgetData()
{
    m_pWidget->setMouseTracking(false);
    m_pWidget->setWindowFlags(m_windowFlags);
    m_pWidget->setAttribute(Qt::WA_Hover, false);

    delete m_pRubberBand;
    m_pRubberBand = NULL;
}

QWidget* WidgetData::widget()
{
    return m_pWidget;
}

void WidgetData::handleWidgetEvent(QEvent *event)
{
    switch (event->type())
    {
    default:
        break;
    case QEvent::MouseButtonPress:
        handleMousePressEvent(static_cast<QMouseEvent*>(event));
        break;
    case QEvent::MouseButtonRelease:
        handleMouseReleaseEvent(static_cast<QMouseEvent*>(event));
        break;
    case QEvent::MouseMove:
        handleMouseMoveEvent(static_cast<QMouseEvent*>(event));
        break;
    case QEvent::Leave:
        handleLeaveEvent(static_cast<QMouseEvent*>(event));
        break;
    case QEvent::HoverMove:
        handleHoverMoveEvent(static_cast<QHoverEvent*>(event));
        break;
    }
}

void WidgetData::updateRubberBandStatus()
{
    if (d->m_bRubberBandOnMove || d->m_bRubberBandOnResize)
    {
        if (NULL == m_pRubberBand)
            m_pRubberBand = new QRubberBand(QRubberBand::Rectangle);
    }
    else
    {
        delete m_pRubberBand;
        m_pRubberBand = NULL;
    }
}

void WidgetData::updateCursorShape(const QPoint &globalMousePos, const QPoint &mousePos)
{
    if (m_pWidget->isFullScreen() || m_pWidget->isMaximized())
    {
        if (m_bCursorShapeChanged)
        {
            m_pWidget->unsetCursor();
        }
        return;
    }

    m_moveMousePos.recalculate(globalMousePos, m_pWidget->frameGeometry());

    if(m_moveMousePos.m_bOnTopLeftEdge || m_moveMousePos.m_bOnBottomRightEdge)
    {
        m_pWidget->setCursor( Qt::SizeFDiagCursor );
        m_bCursorShapeChanged = true;
    }
    else if(m_moveMousePos.m_bOnTopRightEdge || m_moveMousePos.m_bOnBottomLeftEdge)
    {
        m_pWidget->setCursor( Qt::SizeBDiagCursor );
        m_bCursorShapeChanged = true;
    }
    else if(m_moveMousePos.m_bOnLeftEdge || m_moveMousePos.m_bOnRightEdge)
    {
        m_pWidget->setCursor( Qt::SizeHorCursor );
        m_bCursorShapeChanged = true;
    }
    else if(m_moveMousePos.m_bOnTopEdge || m_moveMousePos.m_bOnBottomEdge)
    {
        m_pWidget->setCursor( Qt::SizeVerCursor );
        m_bCursorShapeChanged = true;
    }
    else if(m_bPressedOnTitle)
    {
        m_pWidget->setCursor( Qt::SizeAllCursor );
        m_bCursorShapeChanged = true;
    }
    else
    {
        if (m_bCursorShapeChanged)
        {
            m_pWidget->unsetCursor();
            m_bCursorShapeChanged = false;
        }
    }
}

void WidgetData::resizeWidget(const QPoint &globalMousePos)
{
    QRect origRect;

    if (d->m_bRubberBandOnResize)
        origRect = m_pRubberBand->frameGeometry();
    else
        origRect = m_pWidget->frameGeometry();

    int left = origRect.left();
    int top = origRect.top();
    int right = origRect.right();
    int bottom = origRect.bottom();
    origRect.getCoords(&left, &top, &right, &bottom);

    int minWidth = m_pWidget->minimumWidth();
    int minHeight = m_pWidget->minimumHeight();

    if (m_pressedMousePos.m_bOnTopLeftEdge)
    {
        left = globalMousePos.x();
        top = globalMousePos.y();
    }
    else if (m_pressedMousePos.m_bOnBottomLeftEdge)
    {
        left = globalMousePos.x();
        bottom = globalMousePos.y();
    }
    else if (m_pressedMousePos.m_bOnTopRightEdge)
    {
        right = globalMousePos.x();
        top = globalMousePos.y();
    }
    else if (m_pressedMousePos.m_bOnBottomRightEdge)
    {
        right = globalMousePos.x();
        bottom = globalMousePos.y();
    }
    else if (m_pressedMousePos.m_bOnLeftEdge)
    {
        left = globalMousePos.x();
    }
    else if (m_pressedMousePos.m_bOnRightEdge)
    {
        right = globalMousePos.x();
    }
    else if (m_pressedMousePos.m_bOnTopEdge)
    {
        top = globalMousePos.y();
    }
    else if (m_pressedMousePos.m_bOnBottomEdge)
    {
        bottom = globalMousePos.y();
    }

    QRect newRect(QPoint(left, top), QPoint(right, bottom));

    if (newRect.isValid())
    {
        if (minWidth > newRect.width())
        {
            if (left != origRect.left())
                newRect.setLeft(origRect.left());
            else
                newRect.setRight(origRect.right());
        }
        if (minHeight > newRect.height())
        {
            if (top != origRect.top())
                newRect.setTop(origRect.top());
            else
                newRect.setBottom(origRect.bottom());
        }

        if (d->m_bRubberBandOnResize)
        {
            m_pRubberBand->setGeometry(newRect);
        }
        else
        {
            m_pWidget->setGeometry(newRect);
        }
    }
}

void WidgetData::moveWidget(const QPoint& globalMousePos)
{
    if (d->m_bRubberBandOnMove)
    {
        m_pRubberBand->move(globalMousePos - m_ptDragPos);
    }
    else
    {
        m_pWidget->move(globalMousePos - m_ptDragPos);
    }
}

void WidgetData::handleMousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_bLeftButtonPressed = true;
        m_bPressedOnTitle = CursorPosCalculator::m_titlePosition.isPointOnTitle(event->pos());

        QRect frameRect = m_pWidget->frameGeometry();
        m_pressedMousePos.recalculate(event->globalPos(), frameRect);

        m_ptDragPos = event->globalPos() - frameRect.topLeft();

        if (m_pressedMousePos.m_bOnEdges)
        {
            if (d->m_bRubberBandOnResize)
            {
                m_pRubberBand->setGeometry(frameRect);
                m_pRubberBand->show();
            }
        }
        else if (d->m_bRubberBandOnMove)
        {
            m_pRubberBand->setGeometry(frameRect);
            m_pRubberBand->show();
        }
    }
}

void WidgetData::handleMouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_bLeftButtonPressed = false;
        m_bPressedOnTitle = false;
        m_pressedMousePos.reset();
        if (m_pRubberBand && m_pRubberBand->isVisible())
        {
            m_pRubberBand->hide();
            m_pWidget->setGeometry(m_pRubberBand->geometry());
        }
    }
}

void WidgetData::handleMouseMoveEvent(QMouseEvent *event)
{
    if (m_bLeftButtonPressed)
    {
        if (d->m_bWidgetResizable && m_pressedMousePos.m_bOnEdges)
        {
            resizeWidget(event->globalPos());
        }
        else if (d->m_bWidgetMovable && m_bPressedOnTitle)
        {
            moveWidget(event->globalPos());
        }
    }
    else if (d->m_bWidgetResizable)
    {
        updateCursorShape(event->globalPos(), event->pos());
    }
}

void WidgetData::handleLeaveEvent(QEvent *event)
{
    Q_UNUSED(event)
    if (!m_bLeftButtonPressed)
    {
        m_pWidget->unsetCursor();
    }
}

void WidgetData::handleHoverMoveEvent(QHoverEvent *event)
{
    if (d->m_bWidgetResizable)
    {
        updateCursorShape(m_pWidget->mapToGlobal(event->pos()), event->pos());
    }
}

/*****FramelessHelper*****/
FramelessHelper::FramelessHelper(QObject *parent)
    : QObject(parent),
      d(new FramelessHelperPrivate())
{
    d->m_bWidgetMovable = true;
    d->m_bWidgetResizable = true;
    d->m_bRubberBandOnResize = false;
    d->m_bRubberBandOnMove = false;
}

FramelessHelper::~FramelessHelper()
{
    QList<QWidget*> keys = d->m_widgetDataHash.keys();
    int size = keys.size();
    for (int i = 0; i < size; ++i)
    {
        delete d->m_widgetDataHash.take(keys[i]);
    }

    delete d;
}

bool FramelessHelper::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type())
    {
    case QEvent::MouseMove:
    case QEvent::HoverMove:
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonRelease:
    case QEvent::Leave:
    {
        WidgetData *data = d->m_widgetDataHash.value(static_cast<QWidget*>(obj));
        if (data)
        {
            data->handleWidgetEvent(event);
            return true;
        }
    }
    }
    return QObject::eventFilter(obj, event);
}

void FramelessHelper::activateOn(QWidget *topLevelWidget)
{
    if (!d->m_widgetDataHash.contains(topLevelWidget))
    {
        WidgetData *data = new WidgetData(d, topLevelWidget);
        d->m_widgetDataHash.insert(topLevelWidget, data);

        topLevelWidget->installEventFilter(this);
    }
}

void FramelessHelper::removeFrom(QWidget *topLevelWidget)
{
    WidgetData *data = d->m_widgetDataHash.take(topLevelWidget);
    if (data)
    {
        topLevelWidget->removeEventFilter(this);
        delete data;
    }
}

void FramelessHelper::setRubberBandOnMove(bool movable)
{
    d->m_bRubberBandOnMove = movable;
    QList<WidgetData*> list = d->m_widgetDataHash.values();
    foreach (WidgetData *data, list)
    {
        data->updateRubberBandStatus();
    }
}

void FramelessHelper::setWidgetMovable(bool movable)
{
    d->m_bWidgetMovable = movable;
}

void FramelessHelper::setWidgetResizable(bool resizable)
{
    d->m_bWidgetResizable = resizable;
}

void FramelessHelper::setRubberBandOnResize(bool resizable)
{
    d->m_bRubberBandOnResize = resizable;
    QList<WidgetData*> list = d->m_widgetDataHash.values();
    foreach (WidgetData *data, list)
    {
        data->updateRubberBandStatus();
    }
}

void FramelessHelper::setResizableArea(QMargins m)
{
    CursorPosCalculator::m_margins = m;
}

void FramelessHelper::setTopTitle(bool hasTopTitle, uint topTitleHeight)
{
    CursorPosCalculator::m_titlePosition.m_bHasTopTitle = hasTopTitle;

    if (topTitleHeight > 0)
    {
        CursorPosCalculator::m_titlePosition.m_nTopTitleHeight = topTitleHeight;
    }
}

void FramelessHelper::setLeftTitle(bool hasLeftTitle, uint leftTitleWidth)
{
    CursorPosCalculator::m_titlePosition.m_bHasLeftTitle = hasLeftTitle;

    if (leftTitleWidth > 0)
    {
        CursorPosCalculator::m_titlePosition.m_nLeftTitleWidth = leftTitleWidth;
    }
}

bool FramelessHelper::widgetMovable()
{
    return d->m_bWidgetMovable;
}

bool FramelessHelper::widgetResizable()
{
    return d->m_bWidgetResizable;
}

bool FramelessHelper::rubberBandOnMove()
{
    return d->m_bRubberBandOnMove;
}

bool FramelessHelper::rubberBandOnResisze()
{
    return d->m_bRubberBandOnResize;
}

QMargins FramelessHelper::resizableArea()
{
    return CursorPosCalculator::m_margins;
}
