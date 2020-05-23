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
