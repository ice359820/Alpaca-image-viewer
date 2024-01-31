#ifndef VIEWER_H
#define VIEWER_H

#include <QMainWindow>
#include <QImage>
#include <QGraphicsScene>
#include <QMovie>
#include <QGraphicsPixmapItem>
#include <QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui {
class Viewer;
}
QT_END_NAMESPACE

class Viewer : public QMainWindow
{
    Q_OBJECT

public:
    Viewer(QWidget *parent = nullptr);
    ~Viewer();

    bool loadFile(const QString &fileName);

private slots:
    void open();
    void drawFrame();

private:
    Ui::Viewer *ui;
    QGraphicsScene *scene;
    QMovie movie;
    QGraphicsPixmapItem *graphicsPixmapItem;
    QPixmap frame;
};
#endif // VIEWER_H
