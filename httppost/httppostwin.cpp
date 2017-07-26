#include "httppostwin.h"
#include "ui_httppostwin.h"

HttpPostWin::HttpPostWin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HttpPostWin)
{
    ui->setupUi(this);

    nam = new QNetworkAccessManager(this);
    connect(ui->pushButton_submit,
            SIGNAL(clicked()),
            this,
            SLOT(on_pushButton_submit_clicked()));
    connect(ui->pushButton_clear,
            SIGNAL(clicked()),
            this,
            SLOT(on_pushButton_clear_clicked()));
    connect(nam,
            SIGNAL(finished(QNetworkReply*)),
            this,
            SLOT(finished(QNetworkReply*)));
}

HttpPostWin::~HttpPostWin()
{
    delete ui;
}

void HttpPostWin::on_pushButton_clear_clicked()
{
    ui->lineEdit_url->setText("http://");
    ui->pTextEdit_paras->clear();
    ui->radioButton_u->setChecked(true);
    ui->textEdit_result->clear();
}

void HttpPostWin::on_pushButton_submit_clicked()
{
    if(ui->pushButton_submit->isEnabled())
        ui->pushButton_submit->setEnabled(false);
    if(ui->pushButton_clear->isEnabled())
        ui->pushButton_clear->setEnabled(false);
    QString url=ui->lineEdit_url->text();
    QString paras=ui->pTextEdit_paras->toPlainText();
    qDebug()<<paras;
    QByteArray post_data;
    post_data.append(paras.toLatin1());
    QNetworkRequest request= QNetworkRequest(QUrl(url));
    request.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
    if(post_data.isEmpty())
    {
        nam->get(request);
    }
    else
    {
        nam->post(request,post_data);
    }
}

void HttpPostWin::finished(QNetworkReply *reply)
{
//    if(ui->radioButton_u->isChecked())
//        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
//    else
//        QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));

    if(reply->error() == QNetworkReply::NoError)
    {
        ui->textEdit_result->setText(QObject::tr(reply->readAll()));
    }
    else
    {
        ui->textEdit_result->setPlainText(reply->errorString());
    }
    if(!ui->pushButton_submit->isEnabled())
        ui->pushButton_submit->setEnabled(true);
    if(!ui->pushButton_clear->isEnabled())
        ui->pushButton_clear->setEnabled(true);
}
