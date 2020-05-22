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

int pycall(string fileName, string args[]){
  fileName = "python3 "+fileName;
  int length = args->length();
  for(int i = 0; i < length; i++){
    fileName = fileName+" "+args[i];
  }
  const char* charFile = fileName.c_str();
  system(charFile);
  return 0;
}
