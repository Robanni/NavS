#ifndef DRAWINGPLANE_H
#define DRAWINGPLANE_H

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QVector2D>




class DrawingPlane : public QWidget
{
    Q_OBJECT
public:
    explicit DrawingPlane(QWidget *parent = nullptr);

private:
    const QSize _planeSize = QSize(1000,1000);
    QRect _tractor = QRect(0,0,20,20);
    QVector<QPointF> _trajectoryPoints;
    QVector<QLineF> _trajectoryArea;
    float _crossbarLenght = 70;
    bool _isWork = false;
    QPainter _guidanceLinesPainter;

private:
    int _speed = 0;
    int _angle = 0;
    int _baseAngle = 0;
    int _workAngle = 0;
    QPoint _workPoint;
    QVector2D _tractorPosVector = QVector2D(0,0);

private:
    void FixedUpdate();
    void MoveTractor();
    void DrawTrajectory();
    void DrawCrossbar(QPainter &painter);
    void DrawGuidanceLines();
    void CalculateIntersection();

public:
    void  paintEvent(QPaintEvent* ) override;

signals:
    void GetMainObjectPosition(QVector2D objectPos);

public slots:
    void ChangeTractorAngle(int angle);
    void ChangeTractorSpeed(int speed);
    void SwitchWorkMode();
};

#endif // DRAWINGPLANE_H
