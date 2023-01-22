//
// Created by omer on 1/15/23.
//

#include "StandardIO.h"
//#include <strstream>

StandardIO::StandardIO() : DefaultIO(){}

string StandardIO::read() {
    string output;
    cin >> output;
    return output;
}

void StandardIO::write(std::string data) {
    cout << data << endl;
}

void StandardIO::readToFile(std::string filename) {
    string output;

}

void StandardIO::writeFromFile(std::string filename) {

}