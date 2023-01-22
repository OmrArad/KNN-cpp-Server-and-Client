#include "../knnserver/Client.h"

// The main function
int main(int argc, char* argv[]) {

    // initiate client
    Client client = Client::initClient(argc, argv, cin, cout);

    // run client
    client.run();

    return 0;
}