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
  getHistory("MSFT", "2020-05-21", "2020-05-28", "1m");
  string History = loadHistory("MSFT");
  StockData msft = StockData("MSFT",History,50);
  msft.printInfo();
  /*
  float net;
  while(true){
    History = update(msft);
    msft.printInfo();
    if (msft.update(History)){
      cout << "updated" << endl;
      if (msft.own()){
	if (msft.movingAve() > msft.price()){
	  net += msft.sell(log);
	  cout << "Current Net: " << net << endl;
	  fprintf(log,"Running Total: %f\n",net);
	}
      }else{
	if (msft.movingAve() < msft.price()){
	  msft.buy(log);
	}
      }
    }
  }

  //*/
  return 0;
}
