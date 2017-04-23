#ifndef CUSTOMDIALOG_H
#define CUSTOMDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>

class TitleBar;
class QCustomLineEdit;

class CustomDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CustomDialog(QWidget *parent = 0);
    ~CustomDialog();

private slots:
    void onChecked(bool bChecked);

private:
    void        initMainLayout();
    TitleBar *  initTitlebar();
    QLayout *   initAccountRegion();
    QLayout *   initPwdRegion();
    QLayout *   initAgreementRegion();
    QLayout *   initButtonRegion();

    QWidget *centralWidget;
    QDialogButtonBox *buttonBox;

    QComboBox*    m_pComboBoxZone = NULL;
    QCustomLineEdit*    m_pLineEditAccount = NULL;
    QLabel*             m_pLineAccount = NULL;

    QCustomLineEdit*    m_pLineEditPwd = NULL;
    QLabel*             m_pLinePwd = NULL;

    QPushButton*        m_pBtnRegister = NULL;
};

#endif // CUSTOMDIALOG_H
