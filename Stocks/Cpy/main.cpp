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
#include "analysis.h"

using namespace std;

int main(/*int argc, char* argv[]*/){
  getHistory("MSFT","1d","2m");
  string History = loadHistory("MSFT");
  StockData msft = StockData("MSFT",History);
  msft.printInfo();
  /*
  for (int i = 0; i < msft.entryCount(); i++){
    cout << msft.variance(i) << endl;
  }
  */
  cout << msft.highPoint(" ", " ", " ", " ") << endl;
  //cout << History << endl;
  //system("cat Database/MSFT_history.txt");
  return 0;
}
