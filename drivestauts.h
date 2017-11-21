#ifndef DRIVESTAUTS_H
#define DRIVESTAUTS_H

#include <QObject>

class DriveStauts : public QObject
{
    Q_OBJECT
public:
    explicit DriveStauts(QObject *parent = 0);
public:
    int speed;
    int refspeed;
    long Motorposition;

    bool ALARM;
    bool CTRL_FAIL;
    bool OVER_VOLT;
    bool OVER_TEMP;
    bool HALL_FAIL ;
    bool INV_VEL ;
    bool STALL;
    
signals:
    
public slots:
    
};

#endif // DRIVESTAUTS_H
