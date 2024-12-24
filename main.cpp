#include <QCoreApplication>
#include "tcpserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);  // Chỉ sử dụng QCoreApplication

    // Initialize the TCP server and start listening for connections
    TcpServer server;

    // Check if the server successfully started listening
    if (!server.isListening()) {
        qCritical() << "Unable to start the server: " << server.errorString();
        return 1; // If the server fails to start, terminate the program
    }

    qDebug() << "Server is running...";

    // Run the Qt application (This will only run the event loop, no GUI)
    return a.exec();
}
