#include "loginwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

LoginWindow::LoginWindow(QWidget *parent)
    : QWidget(parent)
{
    setupUi();
}

void LoginWindow::setupUi()
{
    setFixedSize(1024, 768);
    setStyleSheet("background-color: #3498db;");
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    QHBoxLayout *centerLayout = new QHBoxLayout;
    mainLayout->addLayout(centerLayout);
    
    centerLayout->addStretch();
    
    QWidget *container = new QWidget;
    container->setFixedWidth(400);
    centerLayout->addWidget(container);
    
    QVBoxLayout *containerLayout = new QVBoxLayout(container);
    containerLayout->setContentsMargins(0, 50, 0, 50);
    
    m_tabWidget = new QTabWidget;
    containerLayout->addWidget(m_tabWidget);
    
    centerLayout->addStretch();
    
    setupQuickLogin();
    
    initializeTab();
}

void LoginWindow::setupPasswordPage(QWidget *page)
{
    QVBoxLayout *layout = new QVBoxLayout(page);
    layout->setSpacing(16);
    
    m_accountField = new QtMaterialTextField;
    m_accountField->setLabel("请输入账户名");
    m_accountField->setPlaceholderText("手机号请加入地区号");
    
    m_passwordField = new QtMaterialTextField;
    m_passwordField->setLabel("请输入密码");
    m_passwordField->setEchoMode(QLineEdit::Password);
    
    QHBoxLayout *captchaLayout = new QHBoxLayout;
    m_captchaField = new QtMaterialTextField;
    m_captchaField->setLabel("请输入图形码");
    m_captchaWidget = new CaptchaWidget;
    
    captchaLayout->addWidget(m_captchaField);
    captchaLayout->addWidget(m_captchaWidget);
    
    m_loginButton = new QtMaterialRaisedButton("登录");
    m_loginButton->setFixedHeight(36);
    m_loginButton->setBackgroundColor(QColor("#2196F3"));
    m_loginButton->setForegroundColor(Qt::white);
    
    layout->addWidget(m_accountField);
    layout->addWidget(m_passwordField);
    layout->addLayout(captchaLayout);
    layout->addWidget(m_loginButton);
    layout->addStretch();
    
    connect(m_loginButton, &QtMaterialRaisedButton::clicked,
            this, &LoginWindow::onLoginClicked);
    connect(m_captchaWidget, &CaptchaWidget::refreshClicked,
            this, &LoginWindow::onCaptchaRefresh);
}

void LoginWindow::setupSMSPage(QWidget *page)
{
    QVBoxLayout *layout = new QVBoxLayout(page);
    layout->setSpacing(16);
    
    m_phoneField = new QtMaterialTextField;
    m_phoneField->setLabel("请输入手机号");
    
    QHBoxLayout *smsLayout = new QHBoxLayout;
    m_smsField = new QtMaterialTextField;
    m_smsField->setLabel("请输入短信验证码");
    
    m_smsButton = new QtMaterialRaisedButton("获取验证码");
    m_smsButton->setFixedSize(100, 36);
    m_smsButton->setBackgroundColor(QColor("#2196F3"));
    m_smsButton->setForegroundColor(Qt::white);
    
    smsLayout->addWidget(m_smsField);
    smsLayout->addWidget(m_smsButton);
    
    m_smsLoginButton = new QtMaterialRaisedButton("登录");
    m_smsLoginButton->setFixedHeight(36);
    m_smsLoginButton->setBackgroundColor(QColor("#2196F3"));
    m_smsLoginButton->setForegroundColor(Qt::white);
    
    layout->addWidget(m_phoneField);
    layout->addLayout(smsLayout);
    layout->addWidget(m_smsLoginButton);
    layout->addStretch();
}

void LoginWindow::setupQuickLogin()
{
    QHBoxLayout *quickLoginLayout = new QHBoxLayout;
    quickLoginLayout->setAlignment(Qt::AlignRight);
    
    m_quickLoginButton = new QtMaterialFlatButton("快速登录");
    m_quickLoginButton->setForegroundColor(QColor("#2196F3"));
    
    quickLoginLayout->addWidget(m_quickLoginButton);
    
    connect(m_quickLoginButton, &QtMaterialFlatButton::clicked,
            this, &LoginWindow::onQuickLoginClicked);
}

void LoginWindow::initializeTab()
{
    QWidget *pwdPage = new QWidget;
    setupPasswordPage(pwdPage);
    m_tabWidget->addTab(pwdPage, "密码登录");
    
    QWidget *smsPage = new QWidget;
    setupSMSPage(smsPage);
    m_tabWidget->addTab(smsPage, "短信登录");
}

void LoginWindow::onLoginClicked()
{
    // TODO: 实现登录逻辑
}

void LoginWindow::onQuickLoginClicked()
{
    // TODO: 实现快速登录逻辑
}

void LoginWindow::onCaptchaRefresh()
{
    // TODO: 实现验证码刷新逻辑
}