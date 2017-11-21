#ifndef NETCOMMAND_H
#define NETCOMMAND_H

#include <QObject>

class NetCommand : public QObject
{
    Q_OBJECT
public:
    explicit NetCommand(QObject *parent = 0);
    void PaseCommad(QString qstr);
public:
    bool CanRecCommand;
    int RecWillGoID;
    
signals:
    
public slots:
    
};

#endif // NETCOMMAND_H
