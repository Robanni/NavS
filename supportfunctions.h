#ifndef SUPPORTFUNCTIONS_H
#define SUPPORTFUNCTIONS_H

#include <QPoint>
#include <QPointF>
#include <QVector2D>
#include <QDebug>


namespace sf
{

float GetDistanceBetweenPoints(QPoint p1,QPoint p2)
{
    float a,b;
    a = p2.x() - p1.x();
    b = p2.y() - p1.y();

    return std::sqrt(std::pow(a,2) + std::pow(b,2));
}

float GetDistanceBetweenPoints(QPointF p1,QPointF p2)
{
    float a,b;
    a = p2.x() - p1.x();
    b = p2.y() - p1.y();

    return std::sqrt(std::pow(a,2) + std::pow(b,2));
}
QPointF GetNormalPointTwo(QPointF p1,QPointF p2,bool LeftRight)
{
    int i;
    if(LeftRight) i=1;  else i=-1;

    float x = p1.x()+(p2.y()-p1.y())*i;
    float y = p1.y()+(p1.x()-p2.x())*i;

    return QPointF(x,y);
}
QPointF GetUnitVecPointTwo(QPointF p1, QPointF p2)
{
    float x = p2.x() - p1.x();
    float y = p2.y() - p1.y();

    float mod = sqrt(pow(x,2)+pow(y,2));

    x /= mod;
    y /= mod;

    return QPointF(x+p1.x(),y+p1.y());
}

bool RangeIntersection(float r1,float r2,float r3,float r4)
{
    if(r1>r2) std::swap(r1,r2);
    if(r3>r4) std::swap(r3,r4);

    return std::max(r1,r3)<= std::min(r2,r4);
}

QPointF SegmentsCrossingPos(QPointF p1,QPointF p2,QPointF p3, QPointF p4)
{

    if(RangeIntersection(p1.x(),p2.x(),p3.x(),p4.x())&&RangeIntersection(p1.y(),p2.y(),p3.y(),p4.y()))
    {

        QVector2D v(p2-p1);
        QVector2D v1(p3-p1);
        QVector2D v2(p4-p1);

        float Z1 = v1.x()*v.y() - v.x()*v1.y();
        float Z2 = v2.x()*v.y() - v.x()*v2.y();

        if(Z1*Z2>0)return QPointF(0,0);

        float px = p3.x()+(p4.x()-p3.x())*(abs(Z1)/abs(Z2-Z1));
        float py = p3.y()+(p4.y()-p3.y())*(abs(Z1)/abs(Z2-Z1));

        return QPointF(px,py);
    }

    return QPointF(0,0);
}


}

#endif // SUPPORTFUNCTIONS_H
