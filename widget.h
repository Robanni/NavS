#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QScrollArea>
#include <QScrollBar>
#include <QBoxLayout>
#include <QDial>
#include <QPushButton>

#include <drawingplane.h>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    DrawingPlane* _drawingPlane;
    QScrollArea* _worldCut;

private slots:
    void MoveScrollArea(QVector2D objectPos);
};
#endif // WIDGET_H
