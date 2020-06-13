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


void signalHandler(int signum){
  fclose(logFile);
  exit(signum);
}


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
  if (path.compare("Terminated\n") == 0){
    fclose(logFile);
    exit(2);
  }
  while(!isDigit(path[0])){
    i = path.find('\n');
    path.erase(0,i+1);
  }
  return path;
}
  

int main(/*int argc, char* argv[]*/){
  logFile = fopen("log.txt", "a");
  fprintf(logFile,"\nProgram Run:\n\n");
  signal(SIGINT, signalHandler);
  getHistory("COTY", "1d", "1m");
  string History = loadHistory("COTY");
  StockData stock = StockData("COTY",History,50);
  stock.printInfo();
  
  float net; 
  while(true){
    History = update(stock);
    //msft.printInfo();
    //cout << "updated" << endl;
    stock.update(History,logFile);
    //cout << "Moving Average: " << msft.movingAve() <<endl;
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
  //*/
  return 0;
}
