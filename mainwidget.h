#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);

signals:

public slots:

private slots:
    void on_pushButton_0_0_clicked();
    void on_pushButton_0_1_clicked();
    void on_pushButton_0_2_clicked();
    void on_pushButton_0_3_clicked();
    void on_pushButton_0_4_clicked();
    void on_pushButton_0_5_clicked();

    void on_pushButton_1_0_clicked();
    void on_pushButton_1_1_clicked();
    void on_pushButton_1_2_clicked();
    void on_pushButton_1_3_clicked();
    void on_pushButton_1_4_clicked();
    void on_pushButton_1_5_clicked();

	void on_pushButton_2_0_clicked();
	void on_pushButton_2_1_clicked();
	void on_pushButton_2_2_clicked();
	void on_pushButton_2_3_clicked();
	void on_pushButton_2_4_clicked();
	void on_pushButton_2_5_clicked();

private:
    QGridLayout * initGridLayout();
    QWidget * m_pWidget = NULL;
};

#endif // MAINWIDGET_H
