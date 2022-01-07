/*
 *
 * Author: 316460146 Hadar Pinto
 *         313547085 Dor Levy
 */

#include "sys/socket.h"
#include "Server.h"
#include "signal.h"
#include "unistd.h"
#include "sstream"
#include "CLI.h"

#include <netinet/in.h>
#include <functional>
string SocketIO::read() {
    char ch = 0;
    int i = 0, sizeOfChar = sizeof(char);
    string concatenateString = "";
    while (ch != '\n'){
        recv(clientID, &ch, sizeOfChar,0);
        concatenateString += ch;
    }
    return concatenateString;
}

void SocketIO::write(string s){
    const char* text = s.c_str();
    int len = strlen(text);
    send(clientID,text,len,0);

}
void SocketIO::write(float fl){
    ostringstream oStrStream;
    oStrStream << fl;
    string s(oStrStream.str());
    write(s);
}
void SocketIO::read(float* fl) {}

Server::Server(int port)throw (const char*) {
    stopLoop = false;
    sd = socket(AF_INET, SOCK_STREAM, 0);
     if(sd < 0) {
        throw "socket failed";
    }
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    if (bind(sd,(struct sockaddr*)&server, sizeof(server)) < 0) {
        throw "bind failure";
    }
    if(listen(sd,3)<0){
        throw "listen failed";
    }
}
void sigHelper(int n) {
   // cout << "sid" << endl;
}
void Server::start(ClientHandler& ch)throw(const char*){
    t = new thread([&ch, this]() {
        signal(SIGALRM, sigHelper);
        while (!stopLoop) {
            socklen_t clientSize = sizeof(client);
            alarm(1);
            int aClient = accept(sd, (struct sockaddr *) &client, &clientSize);
            if (aClient < 0) {
                throw "client failed";
            }
            ch.handle(aClient);
            close(aClient);
            alarm(0);
        }
        close(sd);
    });
}

void Server::stop(){
    stopLoop = true;
    t->join(); // do not delete this!
}

Server::~Server() {
}

