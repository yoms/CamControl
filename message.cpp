#include "message.h"
#include <QDebug>

Message::Message(QObject *parent) :
    QObject(parent)
  , m_type(Unknown)
{
}

Message::~Message()
{
}

QByteArray Message::serialize()
{
    QByteArray serialized;
    serialized.append((char)m_type);
    serialized.append(';');
    serialized.append(serializeMessagePart());
    return serialized;
}

Message *Message::buildMessage(const QByteArray & message)
{
    MessageType type = (MessageType)message.at(0);
    switch(type)
    {
    case Capture:
    {
        return new CaptureMessage;
        break;
    }
    case TimeLapse:
    {
        QList<QByteArray> messagesData = message.split(';');
        if( messagesData.size() != 3)
            return 0;

        int nbShot = messagesData.at(1).toInt();
        int time = messagesData.at(2).toInt();
        TimeLapseMessage* message = new TimeLapseMessage(nbShot, time);
        return message;
        break;
    }
    default:
    {
        qDebug() << "Unknown id";
        break;
    }
    }
    return 0;

}


CaptureMessage::CaptureMessage(QObject *parent):
    Message(parent)
{
    m_type = Message::Capture;
}


TimeLapseMessage::TimeLapseMessage(int nbShot, int time, QObject *parent):
    Message(parent)
{
    m_nbShot = nbShot;
    m_time= time;
    m_type = Message::TimeLapse;
}

QByteArray TimeLapseMessage::serializeMessagePart()
{
    QString nbShot = QString::number(m_nbShot);
    QString time = QString::number(m_time);
    QString serialized = (nbShot+";"+time);
    return serialized.toLatin1();
}
