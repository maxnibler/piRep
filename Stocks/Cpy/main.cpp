//Maximillian H Nibler
//max.nibler@gmail.com
//https://github.com/maxnibler/

#include <iostream>
#include <fstream>
#include <sstream>
#include "python.h"
#include "analysis.h"

using namespace std;

string update(StockData SD){
  int i;
  string name = SD.getName();
  getUpdate(name);
  string path = "Database/";
  path.append(name);
  path.append("/");
  path.append(name);
  path.append("_update.txt");
  ifstream file(path.c_str());
  if (file){
    ostringstream ss;
    ss << file.rdbuf();
    path = ss.str();
  }
  while(!isDigit(path[0])){
    i = path.find('\n');
    path.erase(0,i+1);
  }
  return path;
}
  

int main(/*int argc, char* argv[]*/){
  //getLongHis("MSFT");
  getHistory("MSFT", "2020-05-01", "2020-05-08", "1m");
  string History = loadHistory("MSFT");
  StockData msft = StockData("MSFT",History,50);
  //msft.printInfo();
  //cout << msft.movingAve() << " " << msft.lastTime() << endl;
  //cout << msft.lastTime() << endl;
  msft.printInfo();

  //while(true){
    History = update(msft);
    //cout << History << endl;
    msft.update(History);
    //}
    msft.printInfo();
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
