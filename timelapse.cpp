#include "timelapse.h"
#include <QTimer>
#include <QCoreApplication>
#include <QDebug>

TimeLapse::TimeLapse(MCamera *camera, int nbShot, int time, QObject *parent) :
    QObject(parent)
{
    m_camera = camera;
    m_nbShot = nbShot;
    m_time = time;
}

void TimeLapse::run()
{
    m_index = 0;
    connect(&m_timer, SIGNAL(timeout()), SLOT(capture()));
    m_timer.start(m_time*1000);
}

void TimeLapse::capture()
{
    QString fileName("TimeLapse_Photo_%1.jpg");
    QString indexString = QString::number(m_index++);
    qDebug() << fileName.arg(indexString);
    m_camera->capture(fileName.arg(indexString));
    if(m_index > m_nbShot)
    {
        m_timer.stop();
        QCoreApplication::instance()->exit();
    }
}
