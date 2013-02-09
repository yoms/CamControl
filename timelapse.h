#ifndef TIMELAPSE_H
#define TIMELAPSE_H

#include <QObject>
#include <QTimer>
#include "mcamera.h"

class TimeLapse : public QObject
{
    Q_OBJECT
public:
    explicit TimeLapse( MCamera *camera, int nbShot, int time, QObject *parent = 0);
    int nbShot()
    {
        return m_nbShot;
    }

signals:
    
public slots:
    void run();
private slots:
    void capture();
private:
    int m_nbShot;
    int m_time;
    int m_index;
    MCamera* m_camera;
    QTimer m_timer;
};

#endif // TIMELAPSE_H
