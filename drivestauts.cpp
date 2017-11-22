#include "drivestauts.h"

DriveStauts::DriveStauts(QObject *parent) :
    QObject(parent)
{

}
void DriveStauts::PassByte(QByteArray qba)
{
    int indexdata=15;
    int addr = qba.at(indexdata) & 0xFF;
    addr |= ((qba.at(indexdata+1)<< 8) & 0xFF00);
    addr |= ((qba.at(indexdata+2) << 16) & 0xFF0000);
    addr |= ((qba.at(indexdata+3)<< 24) & 0xFF000000);
}
