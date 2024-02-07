#ifndef SUPPORTFUNCTIONS_H
#define SUPPORTFUNCTIONS_H

#include <QPoint>
#include <QPointF>
#include <QVector2D>


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

QPointF SegmentsCrossingPos(QPointF p1,QPointF p2,QPointF p3, QPointF p4)
{
    float L1, sin_alf, cos_alf, wsp1, wsp2, beta;
    bool flag_cross = false;
    QPointF CR;

    QPointF p1_copy = p1;
    QPointF p2_copy = p2;
    QPointF p3_copy = p3;
    QPointF p4_copy = p4;

    p1 = QPointF(0,0);

    p2-=p1_copy;
    p3-=p1_copy;
    p4-=p1_copy;

    L1 = sqrt(pow(p2.x(),2)+pow(p2.y(),2));
    if(L1>0)
    {
        sin_alf = p2.x()/L1;
        cos_alf = p2.y()/L1;
    }
    else
    {
        sin_alf = 0;
        cos_alf = 0;
    }

    p2 = QPointF(0,L1);

    wsp1 = p3.x()*cos_alf-p3.y()*sin_alf;
    wsp2 = p3.x()*cos_alf+p3.y()*sin_alf;
    p3 = QPointF(wsp1,wsp2);

    wsp1 = p4.x()*cos_alf-p4.y()*sin_alf;
    wsp2 = p4.x()*cos_alf+p4.y()*sin_alf;
    p4 = QPointF(wsp1,wsp2);

    if (p3.x() - p4.x() == 0) { // отрезок {P3,P4) параллелен {P0,P1)
        if( p3.x() == 0 && p4.x() == 0) {

            if( p3.y() >= 0 && p3.y() <= L1)
            {
                flag_cross = true;
                CR = p3_copy;
            }

            if(p4.y() >= 0 && p4.y() <= L1)
            {
                flag_cross = true;
                CR =p4_copy;
            }

            if((p3.y() < 0 && p4.y() > L1) || (p4.y() < 0 && p3.y() > L1))
            {
                flag_cross = true;
                CR = p1_copy;
            }
        }
    }
    else {
        beta = p3.x() / (p3.x() - p4.x());

        if (beta >= 0 && beta <= 1 )
        {

            CR = QPointF(0,p3.y() + (p4.y()-p3.y())*beta);

            if (CR.y() >= 0 && CR.y() <= L1)
            {

                flag_cross = true;
                wsp1 = CR.x()*cos_alf + CR.y()*sin_alf;
                wsp2 = CR.y()*cos_alf - CR.x()*sin_alf;
                CR = QPointF(wsp1,wsp2);
                CR = QPointF(CR.x() + p1_copy.x(),CR.y() + p1_copy.y());
            }
        }
    }

    if(flag_cross)
    {
        return CR;
    }
    return QPointF(0,0);

}

}

#endif // SUPPORTFUNCTIONS_H
