#include "command.h"

Command::Command(MCamera *camera, Message *message, QObject *parent) :
    QObject(parent)
,   m_camera(camera)
,   m_message(message)
{
}

void Command::run()
{
    emit finish(execute());
}
