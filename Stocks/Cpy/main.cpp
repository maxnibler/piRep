//Maximillian H Nibler
//max.nibler@gmail.com
//https://github.com/maxnibler/

#include <iostream>
#include <fstream>
#include <sstream>
#include "python.h"
#include "analysis.h"

using namespace std;

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
  
  //FILE * log;
  //log = fopen("log.txt", "a");
  //getLongHis("MSFT");
  getHistory("MSFT", "2020-05-21", "2020-05-24", "1m");
  string History = loadHistory("MSFT");
  StockData msft = StockData("MSFT",History,50);
  History = update(msft);
  msft.update(History);
  /*
  //msft.printInfo();
  //cout << msft.movingAve() << " " << msft.lastTime() << endl;
  //cout << msft.lastTime() << endl;
  msft.printInfo();
  float net;
  while(true){
    History = update(msft);
    cout << History << endl;
    if (msft.update(History)){
      //cout << "updated" << endl;
      if (msft.own()){
	if (msft.movingAve() > msft.low()){
	  net += msft.sell(log);
	  cout << "Current Net: " << net << endl;
	}
      }else{
	if (msft.movingAve() < msft.high()){
	  msft.buy(log);
	}
      }
    }
  fprintf(log,"Running total: %f",net);
  }*/
  return 0;
}
