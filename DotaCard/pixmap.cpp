#include "pixmap.h"
#include <QDebug>

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
    connect(hide_pix, &QPropertyAnimation::finished, this, &Pixmap::finishedChangePhaseAnimation);

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
}

QRectF Pixmap::boundingRect() const
{
    return QRectF(0, 0, pixmap.width(), pixmap.height());
}

void Pixmap::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(0, 0, pixmap);
}

void Pixmap::setPixmap(QString filename)
{
    pixmap.load(filename);
}

void Pixmap::doShineAnimation()
{
    //  qDota->music->play("music/magic_active.wav");

    QPropertyAnimation *fade1 = new QPropertyAnimation(this,"opacity");
    fade1->setStartValue(0);
    fade1->setEndValue(1);
    fade1->setDuration(1000);
    QPropertyAnimation *fade2 = new QPropertyAnimation(this,"scale");
    fade2->setStartValue(0);
    fade2->setEndValue(1.2);
    fade2->setDuration(1000);
    QParallelAnimationGroup *group1 = new QParallelAnimationGroup;
    group1->addAnimation(fade1);
    group1->addAnimation(fade2);
    QPropertyAnimation *fade3 = new QPropertyAnimation(this,"opacity");
    fade3->setStartValue(1);
    fade3->setEndValue(0);
    fade3->setDuration(500);
    QPropertyAnimation *fade4 = new QPropertyAnimation(this,"scale");
    fade4->setStartValue(1.2);
    fade4->setEndValue(0);
    fade4->setDuration(500);
    QParallelAnimationGroup *group2 = new QParallelAnimationGroup;
    group2->addAnimation(fade3);
    group2->addAnimation(fade4);
    QSequentialAnimationGroup *group = new QSequentialAnimationGroup;
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
        setVisible(false);
        emit finishedEffect();
    }
}

void Pixmap::effect()
{
    id = startTimer(100);
}

void Pixmap::swordAnimation(QPointF p1, QPointF p2)
{
//  qDota->music->play("music/attack.wav");
    animation->setStartValue(p1);
    animation->setEndValue(p2);
    animation->start();
}
