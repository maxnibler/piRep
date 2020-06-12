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

string loadPath(){
  ifstream file(".config");
  string temp;
  if (file){
    ostringstream ss;
    ss << file.rdbuf();
    temp = ss.str();
  }
  int f = temp.find("=");
  string path = temp.substr(f+1,temp.find("\n")-2);
  path = path.substr(0,path.find("\n"));
  //cout << path << endl;
  return path;
}

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
  string path = "~/Documents/StockData/History/";
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
  ret.erase(ret.find("\n"),ret.find("\n")+1);
  (*dt).erase((*dt).find(" "),(*dt).length()-1);
  return ret;
}

string timeExtract(string* tt){
  int f = (*tt).find(":");
  string ret = (*tt).substr(0,f);
  (*tt).erase(0,f+1);
  return ret;
}

int timeComp(string time1, string time2){
  int h1, h2, m1, m2, s1, s2;
  //cout << time1 << " " << time2 << endl;
  string temp = timeExtract(&time1);
  h1 = stoi(temp);
  temp = timeExtract(&time1);
  m1 = stoi(temp);
  //cout << h1 << " " << m1 << endl;
  temp = timeExtract(&time1);
  s1 = stoi(temp);
  //cout << s1 << endl;
  temp = timeExtract(&time2);
  h2 = stoi(temp);
  temp = timeExtract(&time2);
  m2 = stoi(temp);
  temp = timeExtract(&time2);
  s2 = stoi(temp);
  if (h1 < h2) return 1;
  if (m1 < m2) return 1;
  if (s1 < s2) return 1;
  return 0;
}

string getTime(){time_t tt;
  time(&tt);
  struct tm * ti = localtime(&tt);
  string currTime = asctime(ti);
  return currTime;
}

string hyphenate(string date){
  int len = date.length();
  for(int i = 0; i < len; i++){
    if (date[i] == ' '){
      date[i] = '-';
    }
  }
  return date;
}

int main(/*int argc, char* argv[]*/){
  string currTime = getTime();
  string date = splitDateTime(&currTime);
  date = hyphenate(date);
  string path = loadPath();
  path.append(date);
  //cout << path << endl;
  path.append("_log.txt");
  //cout << path << "/" << endl;
  logFile = fopen(path.c_str(), "w+");
  if (logFile == NULL) cerr << "failed";
  fprintf(logFile,"\nProgram Run:\n\n");
  signal(SIGINT, signalHandler);
  cout << "here" << endl;
  getHistory("COTY", "1d", "1m");
  cout << "no here" << endl;
  string History = loadHistory("COTY",loadPath());
  cout << "actually here" << endl;
  StockData stock = StockData("COTY",History,50);
  stock.printInfo();
  currTime = getTime();
  date = splitDateTime(&currTime);
  //cout << date << "," << currTime << "," <<endl;

  //if (timeComp(currTime,"12:30:00")) cout << "Before" << endl;
  
  float net; 
  while(timeComp(currTime,"13:05:00")){
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
    currTime = getTime();
    date = splitDateTime(&currTime);
  }
  closeProgram(0);
  //*/
  return 0;
}
