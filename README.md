Overview

This is a multithreaded TCP server implemented using the Qt framework. The server listens on port 1237, accepts client connections, and communicates using a custom data protocol defined in protocol.h. Each client connection is handled in a separate thread to ensure scalability and responsiveness.

Features

Multithreaded handling of client connections.

Communication protocol using a structured UserData object.

Real-time logging to the console for debugging and monitoring.

Graceful handling of client disconnections.

Code Structure

Key Components

TcpServer

Handles the server's main operations: listening for new connections and creating ClientHandler objects for each client.

ClientHandler

Manages individual client connections, processes received data, and sends responses.

Protocol

Defines the UserData structure used for communication. Includes methods for serializing and deserializing data.

Main Classes and Functions

TcpServer

Constructor: Initializes the server and starts listening on port 1237.

onNewConnection: Handles new client connections by creating a ClientHandler and assigning it to a new thread.

ClientHandler

Constructor: Sets up the connection between the socket and the handler.

onReadyRead: Reads and processes incoming data from the client.

onDisconnected: Handles client disconnections and cleans up resources.

Protocol (protocol.h)

UserData: A structure representing the user data exchanged between the client and server.

serialize: Converts a UserData object into a byte array.

deserialize: Converts a byte array back into a UserData object.

Setup and Usage

Open the project in Qt Creator or build using qmake:

qmake && make

Running the Server

Run the compiled server binary:

./server

The server will start listening on port 1237.

Logs will be printed to the console for debugging and monitoring.

Example Data Exchange

Client sends (serialized UserData):

{
    "userID": "12345",
    "userName": "John Doe",
    "email": "john.doe@example.com"
}

Server responds (serialized acknowledgment):

{
    "userID": "Server",
    "userName": "Acknowledged",
    "email": "server@example.com"
}

Logging

All critical operations, such as client connections, data receipt, and responses, are logged to the console.

Errors in deserialization or socket operations are logged with qCritical for easier debugging.

Future Improvements

Add secure communication using SSL/TLS.

Implement a configuration file for server settings (e.g., port number).

Enhance error handling and logging to a file.
