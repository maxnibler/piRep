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
  string year = getYear(date);
  string month = getMonth(date);
  year.append("Logs/");
  //cout << getYear(date) << endl;
  path.append("Logs/");
  path.append(year);
  //cout << month << endl;
  month.append("/");
  path.append(month);
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
  //stock.printInfo();
  currTime = theTime();
  endTime = "13:01:00";
  
  while(timeComp(currTime,endTime)){
    History = update(stock);
    if(stock.update(History,logFile) == 2){
      cerr << "Update API call returned invalid data" << endl;
    }else{
      if (stock.movingAve() > stock.price()){
	if (stock.own()){
	  float sold = stock.sell(logFile);
	  net += sold;
	  //cout << "Current Net: " << net << endl;
	  fprintf(logFile,"Running Total: %f\n",net);
	  printf("Sold: %s for: %f, net: %f\n",stock.getName().c_str(),
		 sold,net);
	}else if(!stock.hasCrossed()){
	  stock.firstCross();
	}
      }else if (stock.movingAve() <= stock.price()){
	if (!stock.own() && stock.hasCrossed()){
	  float bought = stock.buy(logFile);
	  printf("Bought: %s for: %f, net: %f\n",
		 stock.getName().c_str(), bought, net);
	}
      }
    }
    currTime = theTime();
  }
  closeProgram(0);
  //*/
  return 0;
}
