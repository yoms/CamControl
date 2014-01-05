#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>
#include "message.h"
#include "mcamera.h"

class Command : public QObject
{
    Q_OBJECT
public:
    explicit Command(MCamera* camera, Message* message, QObject *parent = 0);
    void run();
    virtual bool execute() = 0;
    virtual const Message* result() = 0;
signals:
    void finish(bool returnValue);
public slots:
protected:
    MCamera* m_camera;
    Message* m_message;

};

#endif // COMMAND_H
