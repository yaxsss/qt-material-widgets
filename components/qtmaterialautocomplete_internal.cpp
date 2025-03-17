#include "qtmaterialautocomplete_internal.h"
#include <QSignalTransition>
#include <QPropertyAnimation>
#include <QtWidgets/QGraphicsOpacityEffect>
#include <QDebug>

/*!
 *  \class QtMaterialAutoCompleteStateMachine
 *  \internal
 */

/*!
 *  \internal
 */
QtMaterialAutoCompleteStateMachine::QtMaterialAutoCompleteStateMachine(QWidget *menu)
    : QStateMachine(menu),
      m_menu(menu),
      m_closedState(new QState),
      m_openState(new QState),
      m_closingState(new QState)
{
    Q_ASSERT(menu);

    addState(m_closedState);
    addState(m_openState);
    addState(m_closingState);
    setInitialState(m_closedState);

    QSignalTransition *transition;
    // 从关闭状态转换到打开状态
    transition = new QSignalTransition(this, SIGNAL(shouldOpen()));
    transition->setTargetState(m_openState);
    m_closedState->addTransition(transition);

    // 从打开状态转换到关闭状态
    transition = new QSignalTransition(this, SIGNAL(shouldClose()));
    transition->setTargetState(m_closedState);
    m_openState->addTransition(transition);

    // 从打开状态转换到正在关闭状态（带渐变效果)
    transition = new QSignalTransition(this, SIGNAL(shouldFade()));
    transition->setTargetState(m_closingState);
    m_openState->addTransition(transition);

    // 设置菜单的可见性
    m_closedState->assignProperty(menu, "visible", false);
    m_openState->assignProperty(menu, "visible", true);

    // 设置透明效果
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect;
    menu->setGraphicsEffect(effect);

    // 设置菜单的透明度
    m_openState->assignProperty(effect, "opacity", 1);
    m_closingState->assignProperty(effect, "opacity", 0);
    m_closedState->assignProperty(effect, "opacity", 0);

    QPropertyAnimation *animation;

    animation = new QPropertyAnimation(effect, "opacity", this);
    animation->setDuration(240);
    // 动画设置成为状态机的默认动画
    // 这样实现的效果是：
    // 菜单打开时：透明度从0平滑过渡到1，用时240ms
    // 菜单关闭时：透明度从1平滑过渡到0，用时240ms
    // 创造出流畅的淡入淡出效果，而不是生硬的显示/隐藏
    addDefaultAnimation(animation);

    // 这是一种特殊的状态转换，它监听动画的finished信号
    // 当动画完成时，状态机自动从m_closingState转换到m_closedState
    // 确保动画和状态转换的完美配合，保证不会卡在中间状态
    transition = new QSignalTransition(animation, SIGNAL(finished()));
    transition->setTargetState(m_closedState);
    m_closingState->addTransition(transition);
}

/*!
 *  \internal
 */
QtMaterialAutoCompleteStateMachine::~QtMaterialAutoCompleteStateMachine()
{
}
