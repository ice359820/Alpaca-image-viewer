#include "mygraphicsview.h"
#include <QWheelEvent>  // angleDelta()
#include <QPoint>       // y()
#include <QGraphicsView>    // scale()

#define minScale 0.3
#define maxScale 5.0

MyGraphicsView::MyGraphicsView(QWidget *parent) // parent is ui->centralwidget
    : QGraphicsView(parent)                     // call parent's constructor
{
    view = this;
    scaleFactor = 1.0;
}

void MyGraphicsView::wheelEvent(QWheelEvent *event)
{
    if (event->angleDelta().y() > 0 && scaleFactor < maxScale ) {
        view->scale(1.25, 1.25);
        scaleFactor *= 1.25;
    }
    else if (event->angleDelta().y() < 0 && scaleFactor > minScale ) {
        view->scale(0.8, 0.8);
        scaleFactor *= 0.8;
    }
    else {
        ;
    }
}
