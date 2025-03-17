#ifndef CAPTCHAWIDGET_H
#define CAPTCHAWIDGET_H

#include <QWidget>
#include <QPushButton>

class CaptchaWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CaptchaWidget(QWidget *parent = nullptr);
    
signals:
    void refreshClicked();
    
private:
    QPushButton *m_imageButton;
    QPushButton *m_refreshButton;
};

#endif