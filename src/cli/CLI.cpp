#include "CLI.h"

using std::stringstream;

CLI::CLI(KNN_ClientServer &clientServer, DefaultIO &dio) : dio(dio), noExit(true),
                                                           commands(clientServer, dio, noExit){}
void CLI::start() {
    string choice;
    while (noExit) {
        printMenu();

        // get choice from input
        choice = getChoice();

        // convert to int
        int cmd_num = stoi(choice);

        // set command to given choice
        Command& cmd = commands.command_map.at(cmd_num);

        // execute command
        cmd.execute();
    }
}

void CLI::printMenu() {
    dio.write("Welcome to the KNN Classifier Server. Please choose an option:");
    for (auto cmd = commands.command_map.cbegin(); cmd != commands.command_map.cend(); cmd++) {
        stringstream s;
        s << cmd->first << ". " << cmd->second.getDescription();
        dio.write(s.str());
    }
}

string CLI::getChoice() {
    return dio.read(); // validate input here?  yes -akiva
}

Commands::Commands(KNN_ClientServer& clientServer, DefaultIO& dio, bool& noExit)
        : uploadCsv(clientServer, dio), algoSettings(clientServer, dio),
          classifyData(clientServer, dio), displayResults(clientServer, dio),
          downloadResults(clientServer, dio), _exit(clientServer, dio, noExit),
          command_map{{1,uploadCsv},{2,algoSettings},{3,classifyData},{4,displayResults},
                      {5,downloadResults},{8, _exit}}{}

Command &Commands::at(int key) {
    return command_map.at(key);
}