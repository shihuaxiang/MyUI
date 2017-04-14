#include <QDebug>
#include <QMessageBox>

#include "movable.h"

Movable::Movable(QWidget *parent, MoveType type)
    : QObject(parent)
      , type(type)
    , moveTarget(NULL)
{
    setMoveTriggerArea(120); // default area [0, 120]
    this->isMove = false;

    Q_ASSERT_X(parent, "move event", "class `Movable' must attach to a QWidget.");
	setMoveTarget(parent);
}

Movable::~Movable()
{

}

void Movable::setMoveTarget(QWidget *target)
{
    Q_ASSERT(target);
    this->moveTarget = target;
    target->installEventFilter(this);
}

void Movable::setMoveTriggerArea(int from, int to)
{
    if (from > to) {
        std::swap(from, to);
    }
    moveTriggerStart = from;
    moveTriggerEnd = to;
}

void Movable::setMoveTriggerArea(int to)
{
    this->setMoveTriggerArea(0, to);
}

void Movable::setMoveType(MoveType mt)
{
    type = mt;
}

bool Movable::eventFilter(QObject *obj, QEvent *event)
{
	if (!moveTarget->isEnabled())
		return QObject::eventFilter(obj, event);

	if (QEvent::MouseButtonPress == event->type())
    {
		QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
		targetPressEvent(mouseEvent);
	}
	else if (QEvent::MouseMove == event->type())
	{
		QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
		targetMoveEvent(mouseEvent);
	}
	else if (QEvent::MouseButtonRelease == event->type())
	{
		QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
		targetReleaseEvent(mouseEvent);
	}
	return QObject::eventFilter(obj, event);
}

void Movable::targetPressEvent(QMouseEvent *e)
{
    this->pressPoint = e->pos();
    if (this->moveTriggerStart < this->pressPoint.y() && this->pressPoint.y() < this->moveTriggerEnd) {
        this->isMove = true;
        if (type == Movable::SignalMove)
			emit signalPressed(pressPoint);
    }
}

void Movable::targetMoveEvent(QMouseEvent *e)
{
    if((e->buttons() == Qt::LeftButton) && this->isMove)
    {
        int dx = e->x() - this->pressPoint.x();
        int dy = e->y() - this->pressPoint.y();

        switch (type)
        {
        case Movable::SignalMove:
            emit signalMove(dx, dy);
            break;
        case Movable::MoveSelf:
			moveTarget->move(moveTarget->x() + dx, moveTarget->y() + dy);
            break;
        case Movable::MoveParent:
			QWidget *parentWidget = moveTarget->parentWidget();
			Q_ASSERT(parentWidget);
			parentWidget->move(parentWidget->x() + dx, parentWidget->y() + dy);
            break;
        }
    }
}

void Movable::targetReleaseEvent(QMouseEvent *e)
{
    if(this->isMove)
    {
        this->isMove = false;
        if (type == Movable::SignalMove)
			emit signalReleased();
	}
}
