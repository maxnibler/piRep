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

string formatDate(string inDate){
  return inDate;
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
  string args[] = {name,"2020-05-19","2020-05-22","1h"};
  pycall("getHistory.py",args,4);
  system("cat Database/MSFT_history.txt");
  return 0;
}
