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
  FILE * log;
  log = fopen("log.txt", "a");
  //getLongHis("MSFT");
  getHistory("COTY", "2020-05-23", "2020-05-27", "1m");
  string History = loadHistory("COTY");
  StockData msft = StockData("COTY",History,50);
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
    }else break;
    fprintf(log,"Running total: %f\n",net);
  }
  return 0;
}
