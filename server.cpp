#include "server.h"
#include "timelapse.h"
Server::Server(QObject *parent) :
    QObject(parent)
{
    m_server = new QTcpServer(this);
    m_pongServer = new QUdpSocket(this);
    m_camera = new MCamera(this);
    m_clientSocket=0;
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

    if(!m_pongServer->bind(QHostAddress::Any,8000))
    {
        qDebug() << "Unable to start pong server";
    }
    connect(m_server, SIGNAL(newConnection()), SLOT(onNewClient()));
    connect(m_pongServer, SIGNAL(readyRead()), SLOT(onResearchServer()));
    return true;
}

void Server::onNewClient()
{
    if(!m_clientSocket)
    {
        qDebug() << "NewConnection";
        m_clientSocket = m_server->nextPendingConnection();
        connect(m_clientSocket, SIGNAL(disconnected()),
                SLOT(onClientDisconnected()));
        connect(m_clientSocket, SIGNAL(readyRead()),
                SLOT(onPendingMessage()));
    }
    else
    {
        m_server->nextPendingConnection()->close();
    }
}

void Server::onClientDisconnected()
{
    m_clientSocket->deleteLater();
    m_clientSocket = 0;
}

void Server::onPendingMessage()
{
    QByteArray messageContent =  m_clientSocket->readAll();
    switch(messageContent[0])
    {
    case '1':
        {
            m_camera->capture("One_shot");
            break;
        }
    case '2':
        {
            QList<QByteArray> array = messageContent.split(';');
            TimeLapse tl(m_camera,array[1].toInt(), array[2].toInt());
            tl.run();
            break;
        }
    default:
        {
            qDebug() << "unknown id";
            break;
        }
    }
}

void Server::onResearchServer()
{
    qDebug() << "ResearchServer";
    while (m_pongServer->hasPendingDatagrams()) {
             QByteArray datagram;
             datagram.resize(m_pongServer->pendingDatagramSize());
             QHostAddress sender;
             quint16 senderPort;

             m_pongServer->readDatagram(datagram.data(), datagram.size(),
                                     &sender, &senderPort);

             m_pongServer->writeDatagram("pong",sender, 8002);
         }
}
