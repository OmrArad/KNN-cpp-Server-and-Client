//
// Created by akiva on 1/2/23.
//
#include "../knnserver/KNN_MainServer.h"

/**
 * main function
 * @param argc arg count
 * @param argv arg vector
 * @return 0 (default)
 */
int main(int argc, char *argv[]) {
//    KNN_MainServer::run(argc, argv);
    KNN_MainServer::runAlone(argc, argv);
    return 0;
}