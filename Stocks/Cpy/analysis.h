//Maximillian H Nibler
//max.nibler@gmail.com
//https://github.com/maxnibler/

#include <string>

#define MININDAY 390

class StockData{
private:
  //Base Values
  std::string name;
  int entries;
  float flux;
  
  //Storage
  std::string history;
  std::string * DateTime;
  float * Open;
  float * High;
  float * Low;
  float * Close;
  int * Volume;

  //Member Functions
  int dateTimeIndex(std::string);
  int countEntries();
  int initialize();
  int populate();
  
public:
  float changePerMin();
  StockData(std::string N, std::string H);
  int printInfo();
  float variance(int);
  int entryCount();
  float highPoint(std::string, std::string);
};

std::string loadHistory(std::string name);

