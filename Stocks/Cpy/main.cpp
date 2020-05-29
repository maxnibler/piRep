//Maximillian H Nibler
//max.nibler@gmail.com
//https://github.com/maxnibler/

#include <iostream>
#include <fstream>
#include <sstream>
#include <csignal>
#include "python.h"
#include "analysis.h"

using namespace std;

FILE * logFile;

/*
void signalHandler(int signum){
  fclose(logFile);
  exit(signum);
}
*/

string update(StockData SD){
  int i;
  string name = SD.getName();
  getUpdate(name);
  string path = "Database/";
  path.append(name);
  path.append("/");
  path.append(name);
  path.append("_update.txt");
  ifstream file(path.c_str());
  if (file){
    ostringstream ss;
    ss << file.rdbuf();
    path = ss.str();
  }
  while(!isDigit(path[0])){
    i = path.find('\n');
    path.erase(0,i+1);
  }
  return path;
}
  

int main(/*int argc, char* argv[]*/){
  //signal(SIGINT, signalHandler);
  getHistory("MSFT", "1d", "1m");
  string History = loadHistory("MSFT");
  StockData msft = StockData("MSFT",History,50);
  msft.printInfo();
  
  float net;
  while(true){
    logFile = fopen("log.txt", "a");
    History = update(msft);
    //msft.printInfo();
    //cout << "updated" << endl;
    msft.update(History);
    if (msft.own()){
      if (msft.movingAve() > msft.price()){
	net += msft.sell(logFile);
        cout << "Current Net: " << net << endl;
	fprintf(logFile,"Running Total: %f\n",net);
      }
    }else{
      if (msft.movingAve() < msft.price()){
	msft.buy(logFile);
      }
    }
    fclose(logFile);
  }
  //*/
  return 0;
}
