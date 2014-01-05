#ifndef CAPTURECOMMAND_H
#define CAPTURECOMMAND_H
#include "command.h"

class CaptureCommand : public Command
{
    Q_OBJECT
public:
    explicit CaptureCommand(MCamera* camera, Message* message, QObject *parent = 0);
    virtual bool execute();
    virtual const Message* result()
    //TODO
    {return 0;}

signals:

public slots:

};

#endif // CAPTURECOMMAND_H
