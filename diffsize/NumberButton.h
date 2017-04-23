#ifndef NUMBERBUTTON_H
#define NUMBERBUTTON_H

#include <QPushButton>
#include <QMouseEvent>
#include <QPaintEvent>

class IconButton : public QPushButton
{
    Q_OBJECT
public:
    IconButton(QWidget *parent);
	void setNormalPixmap(const QString fileName);
	void setHoverPixmap(const QString fileName);
	void setCheckedPixmap(const QString fileName);
	void setPressedPixmap(const QString fileName);

private slots:
    void onToggled(bool checked);

protected:
	void enterEvent(QEvent *event) Q_DECL_OVERRIDE;
	void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;
	void mousePressEvent(QMouseEvent * event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent * event) Q_DECL_OVERRIDE;

private:
    void updateIcon();

    enum ButtonStatus{NORMAL, HOVER, PRESSED};
    ButtonStatus status;

    QString m_normalPixmap;
    QString m_hoverPixmap;
    QString m_checkedPixmap;
	QString m_pressedPixmap;
};

class NumberButton : public IconButton
{
    Q_OBJECT
public:
    NumberButton(QWidget *parent);

protected:
    void paintEvent(QPaintEvent *event);

protected:
    int m_number = 89;
    int m_fontSize = 8;

    int m_leftMargin = 0;
    int m_topMargin = 0;
};


class ChatNumberButton : public NumberButton
{
    Q_OBJECT
public:
    ChatNumberButton(QWidget *parent);

public slots:
    //void numberChanged(const EeoEngine::ContactsID& id);

};

class NoticeNumberButton : public NumberButton
{
    Q_OBJECT
public:
    NoticeNumberButton(QWidget *parent);

public slots:
    void numberChanged();

};


#endif //NUMBERBUTTON_H
