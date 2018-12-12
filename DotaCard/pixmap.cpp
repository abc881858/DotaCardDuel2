#include "pixmap.h"
#include <QDebug>
#include <utility>

Pixmap::Pixmap(const QString &filename, bool center_as_origin)
    : pixmap(filename)
{
    if(center_as_origin)
    {
        setTransformOriginPoint(pixmap.width()/2, pixmap.height()/2);
    }

    hide_pix = new QPropertyAnimation(this,"opacity");
    hide_pix->setStartValue(1);
    hide_pix->setEndValue(0);
    hide_pix->setDuration(200);
    connect(hide_pix, &QPropertyAnimation::finished, [=](){
        this->hide();
    });

//    setTransformationMode(Qt::SmoothTransformation);
    z = 1;

    action_start = new QPropertyAnimation(this,"pos");
    action_start->setEndValue(QPointF(266,242));
    action_start->setDuration(1200);
    action_start->setEasingCurve(QEasingCurve::OutBounce);
    connect(action_start, &QPropertyAnimation::finished, this, &Pixmap::finishedActionAnimation);

    animation = new QPropertyAnimation(this, "pos");
    animation->setDuration(300);
    animation->setEasingCurve(QEasingCurve::Linear);
    connect(animation, &QPropertyAnimation::finished, this, &Pixmap::finishedSwordAnimation);

    fadeEquip = new QPropertyAnimation(this,"opacity");
    fadeEquip->setStartValue(0);
    fadeEquip->setKeyValueAt(0.5,0.7);
    fadeEquip->setEndValue(0);
    fadeEquip->setDuration(1000);
    fadeEquip->setLoopCount(-1);
}

Pixmap::Pixmap(QPixmap q)
{
    this->pixmap=std::move(q);
}

QRectF Pixmap::boundingRect() const
{
    return {0, 0, qreal(pixmap.width()), qreal(pixmap.height())};
}

void Pixmap::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(0, 0, pixmap);
}

void Pixmap::setPixmap(const QString &filename)
{
    pixmap.load(filename);
}

void Pixmap::doShineAnimation()
{
    //  qDota->music->play("music/magic_active.wav");

    auto *fade1 = new QPropertyAnimation(this,"opacity");
    fade1->setStartValue(0);
    fade1->setEndValue(1);
    fade1->setDuration(500);
    auto *fade2 = new QPropertyAnimation(this,"scale");
    fade2->setStartValue(0);
    fade2->setEndValue(1.2);
    fade2->setDuration(500);
    auto *group1 = new QParallelAnimationGroup;
    group1->addAnimation(fade1);
    group1->addAnimation(fade2);
    auto *fade3 = new QPropertyAnimation(this,"opacity");
    fade3->setStartValue(1);
    fade3->setEndValue(0);
    fade3->setDuration(500);
    auto *fade4 = new QPropertyAnimation(this,"scale");
    fade4->setStartValue(1.2);
    fade4->setEndValue(0);
    fade4->setDuration(500);
    auto *group2 = new QParallelAnimationGroup;
    group2->addAnimation(fade3);
    group2->addAnimation(fade4);
    auto *group = new QSequentialAnimationGroup;
    group->addAnimation(group1);
    group->addAnimation(group2);
    connect(group, &QParallelAnimationGroup::finished, this, &Pixmap::finishedDoShineAnimation);

    group->start(QAbstractAnimation::DeleteWhenStopped);
}

void Pixmap::changePhaseAnimation()
{
    hide_pix->start();
}

void Pixmap::actionAnimation()
{
    action_start->start();
}

void Pixmap::timerEvent(QTimerEvent *)
{
    ++z;
    pixmap.load(QString("phase_name/e_ba_b%1.png").arg(z));
    update();

    if(z==8)
    {
        z = 1;
        killTimer(id);
        hide();
    }
}

void Pixmap::effect()
{
    show();
    id = startTimer(100);
}

void Pixmap::swordAnimation(QPointF p1, QPointF p2)
{
//  qDota->music->play("music/attack.wav");
    animation->setStartValue(p1);
    animation->setEndValue(p2);
    animation->start();
}

void Pixmap::doEquipAnimation(QPointF positionFrom, QPointF positionTo)
{
    auto *fade1 = new QPropertyAnimation(this,"opacity");
    fade1->setStartValue(1);
    fade1->setEndValue(0);
    fade1->setDuration(1000);
    fade1->setEasingCurve(QEasingCurve::InCirc);

    auto *fade2 = new QPropertyAnimation(this,"scale");
    fade2->setStartValue(1);
    fade2->setKeyValueAt(0.5,2);
    fade2->setEndValue(1);
    fade2->setDuration(1000);

    auto *fade3 = new QPropertyAnimation(this,"pos");
    fade3->setStartValue(positionFrom);
    fade3->setEndValue(positionTo);
    fade3->setDuration(1000);
    fade3->setEasingCurve(QEasingCurve::InBack);

    auto *group = new QParallelAnimationGroup;//并行动画
    group->addAnimation(fade1);
    group->addAnimation(fade2);
    group->addAnimation(fade3);
    group->start(QAbstractAnimation::DeleteWhenStopped);

    connect(group, &QParallelAnimationGroup::finished, this, &Pixmap::finishedEquipAnimation);
}

void Pixmap::doEquipHoverAnimation()
{
    fadeEquip->start();
}

void Pixmap::doneEquipHoverAnimation()
{
    fadeEquip->stop();
}
