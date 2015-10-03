#ifndef SCENE_H
#define SCENE_H

#include <QString>

class Scene
{
public:
    Scene( const QString& name );

    int id() const { return id_; }
    int duration() const { return duration_; }
    int time() const { return time_; }
    const QString& name() const { return name_; }

    bool isRunning() const { return running_;}


    void setId( int id )  { id_ = id; }
    void setDuration( int duration ) { duration_ = duration; }
    void setTime( int time ){ time_ = time; }
    void setRunning( bool running ){ running_ = running; }

private:
    QString name_;
    int id_;
    int duration_;
    int time_;
    bool running_;
};

#endif // SCENE_H
