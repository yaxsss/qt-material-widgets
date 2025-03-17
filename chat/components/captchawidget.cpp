#include "captchawidget.h"
#include <QHBoxLayout>

CaptchaWidget::CaptchaWidget(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(4);
    
    m_imageButton = new QPushButton(this);
    m_imageButton->setFixedSize(120, 35);
    m_imageButton->setStyleSheet(
        "QPushButton {"
        "   border: 1px solid #ddd;"
        "   border-radius: 2px;"
        "}"
    );
    
    m_refreshButton = new QPushButton("刷新", this);
    m_refreshButton->setFixedSize(40, 35);
    m_refreshButton->setStyleSheet(
        "QPushButton {"
        "   color: #2196F3;"
        "   border: none;"
        "   font-size: 13px;"
        "}"
        "QPushButton:hover {"
        "   color: #42A5F5;"
        "}"
    );
    
    layout->addWidget(m_imageButton);
    layout->addWidget(m_refreshButton);
    layout->addStretch();
    
    connect(m_refreshButton, &QPushButton::clicked,
            this, &CaptchaWidget::refreshClicked);
}