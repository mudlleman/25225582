#include "pidcalculate.h"

PidCalculate::PidCalculate(QObject *parent) :
    QObject(parent)
{
     err_inte=0;
     err_diff=0;
     err_record=0;
}
float PidCalculate::GetPidFloat(float kp, float ki, float kd, float error)
{
    err_inte += error;
    err_diff = error - err_record;
    err_record = error;

   float  output = kp * error + ki * err_inte + kd * err_diff;
   return output;
}
