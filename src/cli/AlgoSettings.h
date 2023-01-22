//
// Created by akiva on 1/16/23.
//

#ifndef AP_1_EX_4_ALGOSETTINGS_H
#define AP_1_EX_4_ALGOSETTINGS_H

#include "../knnserver/KNN_ClientServer.h"
#include "Command.h"

class AlgoSettings : public Command{
public:
    AlgoSettings(KNN_ClientServer& clientServerPtr, DefaultIO& dio);
    void execute() override;
};


#endif //AP_1_EX_4_ALGOSETTINGS_H
