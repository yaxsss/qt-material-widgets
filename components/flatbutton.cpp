#include "flatbutton.h"
#include <QPainter>
#include <QMouseEvent>
#include <QStylePainter>
#include <QStyleOption>
#include <QApplication>
#include <QPalette>
#include <QDebug>
#include "lib/style.h"
#include "lib/rippleoverlay.h"

#include "flatbutton_p.h"

FlatButton::FlatButton(QWidget *parent)
    : QPushButton(parent),
      d_ptr(new FlatButtonPrivate(this))
{
}

FlatButton::FlatButton(const QString &text, QWidget *parent)
    : QPushButton(parent),
      d_ptr(new FlatButtonPrivate(this))
{
    setText(text);
}

FlatButton::~FlatButton()
{
}

void FlatButton::setRole(Material::Role role)
{
    Q_D(FlatButton);

    d->role = role;

    switch (role)
    {
    case Material::Primary:
        d->setTextColor("primary1");
        break;
    case Material::Secondary:
        d->setTextColor("accent1");
        break;
    default:
        d->setTextColor("text");
        break;
    }
    update();
}

void FlatButton::resizeEvent(QResizeEvent *event)
{
    Q_D(FlatButton);

    if (d->ripple) {
        d->ripple->setGeometry(rect());
    }

    QPushButton::resizeEvent(event);
}

void FlatButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QStylePainter painter(this);

    QStyleOptionButton option;
    initStyleOption(&option);
    option.features |= QStyleOptionButton::Flat;

    painter.drawControl(QStyle::CE_PushButtonLabel, option);

    if (isEnabled() && testAttribute(Qt::WA_Hover) && underMouse())
    {
        QPainter painter(this);
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        painter.setOpacity(0.1);
        painter.fillRect(rect(), brush);
    }

#ifdef DEBUG_LAYOUT
    QPainter debug(this);
    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(2);
    debug.setPen(pen);
    debug.drawRect(rect());
#endif
}

void FlatButton::mousePressEvent(QMouseEvent *event)
{
    Q_D(FlatButton);

    d->ripple->addRipple(event->pos());

    QPushButton::mousePressEvent(event);
}

void FlatButton::enterEvent(QEvent *event)
{
    update();

    QPushButton::enterEvent(event);
}

void FlatButton::leaveEvent(QEvent *event)
{
    update();

    QPushButton::leaveEvent(event);
}
