#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QUdpSocket>
#include <QTcpSocket>
#include "mcamera.h"
class Message;
class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    bool initialisation();
    
signals:
    
public slots:
    void onNewClient();
    void onClientDisconnected();
    void onPendingMessage();
    void onResearchServer();
    void onCommandFinish(bool result);
private:
    Message* readMessage(const QByteArray&message);
    void processMessage(const QScopedPointer<Message> &message);
    QTcpServer *m_server;
    QUdpSocket *m_pongServer;
    QTcpSocket *m_clientSocket;
    MCamera *m_camera;
    
};

#endif // SERVER_H
