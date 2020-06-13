//Maximillian H Nibler
//max.nibler@gmail.com
//https://github.com/maxnibler/

#include <iostream>
#include <fstream>
#include <sstream>
#include <csignal>
#include "utils.h"
#include "python.h"
#include "analysis.h"

using namespace std;

FILE * logFile;

void closeProgram(int signum){
  fclose(logFile);
  exit(signum);
}

void signalHandler(int signum){
  closeProgram(signum);
}

string update(StockData SD){
  int i;
  //cout << "here" << endl;
  string name = SD.getName();
  getUpdate(name);
  string path = loadPath();
  path.append("History/");
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
  //cout << "no" << endl;
  if (path.compare("Terminated\n") == 0){
    closeProgram(2);
  }
  while(!isDigit(path[0])){
    i = path.find('\n');
    path.erase(0,i+1);
  }
  //cout << "broke" << endl;
  return path;
}


int openLog(string date){
  string path = loadPath();
  path.append(date);
  path.append("_log.txt");
  logFile = fopen(path.c_str(), "a");
  fprintf(logFile,"\nProgram Run:\n\n");
  return 0;
}

int main(/*int argc, char* argv[]*/){
  string currTime, date, path, History, endTime;
  float net;
  date = getDate();
  openLog(date);
  signal(SIGINT, signalHandler);
  getHistory("COTY", "1d", "1m");
  History = loadHistory("COTY",loadPath());
  StockData stock = StockData("COTY",History,50);
  stock.printInfo();
  currTime = theTime();
  endTime = "13:01:00";
  
  while(timeComp(currTime,endTime)){
    History = update(stock);
    if(stock.update(History,logFile) == 2){
      cerr << "Update API call returned invalid data" << endl;
    }else{
      if (stock.own()){
	if (stock.movingAve() > stock.price()){
	  net += stock.sell(logFile);
	  cout << "Current Net: " << net << endl;
	  fprintf(logFile,"Running Total: %f\n",net);
	}
      }else{
	if (stock.movingAve() < stock.price()){
	  stock.buy(logFile);
	}
      }
    }
    currTime = theTime();
  }
  closeProgram(0);
  //*/
  return 0;
}
