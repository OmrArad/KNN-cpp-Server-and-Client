#ifndef AP_1_EX_2_ABSTRACTPEER_H
#define AP_1_EX_2_ABSTRACTPEER_H

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <regex>
#include "../knnset/KNN_Set.h"

#define BUFFER_LEN 4096

using namespace std;

// This abstract class holds methods that are in charge of transferring data to and from the peer socket
class AbstractPeer {
public:

    /**
     * For server: runs the server by waiting to connect a client if there is none connected. Once a client is
     * connected, the server corresponds with the client until the latter disconnects, after which
     * the server waits for a new client.
     *
     * For client: corresponds with server as long as the connection is alive.
     * Otherwise, closes this socket.
     */
    virtual void run() = 0;

    /**
     * Validation of port number.
     * @param port reference to port number destination
     * @param portStr string containing port number
     * @return port number as int
     */
    static int validatePort(char *portStr);

protected:

    /**
     * Receive data from given socket
     * @param peerSock peer socket
     * @return string containing received data
     */
    virtual string receiveFrom(int peerSock) = 0;

    /**
     * Send data to given socket.
     * @param peerSock peer socket
     * @param message data to be sent
     */
    virtual void sendTo(int peerSock, const string &message) = 0;

    /**
     * Send and receive data to and from the given socket.
     * @param peerSock peer socket
     */
    virtual void correspond(int peerSock) = 0;

    /**
     * validate input string from client
     * @param clientInput input from client
     * @return true if valid, false o.w
     */
    static bool validateInput(const string &clientInput);
};


#endif //AP_1_EX_2_ABSTRACTPEER_H
