#ifndef MOVABLE_H
#define MOVABLE_H

#include <QMouseEvent>
#include <QRect>

class Movable : public QObject
{
    Q_OBJECT
public:
	enum MoveType{
		MoveParent = 0,
		SignalMove,
        MoveSelf,
	};
    explicit Movable(QWidget *parent = 0, MoveType type = Movable::MoveParent);
    virtual ~Movable();

    void setMoveTarget(QWidget *target);

    void setMoveTriggerArea(int from, int to);
    void setMoveTriggerArea(int to);
    void setMoveType(MoveType mt);

signals:
	void signalPressed(QPoint pressed);
    void signalMove(int dx, int dy);
	void signalReleased();

protected:
	bool eventFilter(QObject *obj, QEvent *event);


private:
	void targetPressEvent(QMouseEvent *);
	void targetMoveEvent(QMouseEvent *);
	void targetReleaseEvent(QMouseEvent *);

    QPoint  pressPoint;
    int     moveTriggerStart;
    int     moveTriggerEnd;
	QWidget *moveTarget;
    bool    isMove;

	MoveType type;
};

#endif // MOVABLE_H
