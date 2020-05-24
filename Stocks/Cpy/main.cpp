//Maximillian H Nibler
//max.nibler@gmail.com
//https://github.com/maxnibler/

#include <iostream>
#include "python.h"
#include "analysis.h"

using namespace std;

int main(/*int argc, char* argv[]*/){
  //getLongHis("MSFT");
  getHistory("^DJI", "2020-05-01", "2020-05-07", "1m");
  string History = loadHistory("^DJI");
  StockData msft = StockData("^DJI",History);
  //msft.printInfo();
  msft.movingAve(200);
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
