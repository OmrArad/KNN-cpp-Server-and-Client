//
// Created by akiva on 1/16/23.
//

#include "DisplayResults.h"

const string cmdDescription{"display results"};

DisplayResults::DisplayResults(KNN_ClientServer& clientServerPtr, DefaultIO& dio) :
        Command(cmdDescription, dio, clientServerPtr) {}

void DisplayResults::execute() {

    // display the results
    client_server.writeResultsToIO(dio);
}