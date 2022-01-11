/*
 * Author: 316460146 Hadar Pinto
 *         313547085 Dor Levy
 */
#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>

#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"

using namespace std;

class DefaultIO{
public:
    virtual string read()=0;
    virtual void write(string text)=0;
    virtual void write(float f)=0;
    virtual void read(float* f)=0;
    virtual ~DefaultIO(){}

    void readAndCreateFile(string fileName) {
        ofstream newFile(fileName);
        string line = "";
        while ((line=read()) != "done\n"){
            newFile<<line<<endl;
        }
        newFile.close();
    }

};


struct newReport {
    int startLine;
    int endLine;
    string features;
    bool isTruePositive = false;
};
class Data{
public:
    float threshold;
    int numOfRows;
    vector<AnomalyReport> ap;
    vector<newReport> report;
    HybridAnomalyDetector ad;

public:
    Data(){
        threshold = 0.9;
        numOfRows = 0;
    }
    void setThreshold(float f){
        this->threshold = f;
    }
    void setNumOfRows(int i){
        this->numOfRows = i;
    }
};

class Command{
protected:
    DefaultIO* dio;
    Data* data;
public:
    const string description;
    Command(DefaultIO* dio, const string description, Data* data):dio(dio), description(description){
        this->data = data;
    }
    virtual void execute()=0;
    virtual ~Command(){}
};

class UploadCSVFile:public Command{
public:
    UploadCSVFile(DefaultIO* dio, Data* data):Command(dio,"upload a time series csv file", data){}
    virtual void execute(){
        dio->write("Please upload your local train CSV file.\n");
        dio->readAndCreateFile("anomalyTrain.csv");
        dio->write("Upload complete.\n");
        dio->write("Please upload your local test CSV file.\n");
        dio->readAndCreateFile("anomalyTest.csv");
        dio->write("Upload complete.\n");
    }
};

class AlgorithmSetting:public Command{
public:
    AlgorithmSetting(DefaultIO* dio, Data* data):Command(dio, "algorithm settings", data){}
    virtual void execute(){
        bool exitLoop = false;
        float userThreshold;
        while(!exitLoop){
            dio->write("The current correlation threshold is: ");
            dio->write(data->threshold);
            dio->write("\nType a new threshold\n");
            dio->read(&userThreshold);
            if (userThreshold > 0 && userThreshold <= 1) {
                data->setThreshold(userThreshold);
                data->ad.changeThreshold(userThreshold);
                exitLoop = true;
            }
            else {
                dio->write("please choose a value between 0 and 1.\n");
            }
        }
    }
};

class DetectAnomalies:public Command{
public:
    DetectAnomalies(DefaultIO* dio, Data* data): Command(dio, "detect anomalies", data){}
    virtual void execute(){
        TimeSeries trainData("anomalyTrain.csv");
        TimeSeries testData("anomalyTest.csv");
        data->setNumOfRows(testData.numOfRows());
        HybridAnomalyDetector had;
        had.learnNormal(trainData);
        data->ap = had.detect(testData);
        newReport nr;
        nr.startLine = 0;
        nr.endLine = 0;
        nr.features = "";
          for(AnomalyReport iter: data->ap){
            if ((iter.timeStep == nr.endLine + 1) && (iter.description == nr.features)) {
                nr.endLine++;
            } else {
                data->report.push_back(nr);
                nr.startLine = iter.timeStep;
                nr.endLine = nr.startLine;
                nr.features = iter.description;
            }
        }
        data->report.push_back(nr);
        data->report.erase(data->report.begin());

        dio->write("anomaly detection complete.\n");
    }
};

class DisplayResults:public Command{
public:
    DisplayResults(DefaultIO* dio, Data* data): Command(dio, "display results",data){}
    virtual void execute(){
        vector<AnomalyReport>::iterator iter;
//        for (iter = data->ap.begin(); iter <= data->ap.end(); iter++)
         for(AnomalyReport iter: data->ap){
            dio->write(iter.timeStep);
            dio->write("\t" + iter.description + "\n");
        }
        dio->write("Done.\n");
    }
};
class UploadAnomalies:public Command{
public:
    UploadAnomalies(DefaultIO* dio, Data* data): Command(dio,"upload anomalies and analyze results", data){}
    bool isTruePostive(int start, int end){
        for(int i = 0; i < data->report.size(); i++) {
            newReport nr = data->report[i];
            if (end >= nr.startLine && nr.endLine >= start){
                data->report[i].isTruePositive = true;
                return true;
            }
        }
        return false;
    }

    virtual void execute(){
        dio->write("please upload your local anomalies files.\n");
        string line = "";
        float countTruePositive = 0 , numOfReports = 0, totalTimeSteps = 0, countFalsePositive;
        while ((line=dio->read()) != "done\n"){
            numOfReports++;
            int lineLength = line.length();

            string start = line.substr(0,line.find(','));
            string end = line.substr(line.find(',') + 1, lineLength);
            int startToInt = stoi(start);
            int endToInt = stoi(end);
            if(isTruePostive(startToInt,endToInt)){
                countTruePositive++;
            }
            totalTimeSteps += endToInt - startToInt + 1;

        }
        dio->write("Upload complete.\n");
        countFalsePositive = (data->report.size()) - countTruePositive;
        float N;
        float truePositiveRate, falsePositiveRate;
        N = data->numOfRows - totalTimeSteps;
        truePositiveRate = ((int)(1000.0*countTruePositive/numOfReports))/1000.0f;
        falsePositiveRate = ((int)(1000.0*countFalsePositive/N))/1000.0f;
        dio->write("True Positive Rate: ");
        dio->write(truePositiveRate);
        dio->write("\nFalse Positive Rate: ");
        dio->write(falsePositiveRate);
        dio->write("\n");
    }
};
class Exit:public Command{
public:
    Exit(DefaultIO* dio, Data* data): Command(dio,"exit",data){}
    virtual void execute(){
    }
};


#endif /* COMMANDS_H_ */