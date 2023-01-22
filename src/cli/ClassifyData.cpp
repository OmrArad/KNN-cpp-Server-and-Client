//
// Created by akiva on 1/16/23.
//

#include "ClassifyData.h"

const string cmdDescription{"classify data"};

ClassifyData::ClassifyData(KNN_ClientServer& clientServerPtr, DefaultIO& dio) :
    Command(cmdDescription, dio, clientServerPtr) {}

void ClassifyData::execute() {

    client_server.classify(dio);

}