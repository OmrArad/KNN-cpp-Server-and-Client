//
// Created by omer on 1/22/23.
//

#ifndef EX4_SOCKETIO_H
#define EX4_SOCKETIO_H

#include "DefaultIO.h"
#include <iostream>
#include <fstream>
#include <sys/socket.h>
#include <cstdio>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_LEN 4096

using namespace std;


class socketIO : public DefaultIO{
public:
    socketIO();

    socketIO(int clientSocket);

    virtual string read() override;
    virtual void write(string data) override;
    virtual void readToFile(string filename) override;
    virtual void writeFromFile(string filename) override;
private:

    int clientSock;

    /**
     * Receive input from client socket and save in given buffer.
     * @param clientSock client's socket
     * @return string containing received data
     */
    string receiveFrom(int clientSock);

    /**
     * Send message back to client using given client socket.
     * @param clientSock client socket
     * @param message vector classification
     */
    void sendTo(int clientSock, const string &message);

    /**
     * Receive data from client, validate input, and if valid, classify and send classification to client
     * @param clientSock client socket
     */
    void correspond(int clientSock);

};


#endif //EX4_SOCKETIO_H
