#ifndef MESSAGE_H
#define MESSAGE_H
#include <QObject>
#include <QBitArray>

class Message : public QObject
{
    Q_OBJECT
    Q_ENUMS(MessageType)

public:
    enum MessageType
    {
        Unknown,
        Capture,
        TimeLapse
    };

    Message(QObject *parent = 0);
    ~Message();
    QByteArray serialize();
    virtual QByteArray serializeMessagePart() = 0;
    static Message* buildMessage(const QByteArray&message);
    MessageType type(){return m_type;}
protected:
    MessageType m_type;
};

class CaptureMessage : public Message
{
    Q_OBJECT
public:
    CaptureMessage(QObject *parent = 0);
    virtual QByteArray serializeMessagePart()
    {return QByteArray();}
};

class TimeLapseMessage : public Message
{
    Q_OBJECT
public:
    TimeLapseMessage(int nbShot, int time, QObject *parent = 0);
    virtual QByteArray serializeMessagePart();
    int nbShot(){return m_nbShot;}
    int time(){return m_time;}
private:
    int m_nbShot;
    int m_time;

};

#endif // MESSAGE_H
