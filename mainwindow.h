#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class QNetworkReply;
class Scene;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum {
        STATUS,
        PAUSE,
        FULLSCREEN,
        MOVIE,
        PLAYLIST,
        TIMER,
        VOLUME
    };

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    bool isVLCFullscreen( const QByteArray& reply );

    int getTime( const QByteArray& reply );

    void verifyPlaylist( const QByteArray& reply );

    void requestVLC( int state );

    void requestPlaylist();

    void updateUI();

    void launchMovie( int );

private slots:
    void on_fullscreenButton_clicked();

    void on_scene1Button_clicked();
    void on_scene2Button_clicked();
    void on_scene3Button_clicked();
    void on_scene4Button_clicked();
    void on_scene5Button_clicked();
    void on_scene6Button_clicked();
    void on_scene7Button_clicked();
    void on_scene8Button_clicked();



    void on_stopButton_clicked();

    void replyFinished( QNetworkReply* );

    void onTimer();

    void on_soundDial_valueChanged(int value);

private:
    QNetworkAccessManager* manager;
    Ui::MainWindow *ui;
    Scene* scene;
    int timeTick;
    int volume;

    bool requireFullScreen;


    QList<Scene*> scenes;

    QTimer* timer;


};

#endif // MAINWINDOW_H
