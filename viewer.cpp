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
#include <QStyle>
#include <QShortcut>
#include <QKeySequence>
#include <Qt>               // Qt namespace

Viewer::Viewer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Viewer)
{
    ui->setupUi(this);
    scene = nullptr;
    graphicsPixmapItem = nullptr;

    connect( ui->actionOpen, &QAction::triggered, this, &Viewer::open );
    connect( &movie, &QMovie::updated, this, &Viewer::drawFrame );

    QShortcut *shortcut_fullscreen = new QShortcut( QKeySequence(Qt::Key_F), this);
    connect( shortcut_fullscreen, &QShortcut::activated, this, &Viewer::changeFullScreen );
}

Viewer::~Viewer()
{
    delete ui;
}

void Viewer::changeFullScreen()
{
    if ( this->windowState() != Qt::WindowState::WindowFullScreen ) {
        this->setWindowState(Qt::WindowState::WindowFullScreen);
    }
    else {
        this->setWindowState(Qt::WindowState::WindowNoState);
    }
}

void Viewer::adjustWindowSize( QSize imageSize )
{
    QSize availableSize = QApplication::primaryScreen()->availableSize(); // not include bottom tool bar and system menu
    QSize windowSize( imageSize.width()+5, imageSize.height() + ui->menubar->sizeHint().height()+5 ); // not include title bar
    int titleBarHeight = this->style()->pixelMetric(QStyle::PM_TitleBarHeight);

    if ( windowSize.width() <= availableSize.width() && windowSize.height() + titleBarHeight <= availableSize.height() ) {
        resize( QSize( windowSize.width(), windowSize.height() ) );
    }
    else {
        while ( windowSize.width() > availableSize.width() || windowSize.height() + titleBarHeight > availableSize.height() ) {
            ui->graphicsView->scale(0.8, 0.8);
            imageSize *= 0.8;
            windowSize.setWidth(imageSize.width()+5);
            windowSize.setHeight(imageSize.height() + ui->menubar->sizeHint().height()+5);
        }
        resize( QSize( windowSize.width(), windowSize.height() ) );
    }
}

void Viewer::resizeEvent(QResizeEvent *event)
{
    if ( this->windowState() == Qt::WindowState::WindowFullScreen ) { // fullscreen
        ui->menubar->setVisible(false);

        if ( graphicsPixmapItem == nullptr ) {
            QMainWindow::resizeEvent(event);
            return;
        }
        // resize image view to fit fullscreen
        QSize pixmapSize = graphicsPixmapItem->pixmap().size();
        QSize screenResolution = QApplication::primaryScreen()->size();
        double widthRatio = screenResolution.width()*1.0 / (pixmapSize.width()*1.0);
        double heightRatio = screenResolution.height()*1.0 / (pixmapSize.height()*1.0);

        ui->graphicsView->resetTransform();
        if ( widthRatio <= heightRatio ) {
            ui->graphicsView->scale(widthRatio, widthRatio);
        }
        else {
            ui->graphicsView->scale(heightRatio, heightRatio);
        }
    }
    else {
        if ( ! ui->menubar->isVisible() ) {
            ui->menubar->setVisible(true);
        }
    }
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

    setWindowFilePath(fileName);
    setWindowTitle( tr("%1 - %2x%3").arg(windowFilePath()).arg(newImage.width()).arg(newImage.height()) );

    if (scene != nullptr) {
        ui->graphicsView->resetTransform();
        movie.stop();
        delete scene;
    }
    scene = new QGraphicsScene();
    graphicsPixmapItem = scene->addPixmap(QPixmap::fromImage(newImage));

    if (reader.supportsAnimation()) {        
        movie.setFileName(fileName);
        graphicsPixmapItem->setTransformationMode(Qt::SmoothTransformation);
        ui->graphicsView->setScene(scene);
        adjustWindowSize(newImage.size());
        movie.start();
    }
    else {
        graphicsPixmapItem->setTransformationMode(Qt::SmoothTransformation);
        ui->graphicsView->setScene(scene);
        adjustWindowSize(newImage.size());
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
