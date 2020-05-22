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
  getHistory("MSFT","1d","1h");
  system("cat Database/MSFT_history.txt");
  return 0;
}
