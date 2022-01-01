#include "CLI.h"

CLI::CLI(DefaultIO* dio) {
    this->dio = dio;
    this->data = new Data();
    commands.push_back(new UploadCSVFile(dio));
    commands.push_back(new AlgorithmSetting(dio));
    commands.push_back(new DetectAnomalies(dio));
    commands.push_back(new DisplayResults(dio));
    commands.push_back(new UploadAnomalies(dio));
    commands.push_back(new Exit(dio));
}

void CLI::start(){
    int index=-1;
    while(index!=5){
        dio->write("Welcome to the Anomaly Detection Server.\nPlease choose an option:\n");
        for(int i=1;i<=commands.size();i++){
            string option = to_string(i);
            option = option +".";
            dio->write(option);
            dio->write(commands[i-1]->description+"\n");
        }
        string input = dio->read();
        index=input[0]-'0'-1;
        if(index>=0 && index<=6)
            commands[index]->execute();
    }
}

CLI::~CLI() {
    for(size_t i=0;i<commands.size();i++){
        delete commands[i];
    }
}

