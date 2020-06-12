//Maximillian H Nibler
//max.nibler@gmail.com
//https://github.com/maxnibler/

#include <iostream>
#include <fstream>
#include <sstream>
#include <csignal>
#include <chrono>
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

string splitDateTime(string* dt){
  int len = (*dt).length();
  int count = 0;
  for(int i = 0; i < len; i++){
    if ((*dt)[i] == ' ') count++;
    if (count == 3){
      count = i;
      break;
    }
  }
  string ret = (*dt).substr(0,count);
  (*dt).erase(0,count+1);
  string temp = (*dt).substr((*dt).find(" "),(*dt).length()-3);
  //cout << temp << endl;
  ret.append(temp);
  (*dt).erase((*dt).find(" "),(*dt).length()-1);
  return ret;
}

int main(/*int argc, char* argv[]*/){
  logFile = fopen("log.txt", "a");
  fprintf(logFile,"\nProgram Run:\n\n");
  signal(SIGINT, signalHandler);
  getHistory("COTY", "1d", "1m");
  string History = loadHistory("COTY");
  StockData stock = StockData("COTY",History,50);
  stock.printInfo();

  time_t tt;
  time(&tt);
  struct tm * ti = localtime(&tt);
  string currTime = asctime(ti);
  string date = splitDateTime(&currTime);
  cout << date << "," << currTime << endl;
  
  
  float net; 
  while(true){
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
  }
  //*/
  return 0;
}
