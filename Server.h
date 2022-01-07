/*
 * Server.h
 *
 */

#ifndef SERVER_H_
#define SERVER_H_
#include <netinet/in.h>
#include <sys/socket.h>
#include <thread>
#include <iostream>
#include <functional>
#include <thread>
#include <pthread.h>
#include "CLI.h"
#include <exception>
using namespace std;

// edit your ClientHandler interface here:
class ClientHandler{
public:
    virtual void handle(int clientID)=0;
};

class SocketIO:public DefaultIO{
    int clientID;
public:
    SocketIO(int clientID):clientID(clientID){}
    virtual string read();
    virtual void write(string txt);
    virtual void write(float fl);
    virtual void read(float* fl);


};
// you can add helper classes here and implement on the cpp file


// edit your AnomalyDetectionHandler class here
class AnomalyDetectionHandler:public ClientHandler{

public:
    virtual void handle(int clientID){
        SocketIO socketIo(clientID);
        CLI clientInterface(&socketIo);
        clientInterface.start();
    }
};


// implement on Server.cpp
class Server {
    volatile bool stopLoop;
    int sd;
    thread* t; // the thread to run the start() method in
    sockaddr_in server;
    sockaddr_in client;

    // you may add data members

public:
    Server(int port) throw (const char*);
    virtual ~Server();
    void start(ClientHandler& ch)throw(const char*);
    void stop();
};

#endif /* SERVER_H_ */