#ifndef LEFTBAR_H
#define LEFTBAR_H

#include <QWidget>
#include <QBoxLayout>

class LeftBar : public QWidget
{
    Q_OBJECT
public:
    explicit LeftBar(QWidget *parent = 0);

signals:
    void avatarButtonClicked();
    void chatButtonClicked();
    void contactButtonClicked();
    void courseButtonClicked();
    void cloudButtonClicked();
    void noticeCenterButtonClicked();
    void boardEditorButtonClicked();
    void deviceCheckButtonClicked();
    void settingButtonClicked();

public slots:

private:
    QWidget * createAvatarWidget();
    QWidget * createMiddleWidget();
    QWidget * createBottomWidget();
};

#endif // LEFTBAR_H
