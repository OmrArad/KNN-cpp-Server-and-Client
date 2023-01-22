#include "Client.h"

/**
 * Constructor
 * @param socketNum descriptor of socket
 * @param is input stream
 * @param os output stream
 */
Client::Client(int socketNum, istream &is, ostream &os): sock(socketNum), is(is), os(os), noExit(true) {}

/**
 * Validate ip address.
 * @param ip given ip address
 * @param ipAddr ip address will be saved here
 */
void Client::validateIP(const char* ip, char* ipAddr) {
    unsigned char buf[sizeof(struct in_addr)];
    int s = inet_pton(AF_INET, ip, buf);

    // verify the ip address is in presentation format
    if (s <= 0) {
        if (s == 0)
            cerr << stderr << " Not in presentation format" << endl;
        else
            perror("inet_pton");
        exit(EXIT_FAILURE);
    }

    // convert to string
    if (inet_ntop(AF_INET, buf, ipAddr, INET6_ADDRSTRLEN) == NULL) {
        perror("inet_ntop");
        exit(EXIT_FAILURE);
    }
}

/**
 * Initiates client socket and connects with server using given program arguments.
 * @param argc number of args
 * @param argv vector with args
 * @param is input stream
 * @param os output stream
 * @return Client object
 */
Client Client::initClient(int argc, char **argv, istream &is, ostream &os) {
    if (argc != 3) {
        perror("invalid number of arguments");
        exit(1);
    }

    char serverIP[INET_ADDRSTRLEN];
    const int port = validatePort(argv[2]);

    validateIP(argv[1], serverIP);

    // create socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
        exit(1);
    }

    // connect to server socket
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(serverIP);
    if (sin.sin_addr.s_addr < 0) {
        perror("ip address error");
        exit(1);
    }

    // connect with server
    sin.sin_port = htons(port);
    if (connect(sock, (struct sockaddr*) &sin, sizeof(sin))) {
        perror("error connecting socket");
        exit(1);
    }

    return Client(sock, is, os);
}

/**
 * Calls the correspond method that sends and receives data from the server
 * as long as the connection is live.
 * Once the connection with the server is closed, the loop breaks and the socket is closed.
 */
void Client::run() {
    while (noExit) {
        correspond(sock);
    }
    close(sock);
}

/**
 * Send data to the given socket.
 * @param serverSock socket connected to server
 * @param message message
 */
void Client::sendTo(int serverSock, const string &message) {
    send(serverSock, message.c_str(), message.length(), 0);

    // user wants to close the connection
    if (message == "-1")
        noExit = false;
}

/**
 * Receive data from the given socket.
 * @param serverSock socket connected to server
 * @return string containing the received message
 */
string Client::receiveFrom(int serverSock) {
    static char buffer[BUFFER_LEN];

    // resets static buffer to 0
    memset(buffer, 0, BUFFER_LEN);

    // if a message was successfully received, it is returned as a string
    if (recv(serverSock, buffer, BUFFER_LEN, 0) > 0) {
        string receiveStr{buffer};
        return receiveStr;
    }
    else {

        // if receipt was unsuccessful, the exit condition is set and EOF is returned
        perror("receiving error");
        noExit = false;
        return "\\EOF";
    }
}

/**
 * Send and receive data to and from the given socket.
 * A line is read from the member input stream and then checked for proper formatting. If it is correctly formatted,
 * it is sent as a message to the server using sendTo method. If the input is "-1", the global exit condition is set
 * and the function returns without receiving a message from the server. Otherwise, a message is received from the
 * server and then printed to the member ostream.
 * @param serverSock socket connected to server
 */
void Client::correspond(int serverSock) {
    string inputLine;
    getline(is, inputLine);
    if (!validateInput(inputLine) && inputLine != "-1") {
        // invalid input format
        cout << "invalid input" << endl;
        return;
    }

    // send data to server
    sendTo(serverSock, inputLine);

    // if user inputs "-1" the exit condition is set and function returns
    if (inputLine == "-1") {
        noExit = false;
        return;
    }

    // receive data from server
    string receiveMsg{receiveFrom(serverSock)};

    // if receiveFrom returns EOF, a receipt error occurred and nothing is printed to the member ostream
    if (receiveMsg == "\\EOF")
        return;

    // send received data to the member ostream
    os << receiveMsg << endl;
}
