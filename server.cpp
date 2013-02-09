#include "server.h"
Server::Server(QObject *parent) :
    QObject(parent)
{
    m_server = new QTcpServer(this);
    m_camera = new MCamera(this);
    m_client=0;
}

bool Server::initialisation()
{

    if(m_camera->initialisation() != MCamera::NoError)
    {
        qDebug() << "Unable to manage camera";
        return false;
    }

    if(!m_server->listen(QHostAddress::Any, 8001))
    {
        qDebug() << "Unable to start server";
        return false;
    }
    connect(m_server, SIGNAL(newConnection()), SLOT(onNewClient()));
    return true;
}

void Server::onNewClient()
{
    if(!m_client)
    {
        qDebug() << "NewConnection";
        m_client = m_server->nextPendingConnection();
        connect(m_client, SIGNAL(disconnected()),
                SLOT(onClientDisconnected()));
        connect(m_client, SIGNAL(readyRead()),
                SLOT(onPendingMessage()));



    }
    else
    {
        m_server->nextPendingConnection()->close();
    }
}

void Server::onClientDisconnected()
{
    m_client->deleteLater();
    m_client = 0;
}

void Server::onPendingMessage()
{
    QByteArray messageContent =  m_client->readAll();
    switch(messageContent[0])
    {
    case '1':
        m_camera->capture("One_shot");
        break;
    default:
        qDebug() << "unknown id";
        break;
    }
}
