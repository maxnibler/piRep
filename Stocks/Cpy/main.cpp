//Maximillian H Nibler
//max.nibler@gmail.com
//https://github.com/maxnibler/

#include <iostream>
#include "python.h"
#include "analysis.h"

using namespace std;

int main(/*int argc, char* argv[]*/){
  getLongHis("MSFT");
  //string History = loadHistory("MSFT");
  //StockData msft = StockData("MSFT",History);
  //msft.printInfo();
  /*
  for (int i = 0; i < msft.entryCount(); i++){
    cout << msft.variance(i) << endl;
  }
  */
  //cout << msft.changePerMin() << endl;
  //cout << msft.highPoint
  //  ("2020-05-22 09:30:00-04:00", "2020-05-22 15:59:00-04:00") << endl;
  //cout << History << endl;
  //system("cat Database/MSFT_history.txt");
  return 0;
}
