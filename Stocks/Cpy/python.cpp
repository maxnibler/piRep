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
  fileName = "python3 "+fileName;
  for(int i = 0; i < len; i++){
    fileName.append(" ");
    fileName.append(args[i]);
  }
  const char* charFile = fileName.c_str();
  system(charFile);
  return 0;
}

int getHistory(string name, string period, string interval){
  string args[] = {name, period, interval};
  pycall("getHistory.py", args, 3);
  return 0;
}

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
  time_t tt;
  time(&tt);
  struct tm * ti = localtime(&tt);
  string currTime = asctime(ti);
  int currMonth = intMonth("May");
  cout << currTime << endl;

  
  string start = formatDate(2020, currMonth, 1);
  string end = formatDate(2020, currMonth, 23);
  string args[] = {name,start,end,"1d","_longHis.txt"};
  pycall("getHistory.py",args,5);
  system("cat Database/MSFT/MSFT_longHis.txt");
  return 0;
}
