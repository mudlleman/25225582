#ifndef PIDCALCULATE_H
#define PIDCALCULATE_H

#include <QObject>

class PidCalculate : public QObject
{
    Q_OBJECT
public:
    explicit PidCalculate(QObject *parent = 0);

public:
    float GetPidFloat(float kp,float ki,float kd, float error);

private:

    float err_inte;
    float err_diff;
    float err_record;
    //float sample;

    
signals:
    
public slots:
    
};

#endif // PIDCALCULATE_H
