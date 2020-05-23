//Maximillian H Nibler
//max.nibler@gmail.com
//https://github.com/maxnibler/

#include <iostream>
#include <cstdlib>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

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

int getLongHis(string name){
  string start = formatDate(2020, 5, 1);
  string end = formatDate(2020, 5, 23);
  string args[] = {name,start,end,"1d"};
  pycall("getHistory.py",args,4);
  system("cat Database/MSFT_history.txt");
  return 0;
}
