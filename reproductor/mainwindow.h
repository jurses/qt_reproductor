#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QDir>
#include <QSlider>
#include <QFileDialog>
#include <QToolButton>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QInputDialog>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    QGridLayout*        lytMain_;   //organizador por filas y columnas?
    QWidget*            wgtMain_;   //
    QMediaPlayer*       mediaPlayer_;   // permite trabajar con multimedia
    QSlider*            playerSlider_;  // el deslizador
    QVideoWidget*       videoWidget_;   // el mismo que QMediaPlayer pero para vídeo
    QSlider*            volumeSlider_;  // el deslizador del volumen
    QToolButton*        btnOpen_;   // botones...
    QToolButton*        btnPlay_;
    QToolButton*        btnPause_;
    QToolButton*        btnStop_;
    QToolButton*        btnarchivo_;    // el botón del archivo

    QWidget* centralWidget;
    QMenuBar* menu;
    QMenu* archivo_;
    QMenu* ver_;
    QMenu* menu1;
    QMenu* menu2;
    QMenu* subMenu1;
    QMenu* subMenu2 ;
    QAction* actAbrir;
    QAction* action;
    QAction* actStr;
    QAction* action2;
    QAction* action3;
    QMenu* menu3;
    QAction* action4;
    QInputDialog* inputdial1;

private slots:  // forma de qt de gestionar los eventos en la interfaz
    void onOpen();
    void onSeek();
    void onDurationChanged(qint64 duration);    // quint64 un super entero
    void onPositionChanged(qint64 position);
    void onVolumeChanged(int volume);
    void slotAbout();
    void onPantallaCompleta();
    void abrirStrDial();
};

#endif // MAINWINDOW_H
