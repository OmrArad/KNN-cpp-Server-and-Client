//
// Created by akiva on 1/12/23.
//

#ifndef AP_1_EX_4_DEFAULTIO_H
#define AP_1_EX_4_DEFAULTIO_H

#include <string>

using namespace std;

class DefaultIO {
public:
    virtual string read() = 0;
    virtual void write(string data) = 0;
    virtual void readToFile(string filename) = 0;
    virtual void writeFromFile(string filename) = 0;
};


#endif //AP_1_EX_4_DEFAULTIO_H
