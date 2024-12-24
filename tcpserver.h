#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMutex>

class ClientHandler : public QObject
{
    Q_OBJECT

public:
    explicit ClientHandler(QTcpSocket *socket, QObject *parent = nullptr);
    ~ClientHandler();

public slots:
    void onReadyRead();
    void onDisconnected();

private:
    QTcpSocket *clientSocket;
    QMutex mutex;  // Mutex để bảo vệ dữ liệu truy cập đồng thời
};

class TcpServer : public QTcpServer
{
    Q_OBJECT

public:
    explicit TcpServer(QObject *parent = nullptr);

private slots:
    void onNewConnection();

private:
    QMutex mutex;  // Mutex để bảo vệ dữ liệu truy cập đồng thời
};

#endif // TCPSERVER_H
