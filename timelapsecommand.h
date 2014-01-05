#ifndef TIMELAPSECOMMAND_H
#define TIMELAPSECOMMAND_H

#include <QObject>
#include <QTimer>
#include "mcamera.h"
#include "command.h"
#include "message.h"

class TimeLapseCommand : public Command
{
    Q_OBJECT
public:
    explicit TimeLapseCommand(MCamera* camera, Message* message, QObject *parent = 0);
    virtual bool execute();
    virtual const Message* result()
    //TODO
    { return 0; }
signals:
    void p_timeLapseFinish(bool);
private slots:
    void capture();
private:
    int m_nbShot;
    int m_time;
    int m_index;
    QTimer m_timer;
};

#endif // TIMELAPSECOMMAND_H
