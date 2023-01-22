//
// Created by akiva on 1/12/23.
//

#ifndef AP_1_EX_4_CLI_H
#define AP_1_EX_4_CLI_H

#include <map>
#include "../knnserver/KNN_ClientServer.h"
#include "StandardIO.h"
#include "UploadCSV.h"
#include "AlgoSettings.h"
#include "ClassifyData.h"
#include "DisplayResults.h"
#include "DownloadResults.h"
#include "Exit.h"

struct Commands{
    UploadCSV uploadCsv;
    AlgoSettings algoSettings;
    ClassifyData classifyData;
    DisplayResults displayResults;
    DownloadResults downloadResults;
    Exit _exit;

    map<int, Command&> command_map;

    Commands(KNN_ClientServer& clientServer, DefaultIO& dio, bool& noExit);
    Command& at(int);
};

class CLI {
public:
    CLI(KNN_ClientServer& clientServer, DefaultIO& dio);
    void start();
private:
    //KNN_ClientServer& clientServer;
    DefaultIO& dio;
    Commands commands;
    bool noExit;
    void printMenu();
    string getChoice();
};


#endif //AP_1_EX_4_CLI_H
