//
// Created by omer on 1/15/23.
//

#include "StandardIO.h"
#include <fstream>

StandardIO::StandardIO() : DefaultIO(){}

string StandardIO::read() {
    string input;
//    cin >> output;
    getline(cin, input);
    return input;
}

void StandardIO::write(std::string data) {
    cout << data << endl;
}

void StandardIO::readToFile(std::string filename) {
    string output;
    ifstream file(filename);
    ofstream result("myResult.txt");
    string line;

    if(file.is_open()) {
        while (getline(file, line)) {
            result << line << endl;
        }
        file.close();
        result.close();
//        remove(file);
    }
//    else
//        dio.write("Unable to open file");

}

void StandardIO::writeFromFile(std::string filename) {

}