//
// Created by omer on 1/22/23.
//

#include "socketIO.h"

socketIO::socketIO() {}

socketIO::socketIO(int clientSocket) : clientSock(clientSocket){}

string socketIO::read() {
    // Receive data from the client
    string clientInput = receiveFrom(clientSock);

    // if receipt is unsuccessful, receiveFrom returns EOF
    if (clientInput == "\\EOF") {
//        return {};
    }

    return clientInput;
}

void socketIO::write(std::string data) {
    //send data back to client
    sendTo(clientSock, data);
}

void socketIO::readToFile(std::string filename) {}

void socketIO::writeFromFile(std::string filename) {}

/**
 *  receives input message from client and attempts to parse it. if it's successful, the type of the
 *  given vector is calculated according to the given distance method and k value using the KNN
 *  algorithm. the type is then sent to the client in return. if the client sends "-1" as a message,
 *  the connection is closed and the function returns.
 * @param clientSock client socket
 */
void socketIO::correspond(int clientSock) {
    /* receive vector, distance method, and k from client */

//    // Receive data from the client
//    string clientInput = receiveFrom(clientSock);
//
//    // if receipt is unsuccessful, receiveFrom returns EOF
//    if (clientInput == "\\EOF") {
//        return;
//    }

    /* this part should be in server */

    // validate input from buffer
    if (!validateInput(clientInput)) {

        // close connection with client if user input was '8'
        if (clientInput == "8") {
            // _exit command
            close(clientSock);
            acceptClient = true;
            return;
        }

        // otherwise send error msg back to client
        sendTo(clientSock, "invalid input");
        return;
    }

    try {
        // get type of given input from client
        string inputType = getTypeFromInput(clientInput);

        //send result back to client
        sendTo(clientSock, inputType);
    }
    catch (invalid_argument &exc) {
        string errMsg = "invalid input";
        sendTo(clientSock, errMsg);
    }
}

/**
 * Receive input from client socket and return as string.
 * @param clientSock client's socket
 * @return string message received from client or EOF if receipt unsuccessful
 */
string socketIO::receiveFrom(int clientSock) {

    static char buffer[BUFFER_LEN];

    // Clear the buffer
    memset(buffer, 0, BUFFER_LEN);

    // Receive data from client
    int read_bytes = recv(clientSock, buffer, BUFFER_LEN, 0);
    if (read_bytes <= 0) {
        if (read_bytes < 0)
            perror("error reading bytes");
        // connection is closed
        close(clientSock);
        acceptClient = true;
        return "\\EOF";
    }

    // copy buffer to string
    string receivedStr{buffer};
    return receivedStr;
}

/**
 * Send message back to client using given client socket.
 * @param clientSock client socket
 * @param message vector classification
 */
void socketIO::sendTo(int clientSock, const string &message) {

    // attempts to send message to client
    if (send(clientSock, message.c_str(), message.size(), 0) < 0) {

        // if unsuccessful, prints error, closes client socket, and sets server to accept new client
        perror("error sending to client");
        close(clientSock);
        acceptClient = true;
    }
}
