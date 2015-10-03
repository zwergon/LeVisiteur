#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "scene.h"

#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDomDocument>
#include <visiteursettings.h>
#include <QDebug>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(0),
    timeTick(0),
    volume(50),
    requireFullScreen(false)
{

    manager = new QNetworkAccessManager(this);


    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));

    ui->setupUi(this);

    scenes.clear();
    requestVLC( PLAYLIST );

    timer = new QTimer(this);
    timer->setTimerType(Qt::PreciseTimer);
    connect( timer, SIGNAL(timeout()), this, SLOT(onTimer()) );

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::updateUI(){
    if ( requireFullScreen ){
        ui->fullscreenButton->setAutoFillBackground(true);
        ui->fullscreenButton->setStyleSheet("color: rgb(0, 255, 0)");
    }
    else {
         ui->fullscreenButton->setStyleSheet("color: rgb(255, 0, 0)");
    }

    if ( 0 != scene ){

        int currentTime = scene->time() + timeTick;
        ui->timeLabel->setText( QString("Time: %1/%2").arg(currentTime).arg(scene->duration()));
        if ( scene->isRunning() && ( currentTime >= (scene->duration()-3) ) ){
            requestVLC( PAUSE );
        }
    }

    ui->soundDial->setValue( volume );
}



void MainWindow::on_fullscreenButton_clicked()
{
    requestVLC( FULLSCREEN );
}

void MainWindow::requestVLC( int state ){

    QNetworkRequest request;
    QString str = QString("http://%1/requests/status.xml").arg( VisiteurSettings::getInstance()->getHostPort());

    request.setAttribute( QNetworkRequest::User, state );
    switch(state){
    case STATUS:
    case TIMER:
        break;

    case FULLSCREEN:
        str += "?command=fullscreen";
        break;

    case PAUSE:
        str += QString("?command=pl_pause&id=%1").arg(scene->id());
        if ( scene->isRunning() ){
            timer->stop();
            scene->setRunning(false);
        }
        else {
            if ( !timer->isActive() )
                timer->start();
            scene->setRunning(true);
        }
        break;

    case PLAYLIST:
        str = QString("http://%1/requests/playlist.xml").arg( VisiteurSettings::getInstance()->getHostPort());
        break;

    case MOVIE:
        scene->setRunning(true);
        if ( !timer->isActive() )
            timer->start(1000);
        str += QString("?command=pl_play&id=%1").arg(scene->id());
        break;
    case VOLUME:
        str += QString("?command=volume&val=%1").arg(volume);
        break;
    default:
        return;
    }


    QUrl url(str);
    url.setPassword("jef");
    request.setUrl(url);
    manager->get( request  );
}

void MainWindow::launchMovie( int i ){
    if ( i >= scenes.size() ){
        qDebug() << "unable to launch scene " << i;
        return;
    }
    scene = scenes.at(i);
    scene->setTime(0);
    timeTick = 0;
    requestVLC( MOVIE );
}

void MainWindow::onTimer(){
    timeTick++;
    //request VLC only every ten seconds.
    if ( timeTick == 10 ){
        requestVLC( TIMER );
        timeTick=0;
    }
    else {
        updateUI();
    }
}

void MainWindow::on_scene1Button_clicked()
{
    launchMovie(0);
}

void MainWindow::on_scene2Button_clicked()
{
    launchMovie(1);
}


void MainWindow::on_scene3Button_clicked()
{
    launchMovie(2);
}


void MainWindow::on_scene4Button_clicked()
{
    launchMovie(3);
}


void MainWindow::on_scene5Button_clicked()
{
    launchMovie(4);
}

void MainWindow::on_scene6Button_clicked()
{
    launchMovie(5);
}

void MainWindow::on_scene7Button_clicked()
{
    launchMovie(6);
}

void MainWindow::on_scene8Button_clicked()
{
    launchMovie(7);
}

bool MainWindow::isVLCFullscreen( const QByteArray& reply ){
    QDomDocument doc;
    doc.setContent( reply );
    QDomNodeList nodeList = doc.elementsByTagName("fullscreen");
    if ( nodeList.isEmpty() ){
        return false;
    }

    QDomElement element = nodeList.at(0).toElement();
    qDebug( QString("%1 : %2").arg(element.tagName()).arg(element.text()).toLatin1() );

    if ( element.text() == "true" ){
        return true;
    }
    if ( element.text() == "false" ){
        return false;
    }
    return ( 1 == element.text().toInt());
}


int MainWindow::getTime( const QByteArray& reply ){
    QDomDocument doc;
    doc.setContent( reply );
    QDomNodeList nodeList = doc.elementsByTagName("time");
    if ( nodeList.isEmpty() ){
        return -1;
    }

    QDomElement element = nodeList.at(0).toElement();
    return element.text().toInt();
}


void MainWindow::verifyPlaylist( const QByteArray& reply ){
    QDomDocument doc;
    doc.setContent( reply );

    QDomNodeList nodeList = doc.elementsByTagName("leaf");

    for( int i =0; i<nodeList.count(); i++ ){
        QDomElement element = nodeList.at(i).toElement();
        QString name = element.attribute("name");;
        int id = element.attribute("id").toInt();
        int duration = element.attribute("duration").toInt();
        Scene* sc = new Scene(name);
        sc->setId( id );
        sc->setDuration(duration);
        scenes.append( sc );
    }

}

void MainWindow::replyFinished( QNetworkReply* reply ){

    if ( 0 == reply ){
        return;
    }

    QByteArray answer = reply->readAll();

    QVariant variant = reply->request().attribute(QNetworkRequest::User);
    if ( variant.isValid() ){

        int rState = variant.toInt();
        switch(rState){
        case PLAYLIST:
            verifyPlaylist( answer );
            break;

        case TIMER:
        {
            int time = getTime( answer );
            if (( time != -1 ) && ( scene != 0 )){
                scene->setTime(time);
            }
            break;
        }
        case FULLSCREEN:
            requireFullScreen =  isVLCFullscreen( answer );
            break;
        }
    }





    updateUI();

}

void MainWindow::on_stopButton_clicked()
{
    requestVLC(PAUSE);
}


void MainWindow::on_soundDial_valueChanged(int value)
{
    volume = value;
    requestVLC( VOLUME );
}
