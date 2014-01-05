#include "timelapsecommand.h"
#include <QTimer>
#include <QCoreApplication>
#include <QDebug>

TimeLapseCommand::TimeLapseCommand(MCamera *camera, Message* message, QObject *parent) :
    Command(camera, message, parent)
{
    m_camera = camera;
    TimeLapseMessage* tlMessage =  dynamic_cast<TimeLapseMessage*>(message);
    m_nbShot = tlMessage->nbShot();
    m_time = tlMessage->time();
}

bool TimeLapseCommand::execute()
{
    m_index = 0;
    connect(&m_timer, SIGNAL(timeout()), SLOT(capture()));
    m_timer.start(m_time*1000);
    qDebug() << "TimeLapseCommand";
    return false;
}

void TimeLapseCommand::capture()
{
    QString fileName("TimeLapseCommand_Photo_%1.jpg");
    QString indexString = QString::number(m_index++);
    qDebug() << fileName.arg(indexString);
    if(m_camera->capture(fileName.arg(indexString)) != MCamera::NoError)
    {
        m_timer.stop();
        emit p_timeLapseFinish(false);
    }
    if(m_index > m_nbShot)
    {
        m_timer.stop();
        emit p_timeLapseFinish(true);
    }
}
