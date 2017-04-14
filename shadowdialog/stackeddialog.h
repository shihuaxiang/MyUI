#ifndef STACKEDDIALOG_H
#define STACKEDDIALOG_H

#include <QDialog>

namespace Ui {
class StackedDialog;
}

class TitleBar;

class StackedDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StackedDialog(QWidget *parent = 0);
    ~StackedDialog();

private slots:
    void on_buttonBox_accepted();

private:
    void initMainLayout();
    TitleBar * initTitlebar();

private:
    Ui::StackedDialog *ui;
};

#endif // STACKEDDIALOG_H
