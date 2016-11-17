#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //Create central widget and set main layout
    wgtMain_ = new QWidget(this);
    lytMain_ = new QGridLayout(wgtMain_);
    wgtMain_->setLayout(lytMain_);
    setCentralWidget(wgtMain_);

    //...
    centralWidget = new QWidget();
    menu  = new QMenuBar(this);
    archivo_ = new QMenu("Archivo");
    ver_ = new QMenu("Ver");
    menu1 	  = new QMenu("Menu 1");
    menu2 	  = new QMenu("Menu 2");
    menu3 = new QMenu("Menu3");
    subMenu1 = new QMenu("Submenu 1");
    subMenu2 = new QMenu("Submenu 2");

    archivo_->addMenu(menu1);
    archivo_->addMenu(menu2);
    archivo_->addMenu(menu3);

    menu1->addMenu(subMenu1);
    menu2->addMenu(subMenu2);

    menu->addMenu(archivo_);
    menu->addMenu(ver_);
    action  = menu1->addAction("About");
    actAbrir = archivo_->addAction("Abrir archivo");
    action2 = subMenu1->addAction("Submenu 1 Action");
    action3 = subMenu2->addAction("Submenu 2 Action");
    action4 = ver_->addAction("Pantalla completa");
    actStr = archivo_->addAction("Abrir stream");
    //Initialize widgets
    mediaPlayer_  = new QMediaPlayer(this);
    playerSlider_ = new QSlider(Qt::Horizontal, this);
    videoWidget_  = new QVideoWidget(this);
    volumeSlider_ = new QSlider(Qt::Horizontal, this);
    btnOpen_      = new QToolButton(this);
    btnPlay_      = new QToolButton(this);
    btnPause_     = new QToolButton(this);
    btnStop_      = new QToolButton(this);

    //Setup widwgets
    videoWidget_->setMinimumSize(400, 400);
    mediaPlayer_->setVideoOutput(videoWidget_);
    mediaPlayer_->setVolume(100);
    videoWidget_->setAspectRatioMode(Qt::KeepAspectRatio);
    volumeSlider_->setRange(0, 100);
    volumeSlider_->setSliderPosition(100);

    //Populate grid layout
    lytMain_->addWidget(videoWidget_,  0, 0, 1, 5); // fila columna, numero de filas, numero de columnas
    lytMain_->addWidget(playerSlider_, 1, 0, 1, 5);
    lytMain_->addWidget(btnOpen_,      2, 0, 1, 1);
    lytMain_->addWidget(btnPlay_,      2, 1, 1, 1);
    lytMain_->addWidget(btnPause_,     2, 2, 1, 1);
    lytMain_->addWidget(btnStop_,      2, 3, 1, 1);
    lytMain_->addWidget(volumeSlider_, 2, 4, 1, 1);

    //Buttons icons
    btnOpen_->setIcon(QIcon(QPixmap(":/icons/resources/eject.png")));
    btnPause_->setIcon(QIcon(QPixmap(":/icons/resources/pause.png")));
    btnPlay_->setIcon(QIcon(QPixmap(":/icons/resources/play.png")));
    btnStop_->setIcon(QIcon(QPixmap(":/icons/resources/stop.png")));

    //Connections
    connect(btnOpen_,      SIGNAL(pressed()),               this,         SLOT(onOpen()));
    connect(btnPlay_,      SIGNAL(pressed()),               mediaPlayer_, SLOT(play()));
    connect(btnPause_,     SIGNAL(pressed()),               mediaPlayer_, SLOT(pause()));
    connect(btnStop_,      SIGNAL(pressed()),               mediaPlayer_, SLOT(stop()));
    connect(playerSlider_, SIGNAL(sliderReleased()),        this,         SLOT(onSeek()));
    connect(mediaPlayer_,  SIGNAL(durationChanged(qint64)), this,         SLOT(onDurationChanged(qint64)));
    connect(mediaPlayer_,  SIGNAL(positionChanged(qint64)), this,         SLOT(onPositionChanged(qint64)));
    connect(volumeSlider_, SIGNAL(sliderMoved(int)),        this,         SLOT(onVolumeChanged(int)));
    connect(action,         SIGNAL(triggered()),            this,         SLOT(slotAbout()));
    connect(action2,        SIGNAL(triggered()),             this,          SLOT(slotAbout()));
    connect(action3,        SIGNAL(triggered()),             this,          SLOT(slotAbout()));
    connect(action4,        SIGNAL(triggered()),            this,           SLOT(onPantallaCompleta()));
    connect(actAbrir,       SIGNAL(triggered()),            this,         SLOT(onOpen()));
    connect(actStr,       SIGNAL(triggered()),            this,         SLOT(abrirStrDial()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::onOpen()
{
    //Show file open dialog
    QString fileName = QFileDialog::getOpenFileName(this,
                                            tr("Abrir archivo"));
    if (fileName != "") {
        mediaPlayer_->setMedia(QUrl::fromLocalFile(fileName));
    }
}

void MainWindow::onSeek()
{
    mediaPlayer_->setPosition(playerSlider_->sliderPosition());
}

void MainWindow::slotAbout()
{
  QMessageBox::about(this,"About","This is an about box \n shown with QAction of QMenu.");
}

void MainWindow::onDurationChanged(qint64 duration)
{
    playerSlider_->setRange(0, duration);
}

void MainWindow::onPositionChanged(qint64 position)
{
    playerSlider_->setSliderPosition(position);
}

void MainWindow::onVolumeChanged(int volume)
{
    mediaPlayer_->setVolume(volume);
}

void MainWindow::abrirStrDial(){
    QString stream = inputdial1->getText(this,"Url del streaming", "stream");
    mediaPlayer_->setMedia(QUrl(stream));
}

void MainWindow::onPantallaCompleta() {
    this->setWindowState(Qt::WindowFullScreen);
}
