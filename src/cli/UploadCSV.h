//
// Created by omer on 1/15/23.
//

#ifndef AP_1_EX_4_UPLOADCSV_H
#define AP_1_EX_4_UPLOADCSV_H

#include "../knnserver/KNN_ClientServer.h"
#include "Command.h"

class UploadCSV : public Command {
public:
    UploadCSV(KNN_ClientServer& clientServerPtr, DefaultIO& dio);
    void execute() override;

};





#endif //AP_1_EX_4_UPLOADCSV_H
