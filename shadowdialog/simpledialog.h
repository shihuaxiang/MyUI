#ifndef SIMPLEDIALOG_H
#define SIMPLEDIALOG_H

#include <QDialog>

class TitleBar;

namespace Ui {
class SimpleDialog;
}

class SimpleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SimpleDialog(QWidget *parent = 0);
    ~SimpleDialog();

private:
    void initMainLayout();
    TitleBar * initTitlebar();

private:
    Ui::SimpleDialog *ui;
};

#endif // SIMPLEDIALOG_H
