#ifndef SUPPORTFUNCTIONS_H
#define SUPPORTFUNCTIONS_H

#include <QPoint>
#include <QPointF>


namespace sf
{

float GetDistanceBetweenPoints(QPoint pointOne,QPoint pointTwo)
{
    float a,b;
    a = pointTwo.x() - pointOne.x();
    b = pointTwo.y() - pointOne.y();

    return std::sqrt(std::pow(a,2) + std::pow(b,2));
}

float GetDistanceBetweenPoints(QPointF pointOne,QPointF pointTwo)
{
    float a,b;
    a = pointTwo.x() - pointOne.x();
    b = pointTwo.y() - pointOne.y();

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

}

#endif // SUPPORTFUNCTIONS_H
