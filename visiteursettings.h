#ifndef VISITEURSETTINGS_H
#define VISITEURSETTINGS_H

#include<QString>

class VisiteurSettings
{
public:
    static VisiteurSettings* getInstance();

public:
    const QString& getHost() const { return host; }
    int getPort() const { return port; }

    void setHost( const QString& host ){
        this->host = host;
    }

    void setPort( int port ){
        this->port = port;
    }

    QString getHostPort() const {
        return QString("%1:%2").arg(host).arg(port);
    }

private:
    VisiteurSettings();



private:
    static VisiteurSettings* instance;
    QString host;
    int port;
};

#endif // VISITEURSETTINGS_H
