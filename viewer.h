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
    void adjustWindowSize(QSize imageSize);
protected:
    void resizeEvent(QResizeEvent *event) override;
private slots:
    void open();
    void drawFrame();
    void changeFullScreen();
private:
    Ui::Viewer *ui;
    QGraphicsScene *scene;
    QMovie movie;
    QGraphicsPixmapItem *graphicsPixmapItem;
    QPixmap frame;
};
#endif // VIEWER_H
