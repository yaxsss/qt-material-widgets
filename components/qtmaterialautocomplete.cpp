/* 功能：
 * 实时响应用户输入
 * 动态创建和销毁列表项以优化性能
 * 自适应内容宽度
 * material design风格呈现
 * 状态机管理显示/隐藏状态
 */
#include "qtmaterialautocomplete.h"
#include "qtmaterialautocomplete_p.h"
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QtWidgets/QVBoxLayout>
#include <QEvent>
#include <QTimer>
#include <QPainter>
#include <QDebug>
#include "qtmaterialautocomplete_internal.h"
#include "qtmaterialflatbutton.h"

/*!
 *  \class QtMaterialAutoCompletePrivate
 *  \internal
 */

/*!
 *  \internal
 */
QtMaterialAutoCompletePrivate::QtMaterialAutoCompletePrivate(QtMaterialAutoComplete *q)
    : QtMaterialTextFieldPrivate(q)
{
}

/*!
 *  \internal
 */
QtMaterialAutoCompletePrivate::~QtMaterialAutoCompletePrivate()
{
}

/*!
 *  \internal
 */
void QtMaterialAutoCompletePrivate::init()
{
    Q_Q(QtMaterialAutoComplete);

    menu         = new QWidget; // 菜单
    frame        = new QWidget; // 框架
    stateMachine = new QtMaterialAutoCompleteStateMachine(menu); // 状态机
    menuLayout   = new QVBoxLayout; // 菜单布局
    maxWidth     = 0; // 最大宽度

    // 设置父窗口
    menu->setParent(q->parentWidget());
    frame->setParent(q->parentWidget());

    // 安装事件过滤器
    menu->installEventFilter(q);
    frame->installEventFilter(q);

    // 设置阴影效果
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(11); // 模糊半径
    effect->setColor(QColor(0, 0, 0, 50)); // 颜色
    effect->setOffset(0, 3); // 偏移量

    frame->setGraphicsEffect(effect);
    frame->setVisible(false);

    menu->setLayout(menuLayout);
    menu->setVisible(false);

    menuLayout->setContentsMargins(0, 0, 0, 0);
    menuLayout->setSpacing(0);

    QObject::connect(q, SIGNAL(textEdited(QString)), q, SLOT(updateResults(QString)));

    stateMachine->start();
}

/*!
 *  \class QtMaterialAutoComplete
 */

QtMaterialAutoComplete::QtMaterialAutoComplete(QWidget *parent)
    : QtMaterialTextField(*new QtMaterialAutoCompletePrivate(this), parent)
{
    d_func()->init();
}

QtMaterialAutoComplete::~QtMaterialAutoComplete()
{
}

void QtMaterialAutoComplete::setDataSource(const QStringList &data)
{
    Q_D(QtMaterialAutoComplete);

    d->dataSource = data;
    update();
}
void QtMaterialAutoComplete::updateResults(QString text)
{
    Q_D(QtMaterialAutoComplete);

    QStringList results;
    QString trimmed(text.trimmed());
    // 如果文本不为空，则进行搜索
    if (!trimmed.isEmpty()) {
        QString lookup(trimmed.toLower());
        QStringList::iterator i;
        for (i = d->dataSource.begin(); i != d->dataSource.end(); ++i) {
            if (i->toLower().indexOf(lookup) != -1) {
                results.push_back(*i);
            }
        }
    }

    const int diff = results.length() - d->menuLayout->count();
    QFont font("Roboto", 12, QFont::Normal);

    if (diff > 0) {
        // 需要添加更多按钮
        for (int c = 0; c < diff; c++) {
            QtMaterialFlatButton *item = new QtMaterialFlatButton;
            item->setFont(font);
            item->setTextAlignment(Qt::AlignLeft);
            item->setCornerRadius(0);
            item->setHaloVisible(false);
            item->setFixedHeight(50);
            item->setOverlayStyle(Material::TintedOverlay);
            d->menuLayout->addWidget(item);
            item->installEventFilter(this);
        }
    } else if (diff < 0) {
        // 需要删除按钮
        for (int c = 0; c < -diff; c++) {
            QWidget *widget = d->menuLayout->itemAt(0)->widget();
            if (widget) {
                d->menuLayout->removeWidget(widget);
                delete widget;
            }
        }
    }

    QFontMetrics *fm = new QFontMetrics(font);
    d->maxWidth = 0;
    // 遍历结果，设置按钮文本和最大宽度
    for (int i = 0; i < results.count(); ++i) {
        QWidget *widget = d->menuLayout->itemAt(i)->widget();
        QtMaterialFlatButton *item;
        if ((item = static_cast<QtMaterialFlatButton *>(widget))) {
            QString text = results.at(i);
            QRect rect = fm->boundingRect(text);
            d->maxWidth = qMax(d->maxWidth, rect.width());
            item->setText(text);
        }
    }

    // 如果结果为空，则关闭菜单, 否则打开菜单
    if (!results.count()) {
        emit d->stateMachine->shouldClose();
    } else {
        emit d->stateMachine->shouldOpen();
    }

    d->menu->setFixedHeight(results.length()*50); // 设置菜单高度
    d->menu->setFixedWidth(qMax(d->maxWidth + 24, width())); // 设置菜单宽度
    d->menu->update(); // 更新菜单
}

bool QtMaterialAutoComplete::QtMaterialAutoComplete::event(QEvent *event)
{
    Q_D(QtMaterialAutoComplete);

    switch (event->type())
    {
    case QEvent::Move:
    case QEvent::Resize: {
        d->menu->move(pos() + QPoint(0, height() + 6));
        break;
    }
    // 1. 当组件的父窗口发生改变时
    // 2. 当组件被重新插入到不同的布局中时
    // 3. 当组件的父窗口被删除时
    case QEvent::ParentChange: {
        QWidget *widget = static_cast<QWidget *>(parent());
        if (widget) {
            d->menu->setParent(widget);
            d->frame->setParent(widget);
        }
        break;
    }
    default:
        break;
    }
    return QtMaterialTextField::event(event);
}
// 同步框架和菜单的位置以及处理显示层级
bool QtMaterialAutoComplete::eventFilter(QObject *watched, QEvent *event)
{
    Q_D(QtMaterialAutoComplete);

    if (d->frame == watched)
    {
        switch (event->type())
        {
        case QEvent::Paint: {
            // 绘制白色背景
            QPainter painter(d->frame);
            painter.fillRect(d->frame->rect(), Qt::white);
            break;
        }
        default:
            break;
        }
    }
    else if (d->menu == watched)
    {
        switch (event->type())
        {
        case QEvent::Resize:
        case QEvent::Move: {
            d->frame->setGeometry(d->menu->geometry()); // 同步移动frame
            break;
        }
        case QEvent::Show: {
            d->frame->show();
            d->menu->raise(); // 确保菜单在框架之上
            break;
        }
        case QEvent::Hide: {
            d->frame->hide(); // 同步隐藏框架
            break;
        }
        default:
            break;
        }
    }
    else
    {
        switch (event->type())
        {
        // 当用户选中一个列表项时，触发淡出动画，并设置文本
        case QEvent::MouseButtonPress: {
            emit d->stateMachine->shouldFade();
            QtMaterialFlatButton *widget;
            if ((widget = static_cast<QtMaterialFlatButton *>(watched))) {
                QString text(widget->text());
                setText(text);
                emit itemSelected(text);
            }
            break;
        }
        default:
            break;
        }
    }
    return QtMaterialTextField::eventFilter(watched, event);
}
