#ifndef HTTPPOSTWIN_H
#define HTTPPOSTWIN_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTextCodec>
#include <QtDebug>

namespace Ui {
class HttpPostWin;
}

class HttpPostWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit HttpPostWin(QWidget *parent = 0);
    ~HttpPostWin();

private slots:
    void on_pushButton_clear_clicked();

    void on_pushButton_submit_clicked();

    void finished(QNetworkReply *reply);

private:
    Ui::HttpPostWin *ui;
    QNetworkAccessManager *nam;
};

#endif // HTTPPOSTWIN_H
