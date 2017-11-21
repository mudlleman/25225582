#include "netcommand.h"
#include <QStringList>

NetCommand::NetCommand(QObject *parent) :
    QObject(parent)
{
    CanRecCommand=false;
    RecWillGoID=-1;
}
void NetCommand::PaseCommad(QString qstr)
{


}
