#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QStackedWidget>
#include "qtmaterialtabs.h"
#include "qtmaterialappbar.h"
#include "qtmaterialtextfield.h"
#include "qtmaterialraisedbutton.h"
#include "qtmaterialflatbutton.h"
#include "captchawidget.h"

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);

private slots:
    void onLoginClicked();
    void onQuickLoginClicked();
    void onCaptchaRefresh();
    
private:
    void setupUi();
    void initializeTab();
    void setupPasswordPage(QWidget *page);
    void setupSMSPage(QWidget *page);
    void setupQuickLogin();
    
private:
    QtMaterialTabs *m_tabWidget;
    QStackedWidget *m_tabContent;
    QtMaterialTextField *m_accountField;
    QtMaterialTextField *m_passwordField;
    QtMaterialTextField *m_captchaField;
    CaptchaWidget *m_captchaWidget;
    QtMaterialRaisedButton *m_loginButton;
    QtMaterialTextField *m_phoneField;
    QtMaterialTextField *m_smsField;
    QtMaterialRaisedButton *m_smsButton;
    QtMaterialRaisedButton *m_smsLoginButton;
    QtMaterialFlatButton *m_quickLoginButton;
};
#endif