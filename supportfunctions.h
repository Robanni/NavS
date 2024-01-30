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

}

#endif // SUPPORTFUNCTIONS_H
