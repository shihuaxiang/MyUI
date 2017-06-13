#ifndef CALENDARWIDGET_H
#define CALENDARWIDGET_H

#include <QWidget>

namespace Ui {
class CalendarWidget;
}

class CalendarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CalendarWidget(QWidget *parent = 0);
    ~CalendarWidget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::CalendarWidget *ui;
};

#endif // CALENDARWIDGET_H
