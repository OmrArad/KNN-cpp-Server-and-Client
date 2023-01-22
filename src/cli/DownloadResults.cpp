//
// Created by akiva on 1/16/23.
//

#include "DownloadResults.h"

const string cmdDescription{"download results"};

DownloadResults::DownloadResults(KNN_ClientServer& clientServerPtr, DefaultIO& dio) :
        Command(cmdDescription, dio, clientServerPtr) {}

void DownloadResults::execute() {

    client_server.writeResultsToFile(dio);

//    void (KNN_ClientServer::*func)(DefaultIO);
//    func = &KNN_ClientServer::downloadResults;

    // download the results in a separate thread
    thread download(KNN_ClientServer::downloadResults, ref(dio));
    download.join(); // remove when using with clients
}