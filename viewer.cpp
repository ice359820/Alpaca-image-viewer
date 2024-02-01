#include "viewer.h"
#include "./ui_viewer.h"
#include "mygraphicsview.h"
#include <QDebug>
#include <QString>
#include <QImageReader>
#include <QImage>
#include <QMessageBox>
#include <QGuiApplication>
#include <QDir>
#include <QColorSpace>
#include <QPixmap>          // QPixmap::fromImage()
#include <QGraphicsView>    // graphicsView->setScene()
#include <QApplication>     // QApplication::primaryScreen()->availableSize()
#include <QScreen>          // availableSize()
#include <QSize>
#include <QLayout>          // setContentsMargins()
#include <QFileDialog>
#include <QStringList>
#include <QStandardPaths>
#include <QDialog>

Viewer::Viewer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Viewer)
{
    ui->setupUi(this);
    scene = nullptr;

    // remove margin that between QMainWindow and layout in centralWidget
    QMainWindow *m = &(*this);
    QWidget *w = m->centralWidget();
    w->layout()->setContentsMargins(0, 0, 0, 0);

    connect( ui->actionOpen, &QAction::triggered, this, &Viewer::open );
    connect( &movie, &QMovie::updated, this, &Viewer::drawFrame );
}

Viewer::~Viewer()
{
    delete ui;
}

bool Viewer::loadFile(const QString &fileName)
{
    QImageReader reader(fileName);
    reader.setAutoTransform(true);
    QImage newImage = reader.read();
    if (newImage.isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1: %2")
                                     .arg(QDir::toNativeSeparators(fileName), reader.errorString()));
        return false;
    }

    setWindowFilePath(fileName);    // If not set the window title, sets the window title to the file name
    resize( QSize( newImage.width(), newImage.height() + ui->menubar->sizeHint().height() ) );

    if (scene != nullptr) {
        ui->graphicsView->resetTransform();
        movie.stop();
        delete scene;
    }
    scene = new QGraphicsScene();
    graphicsPixmapItem = scene->addPixmap(QPixmap::fromImage(newImage));   // initialize

    if (reader.supportsAnimation()) {        
        movie.setFileName(fileName);
        graphicsPixmapItem->setTransformationMode(Qt::SmoothTransformation);
        ui->graphicsView->setScene(scene);
        movie.start();
    }
    else {
        graphicsPixmapItem->setTransformationMode(Qt::SmoothTransformation);
        ui->graphicsView->setScene(scene);
    }
    return true;
}

void Viewer::drawFrame()
{
    frame = movie.currentPixmap();
    graphicsPixmapItem->setPixmap(frame);
}

static void initializeImageFileDialog(QFileDialog &dialog)
{
    static bool firstDialog = true;

    if (firstDialog) {
        firstDialog = false;
        const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
        dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
    }

    QStringList mimeTypeFilters;
    mimeTypeFilters.append("application/octet-stream"); // all files
    const QByteArrayList supportedMimeTypes = QImageReader::supportedMimeTypes();
    for (const QByteArray &mimeTypeName : supportedMimeTypes) {
        mimeTypeFilters.append(mimeTypeName);
    }
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("application/octet-stream");
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
}

void Viewer::open()
{
    QFileDialog dialog(this, tr("Open File"));
    initializeImageFileDialog(dialog);

    while (dialog.exec() == QDialog::Accepted && ! loadFile(dialog.selectedFiles().constFirst())) {}
}
