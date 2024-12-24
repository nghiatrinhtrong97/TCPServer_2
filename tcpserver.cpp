#include "tcpserver.h"
#include <QThread>
#include <QMutexLocker>
#include <QDebug>
#include "protocol.h"

ClientHandler::ClientHandler(QTcpSocket *socket, QObject *parent)
    : QObject(parent), clientSocket(socket)
{
    connect(clientSocket, &QTcpSocket::readyRead, this, &ClientHandler::onReadyRead);
    connect(clientSocket, &QTcpSocket::disconnected, this, &ClientHandler::onDisconnected);
}

ClientHandler::~ClientHandler()
{
    // Cleanup resources
    clientSocket->deleteLater();
}

void ClientHandler::onReadyRead()
{
    QMutexLocker locker(&mutex); // Lock the mutex to protect concurrent data access

    while (clientSocket->bytesAvailable()) {
        QByteArray receivedData = clientSocket->readAll();

        // Deserialize received data into UserData
        try {
            UserData userData = UserData::deserialize(receivedData);
            qDebug() << "Received User Data:";
            qDebug() << "UserID:" << userData.userID;
            qDebug() << "UserName:" << userData.userName;
            qDebug() << "Email:" << userData.email;

            // Prepare an acknowledgment response
            QByteArray response = UserData::serialize({
                "Server",
                "Acknowledged",
                "server@example.com"
            });
            clientSocket->write(response);
        } catch (...) {
            qCritical() << "Failed to parse received data.";
        }
    }
}

void ClientHandler::onDisconnected()
{
    qDebug() << "Client disconnected";
    clientSocket->deleteLater();
    this->deleteLater();
}

TcpServer::TcpServer(QObject *parent) : QTcpServer(parent)
{
    // Initialize the server and listen on port 1234
    if (!this->listen(QHostAddress::Any, 1237)) {
        qCritical() << "Unable to start the server: " << this->errorString();
        return;
    }

    // Connect the newConnection signal to the onNewConnection slot
    connect(this, &QTcpServer::newConnection, this, &TcpServer::onNewConnection);
}

void TcpServer::onNewConnection()
{
    // Get the new socket when a client connects
    QTcpSocket *clientSocket = this->nextPendingConnection();

    if (!clientSocket) {
        qCritical() << "Error: Unable to get client socket!";
        return;
    }

    // Create a new ClientHandler object to handle the client connection
    ClientHandler *handler = new ClientHandler(clientSocket);

    // Create a new QThread to run the ClientHandler in a separate thread
    QThread *thread = new QThread(this);
    handler->moveToThread(thread);

    // Connect thread's finished signal to delete the thread when done
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    // Start the thread
    thread->start();
}
