//Maximillian H Nibler
//max.nibler@gmail.com
//https://github.com/maxnibler/

#include <iostream>
#include <cstdlib>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include "python.h"

using namespace std;

int main (/*int argc, char* argv[]*/){
  string args[] = {""};
  pycall("test.py", args);
  system("cat out.txt");
  return 0;
}
