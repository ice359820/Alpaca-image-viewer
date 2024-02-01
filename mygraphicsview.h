#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QWidget>

class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    MyGraphicsView(QWidget *parent = nullptr);
protected:
    virtual void wheelEvent(QWheelEvent *event) override ;
};

#endif // MYGRAPHICSVIEW_H
