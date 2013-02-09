#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include "mcamera.h"

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
private:
    QTcpServer *m_server;
    QTcpSocket *m_client;
    MCamera *m_camera;
    
};

#endif // SERVER_H
