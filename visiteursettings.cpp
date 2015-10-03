#include "visiteursettings.h"


VisiteurSettings* VisiteurSettings::instance = 0;


VisiteurSettings* VisiteurSettings::getInstance() {
    if ( instance == 0 ){
        instance = new VisiteurSettings;
    }

    return instance;
}

VisiteurSettings::VisiteurSettings() : host("localhost"), port(8080)
{

}
