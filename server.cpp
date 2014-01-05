#include "server.h"
#include "timelapsecommand.h"
#include "capturecommand.h"
#include "message.h"
#include <QScopedPointer>
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
    QScopedPointer<Message> message(readMessage(m_clientSocket->readAll()));
    if(message.isNull())
    {
        //TODO implement error return;
        qDebug() << "The message cannot be compute";
        return;
    }
    processMessage(message);
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

void Server::onCommandFinish(bool result)
{
    Q_UNUSED(result)
    //delete sender();
}

Message *Server::readMessage(const QByteArray & message)
{
    return Message::buildMessage(message);
}


void Server::processMessage(const QScopedPointer<Message>& message)
{
    Command* command;
    switch(message->type())
    {
    case Message::Capture:
        {
            command = new CaptureCommand(m_camera, qobject_cast<CaptureMessage*>(message.data()));
            break;
        }
    case Message::TimeLapse:
        {
            command = new TimeLapseCommand(m_camera, qobject_cast<TimeLapseMessage*>(message.data()));
            break;
        }
    default:
        {
            qDebug() << "unknown id";
            break;
        }
    }
    connect(command, SIGNAL(finish(bool)), SLOT(onCommandFinish(bool)));
    command->run();
}
