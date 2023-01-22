#include "AbstractPeer.h"

/**
 * Validation of port number.
 * @param port reference to port number destination
 * @param portStr string containing port number
 * @return port number as int
 */
int AbstractPeer::validatePort(char *portStr) {
    int port;
    string errMsg = portStr;
    errMsg.append(" invalid format for port number");
    if (KNN_Set::isValidNumber(portStr)) {
        try {
            port = stoi(portStr);
        }
        catch (exception &err) {
            cerr << errMsg << endl;
            exit(EXIT_FAILURE);
        }
    }
    else {
        // port number argument is not a valid number
        cerr << errMsg << endl;
        exit(EXIT_FAILURE);
    }

    if (port < 0 || port > 65536) {
        cerr << port << " not in between 0 and 65536" << endl;
        exit(EXIT_FAILURE);
    }

    /* no need to validate file here since it is done in KNN_Set */
    return port;
}

/**
 * checks if client message fits the specified format
 * @param clientInput input from client
 * @return true if clientInput is correctly formatted, otherwise false
 */
bool AbstractPeer::validateInput(const std::string &clientInput) {
    // regex sequence for valid input
    const static regex inputPat {"^\\s*((\\d+\\.?|\\d+\\.\\d+|\\.\\d+)(E(\\+|\\-)\\d+)?\\s)+"
                                 "(AUC|MAN|CHB|CAN|MIN)\\s\\d+\\s*$"};

    // returns true if a valid input string was found, otherwise false
    return regex_match(clientInput, inputPat);
}