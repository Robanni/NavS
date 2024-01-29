#include "drawingplane.h"

DrawingPlane::DrawingPlane(QWidget *parent)
    : QWidget{parent}
{
    resize(10000,10000);
     _tractor.moveTo(5000,5000);

    QTimer* timer = new QTimer(this);

    connect(timer,&QTimer::timeout,this,&DrawingPlane::FixedUpdate);

    timer->start(100);
}

void DrawingPlane::paintEvent(QPaintEvent *)
{
    QPainter tractorPainter;

    tractorPainter.begin(this);

    tractorPainter.translate(_tractorPosVector.toPoint());
    tractorPainter.rotate(_baseAngle);


    QTransform trans = tractorPainter.transform();

    _tractorPosVector = QVector2D(trans.map(_tractor.center()));

    float XY = 2;
    if(!_trajectoryPoints.empty())XY = pow((_trajectoryPoints.last().x() - _tractorPosVector.toPointF().x()),2)
               + pow((_trajectoryPoints.last().y() - _tractorPosVector.toPointF().y()),2);

    if(XY>1)
        _trajectoryPoints.append(QPointF(_tractorPosVector.toPointF()));

    QVector2D v = QVector2D(_tractor.topLeft() - _tractor.center());
    _tractor.moveTo(v.x(),v.y());

    tractorPainter.drawRect(_tractor);

    DrawCrossbar(tractorPainter);
    tractorPainter.end();
    DrawTrajectory();
    QPainter painter;
    painter.begin(this);

    for(auto var:_trajectoryArea){
        painter.drawLine(var);
    }

    painter.end();
    DrawGuidanceLines();
}

void DrawingPlane::FixedUpdate()
{
    MoveTractor();
    update();
    CalculateIntersection();
    emit GetMainObjectPosition(_tractorPosVector);
}

void DrawingPlane::MoveTractor()
{
    int dy = _tractor.y() + _speed;
    if(_speed != 0)
        _baseAngle +=_angle;

    _tractor.moveTop(dy);
}

void DrawingPlane::DrawTrajectory()
{
    if(_trajectoryPoints.size() < 2)return;

    QPainter painter;
    painter.begin(this);

    for (int var = 1; var < _trajectoryPoints.size(); ++var)
    {
        painter.drawLine(_trajectoryPoints[var-1],_trajectoryPoints[var]);
    }
    painter.end();
}

void DrawingPlane::DrawCrossbar(QPainter &painter)
{
    QPointF point1 = QPointF(_tractor.center().x() - _crossbarLenght/2,_tractor.center().y() - 15);
    QPointF point2 = QPointF(_tractor.center().x() + _crossbarLenght/2,_tractor.center().y() - 15);
    QLineF line(point1,point2);


    painter.drawLine(line);

    QTransform transform = painter.transform();

    _trajectoryArea.append(transform.map(line));
    //qDebug()<<_trajectoryArea.count();
}

void DrawingPlane::DrawGuidanceLines()
{
    if(!_isWork) return;

    _guidanceLinesPainter.begin(this);

    _guidanceLinesPainter.translate(_workPoint);
    _guidanceLinesPainter.rotate(_workAngle);

    for (int var = 0; var < 100; ++var) {
        QPoint p1(_crossbarLenght*var,10000);
        QPoint p2(_crossbarLenght*var,-10000);
        _guidanceLinesPainter.drawLine(p1,p2);
    }
    for (int var = 0; var < 100; ++var) {
        QPoint p1(_crossbarLenght*-var,10000);
        QPoint p2(_crossbarLenght*-var,-10000);
        _guidanceLinesPainter.drawLine(p1,p2);
    }

    _guidanceLinesPainter.end();
}

void DrawingPlane::CalculateIntersection()
{
    if(_trajectoryPoints.size() < 4)return;

    QVector2D vecOne;
    QPointF lastPos = _trajectoryPoints.last();
    QVector2D vecTwo =  QVector2D(_trajectoryPoints[_trajectoryPoints.count()-2].x()-lastPos.x(),
                                 _trajectoryPoints[_trajectoryPoints.count()-2].y()-lastPos.y());

    QVector<QPointF> finalPoints;


    QPointF finalTwoPoints[2];


    double cosB;

    for (int var = 0; var < _trajectoryPoints.count() - 2; ++var)
    {
        vecOne = QVector2D(_trajectoryPoints[var].x()-lastPos.x(),_trajectoryPoints[var].y()-lastPos.y());

        cosB = (vecOne.x()*vecTwo.x() + vecOne.y()*vecTwo.y())
                 /(vecOne.length()*vecTwo.length());

        /*if(cosB!=1){
        qDebug()<<"last pos:  "<<lastPos;
        qDebug()<<"vec one:  "<<vecOne;
        qDebug()<<"vec two:  "<<vecTwo;
        qDebug()<<"cos:  "<< cosB;
        }*/
        if(cosB >= -0.2 && cosB <= 0.2) finalPoints.append(_trajectoryPoints[var]);


    }
    qDebug()<<"**************************************************";
    qDebug()<<finalPoints.count();
    qDebug()<<"**************************************************";



    if(finalPoints.count()<2)return;

    finalPoints[0] = finalTwoPoints[0];
    finalPoints[1] = finalTwoPoints[1];

    if(QLineF(finalTwoPoints[0],lastPos).length()>QLineF(finalTwoPoints[1],lastPos).length()) std::swap(finalTwoPoints[0],finalTwoPoints[1]);

    for (int var = 2; var < finalPoints.count(); ++var)
    {
        if(QLineF(finalPoints[var],lastPos).length()<QLineF(finalTwoPoints[1],lastPos).length())finalTwoPoints[1]=finalPoints[var];

        if(QLineF(finalTwoPoints[0],lastPos).length()>QLineF(finalTwoPoints[1],lastPos).length()) std::swap(finalTwoPoints[0],finalTwoPoints[1]);
    }

    qDebug()<<"*------------------------------------------------*";
    qDebug()<<"line dist : "<<QLineF(finalTwoPoints[0],lastPos).length()<<"   "<<QLineF(finalTwoPoints[1],lastPos).length();
    qDebug()<<"btw dist: "<<QLineF(finalTwoPoints[1],finalTwoPoints[0]).length();
    qDebug()<<"main dist : "<<QLineF(QLineF(finalTwoPoints[1],finalTwoPoints[0]).center(),lastPos).length();
    qDebug()<<"*------------------------------------------------*";


    /* линейная инторполяция(не работает)
    double a=0,b=0,dist=0;
    a = (finalTwoPoints[1].y() - finalTwoPoints[0].y())/(finalTwoPoints[1].x() - finalTwoPoints[0].x());

    b = finalTwoPoints[0].y() - a;
    qDebug()<<"a = "<<a;
    qDebug()<<"b = "<<b;

    dist = abs(finalTwoPoints[1].x()-finalTwoPoints[0].x());
    QPointF last = finalTwoPoints[0];
    for (int var = 1; var < 10; var++)
    {
        qDebug()<<"y = "<<a*(finalTwoPoints[0].x() + dist*var) + b << "      x ="<<finalTwoPoints[0].x() + dist*var;
    }
    */
}

// slots
void DrawingPlane::ChangeTractorAngle(int angle)
{
    _angle = angle;
}

void DrawingPlane::ChangeTractorSpeed(int speed)
{
    _speed = speed;
}

void DrawingPlane::SwitchWorkMode()
{
    _isWork = !_isWork;
    _workAngle = _baseAngle;
    _workPoint = _tractorPosVector.toPoint();
}
//slots


















