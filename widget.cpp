#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    _drawingPlane = new DrawingPlane(this);
    _worldCut = new QScrollArea(this);

    _worldCut->setWidget(_drawingPlane);

    this->resize(500,500);

    //this->horizontalScrollBar()->hide();
    //this->verticalScrollBar()->hide();

    QHBoxLayout *layout = new QHBoxLayout(this);
    QVBoxLayout *controllerLayout = new QVBoxLayout(this);
    QPushButton *startWorkButton = new QPushButton(this);

    startWorkButton->setText("On/Off");

    QDial* speedScrollBar = new QDial(this);
    speedScrollBar->setRange(0,100);


    QDial* angleScrollBar = new QDial(this);
    angleScrollBar->setRange(-10,10);
    angleScrollBar->setValue(10);


    layout->addWidget(_worldCut);
    layout->addLayout(controllerLayout);

    controllerLayout->addWidget(speedScrollBar);
    controllerLayout->addWidget(angleScrollBar);
    controllerLayout->addWidget(startWorkButton);



    connect(_drawingPlane,SIGNAL(GetMainObjectPosition(QVector2D)),this,SLOT(MoveScrollArea(QVector2D)));
    connect(speedScrollBar,SIGNAL(valueChanged(int)),_drawingPlane,SLOT(ChangeTractorSpeed(int)));
    connect(angleScrollBar,SIGNAL(valueChanged(int)),_drawingPlane,SLOT(ChangeTractorAngle(int)));
    connect(startWorkButton,SIGNAL(clicked()),_drawingPlane,SLOT(SwitchWorkMode()));
}

Widget::~Widget()
{
}

void Widget::MoveScrollArea(QVector2D objectPos)
{
    _worldCut->horizontalScrollBar()->setValue(objectPos.x()-this->size().width()/2);
    _worldCut->verticalScrollBar()->setValue(objectPos.y()-this->size().height()/2);
}

