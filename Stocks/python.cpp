//Maximillian H Nibler
//max.nibler@gmail.com
//https://github.com/maxnibler/

#include <iostream>
#include <cstdlib>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <chrono>

using namespace std;

string formatDate(int y, int m, int d){
  string date;
  date = to_string(y);
  date.append("-");
  if (m < 10) date.append("0");
  date.append(to_string(m));
  date.append("-");
  if (d < 10) date.append("0");
  date.append(to_string(d));
  return date;
}

int pycall(string fileName, string args[], int len){
  string path;
  path = "/home/pi/.Scripts/";
  path.append(fileName);
  fileName = path;
  fileName = "python3 "+fileName;
  for(int i = 0; i < len; i++){
    fileName.append(" ");
    fileName.append(args[i]);
  }
  const char* charFile = fileName.c_str();
  system(charFile);
  return 0;
}

int sellShares(string name, int quant){
  string args[] = {name, to_string(quant), "sell"};
  pycall("makeTrade.py", args, 3);
  return 0;
}

int buyShares(string name, int quant){
  string args[] = {name, to_string(quant), "buy"};
  pycall("makeTrade.py", args, 3);
  return 0;
}

int getUpdate(string name){
  string args[] = {name};
  pycall("getUpdate.py",args,1);
  return 0;
}

int getHistory(string name, string period, string interval){
  string args[] = {name, period, interval};
  //cout << "calling" << endl;
  pycall("getHistory.py", args, 3);
  return 0;
}
/*
int intMonth(string m){
  string Months[] = {"na","January","February","March",
	         "April","May","June","July","August",
          "September","October","November","December"};
  for(int i = 0; i < 13; i++){
    if (!Months[i].compare(m)) return i;
  }
  //cout << m << " " << Months[1] << endl;
  return 0;
}

int getLongHis(string name){
  string currTime, temp, start, end;
  time_t tt;
  time(&tt);
  struct tm * ti = localtime(&tt);
  currTime = asctime(ti);
  cout << currTime << endl;
  currTime.erase(0,currTime.find(" ")+1);
  temp = currTime.substr(0,currTime.find(" "));
  currTime.erase(0,currTime.find(" ")+1);
  int currMonth = intMonth(temp);
  temp = currTime.substr(0,currTime.find(" "));
  currTime.erase(0,currTime.find(" ")+1);
  int currDay = stoi(temp);
  currTime.erase(0,currTime.find(" ")+1);
  currTime.erase(0,currTime.find(" ")+1);
  temp = currTime.substr(0,currTime.find("\n"));
  int currYear = stoi(temp);
  cout << currMonth << " " << currDay << " " << currYear << endl;
  
  start = formatDate(currYear, currMonth, 1);
  end = formatDate(currYear, currMonth, currDay);
  string args[] = {name,start,end,"1d","_longHis.txt"};
  pycall("getHistory.py",args,5);
  system("cat Database/MSFT/MSFT_longHis.txt");
  return 0;
}
*/
