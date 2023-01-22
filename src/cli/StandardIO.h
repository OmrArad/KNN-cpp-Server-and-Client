//
// Created by omer on 1/15/23.
//

#ifndef AP_1_EX_4_STANDARDIO_H
#define AP_1_EX_4_STANDARDIO_H

#include "DefaultIO.h"
#include <iostream>
#include <fstream>


class StandardIO : public DefaultIO{
public:
    StandardIO();
    virtual string read() override;
    virtual void write(string data) override;
    virtual void readToFile(string filename) override;
    virtual void writeFromFile(string filename) override;

};


#endif //AP_1_EX_4_STANDARDIO_H
