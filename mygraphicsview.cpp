#include "mygraphicsview.h"
#include <QDebug>
#include <QWheelEvent>  // angleDelta()
#include <QPoint>       // y()
#include <QGraphicsView>    // scale()

#define minScale 0.3
#define maxScale 5.0

MyGraphicsView::MyGraphicsView(QWidget *parent) // parent is ui->centralwidget
    : QGraphicsView(parent)                     // call parent's constructor
{
    ;
}

void MyGraphicsView::wheelEvent(QWheelEvent *event)
{
    if (event->angleDelta().y() > 0 && this->transform().m11() < maxScale ) {
        this->scale(1.25, 1.25);
    }
    else if (event->angleDelta().y() < 0 && this->transform().m11() > minScale ) {
        this->scale(0.8, 0.8);
    }
    else {
        ;
    }
}
