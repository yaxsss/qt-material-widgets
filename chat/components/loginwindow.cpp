#include "loginwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <qwidget.h>

LoginWindow::LoginWindow(QWidget *parent)
    : QWidget(parent)
{
    setupUi();
}

void LoginWindow::setupUi()
{
    // 设置窗口大小
    setFixedSize(1024, 768);
    
    // 创建主布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(0);  // 移除边距
    
    // 创建一个 AppBar 作为背景
    // 创建带LOGO的AppBar
    QtMaterialAppBar *appBar = new QtMaterialAppBar;
    QHBoxLayout *appBarLayout = new QHBoxLayout(appBar);
    QLabel *logo = new QLabel("Chat App");
    logo->setStyleSheet("QLabel { color: white; font-size: 24px; font-weight: 500; }");
    appBarLayout->addWidget(logo);
    appBarLayout->addStretch();
    appBar->setBackgroundColor(QColor("#2196F3"));
    appBar->setFixedSize(this->size());
    
    // 创建中央白色容器
    QWidget *centerCard = new QWidget;
    centerCard->setFixedSize(400, 500);
    centerCard->setStyleSheet("background-color: white; border-radius: 10px;");

    // 使用布局让卡片居中
    QHBoxLayout *centerLayout = new QHBoxLayout;
    centerLayout->addStretch();
    centerLayout->addWidget(centerCard);
    centerLayout->addStretch();
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->addLayout(centerLayout, 1);
    
    // 卡片的布局
    QVBoxLayout *cardLayout = new QVBoxLayout(centerCard);
    cardLayout->setContentsMargins(20, 20, 20, 20);
    
    // 快速登录按钮
    QHBoxLayout *quickLoginLayout = new QHBoxLayout;
    quickLoginLayout->setAlignment(Qt::AlignRight);
    m_quickLoginButton = new QtMaterialFlatButton("快速登录");
    m_quickLoginButton->setForegroundColor(QColor("#2196F3"));
    quickLoginLayout->addWidget(m_quickLoginButton);
    cardLayout->addLayout(quickLoginLayout);
    
    // 标签页
    m_tabWidget = new QtMaterialTabs;
    m_tabWidget->setFixedHeight(50);  // 调整标签栏高度
    cardLayout->addWidget(m_tabWidget);
    
    // 标签页内容容器
    m_tabContent = new QStackedWidget;
    cardLayout->addWidget(m_tabContent);
    
    initializeTab();
    
    // 连接标签切换信号
    connect(m_tabWidget, &QtMaterialTabs::currentChanged,
            m_tabContent, &QStackedWidget::setCurrentIndex);
}

void LoginWindow::setupPasswordPage(QWidget *page)
{
    QVBoxLayout *layout = new QVBoxLayout(page);
    layout->setSpacing(20);
    
    // 账号输入框
    m_accountField = new QtMaterialTextField;
    m_accountField->setLabel("请输入账户名");
    m_accountField->setPlaceholderText("手机号请加入地区号");
    m_accountField->setMinimumWidth(300);
    m_accountField->setTextColor(QColor("#333333"));
    m_accountField->setInkColor(QColor("#2196F3"));
    m_accountField->setLabelColor(QColor("#666666"));
    
    // 密码输入框
    m_passwordField = new QtMaterialTextField;
    m_passwordField->setLabel("请输入密码");
    m_passwordField->setEchoMode(QLineEdit::Password);
    m_passwordField->setTextColor(QColor("#333333"));
    m_passwordField->setInkColor(QColor("#2196F3"));
    m_passwordField->setLabelColor(QColor("#666666"));
    
    // 验证码布局
    QHBoxLayout *captchaLayout = new QHBoxLayout;
    captchaLayout->setSpacing(10);
    
    m_captchaField = new QtMaterialTextField;
    m_captchaField->setLabel("请输入图形码");
    m_captchaField->setMinimumWidth(200);
    m_captchaField->setTextColor(QColor("#333333"));
    m_captchaField->setInkColor(QColor("#2196F3"));
    m_captchaField->setLabelColor(QColor("#666666"));
    
    // 验证码刷新按钮
    QtMaterialFlatButton *refreshButton = new QtMaterialFlatButton("刷新");
    refreshButton->setForegroundColor(QColor("#2196F3"));
    
    m_captchaWidget = new CaptchaWidget;
    m_captchaWidget->setFixedSize(100, 36);
    
    captchaLayout->addWidget(m_captchaField);
    captchaLayout->addWidget(m_captchaWidget);
    captchaLayout->addWidget(refreshButton);
    
    // 登录按钮
    m_loginButton = new QtMaterialRaisedButton("登录");
    m_loginButton->setFixedHeight(36);
    m_loginButton->setBackgroundColor(QColor("#2196F3"));
    m_loginButton->setForegroundColor(Qt::white);
    m_loginButton->setOverlayColor(Qt::white);
    m_loginButton->setRippleStyle(Material::CenteredRipple);
    
    layout->addWidget(m_accountField);
    layout->addWidget(m_passwordField);
    layout->addLayout(captchaLayout);
    layout->addWidget(m_loginButton);
    layout->addStretch();
    
    connect(m_loginButton, &QtMaterialRaisedButton::clicked,
            this, &LoginWindow::onLoginClicked);
    connect(refreshButton, &QtMaterialFlatButton::clicked,
            this, &LoginWindow::onCaptchaRefresh);
}

void LoginWindow::setupSMSPage(QWidget *page)
{
    QVBoxLayout *layout = new QVBoxLayout(page);
    layout->setSpacing(20);
    
    // 手机号输入框
    m_phoneField = new QtMaterialTextField;
    m_phoneField->setLabel("请输入手机号");
    m_phoneField->setTextColor(QColor("#333333"));
    m_phoneField->setInkColor(QColor("#2196F3"));
    m_phoneField->setLabelColor(QColor("#666666"));
    
    // 验证码布局
    QHBoxLayout *smsLayout = new QHBoxLayout;
    smsLayout->setSpacing(10);
    
    m_smsField = new QtMaterialTextField;
    m_smsField->setLabel("请输入短信验证码");
    m_smsField->setTextColor(QColor("#333333"));
    m_smsField->setInkColor(QColor("#2196F3"));
    m_smsField->setLabelColor(QColor("#666666"));
    
    // 获取验证码按钮
    m_smsButton = new QtMaterialRaisedButton("获取验证码");
    m_smsButton->setFixedSize(100, 36);
    m_smsButton->setBackgroundColor(QColor("#2196F3"));
    m_smsButton->setForegroundColor(Qt::white);
    m_smsButton->setOverlayColor(Qt::white);
    m_smsButton->setRippleStyle(Material::CenteredRipple);
    
    smsLayout->addWidget(m_smsField);
    smsLayout->addWidget(m_smsButton);
    
    // 登录按钮
    m_smsLoginButton = new QtMaterialRaisedButton("登录");
    m_smsLoginButton->setFixedHeight(36);
    m_smsLoginButton->setBackgroundColor(QColor("#2196F3"));
    m_smsLoginButton->setForegroundColor(Qt::white);
    m_smsLoginButton->setOverlayColor(Qt::white);
    m_smsLoginButton->setRippleStyle(Material::CenteredRipple);
    
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
    // 添加标签
    m_tabWidget->addTab("密码登录");
    m_tabWidget->addTab("短信登录");
    m_tabWidget->setBackgroundColor(Qt::white);
    m_tabWidget->setTextColor(QColor("#666666"));
    // m_tabWidget->setSelectedTextColor(QColor("#2196F3"));
    m_tabWidget->setInkColor(QColor("#2196F3"));
    
    // 创建并添加页面
    QWidget *pwdPage = new QWidget;
    setupPasswordPage(pwdPage);
    m_tabContent->addWidget(pwdPage);
    
    QWidget *smsPage = new QWidget;
    setupSMSPage(smsPage);
    m_tabContent->addWidget(smsPage);
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