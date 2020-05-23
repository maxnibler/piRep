//Maximillian H Nibler
//max.nibler@gmail.com
//https://github.com/maxnibler/

#include <string>

class StockData{
private:
  //Base Values
  std::string name;
  int entries;
  
  //Storage
  std::string history;
  std::string * DateTime;
  float * Open;
  float * High;
  float * Low;
  float * Close;
  int * Volume;

  //Member Functions
  int dateTimeIndex(std::string, std::string);
  int countEntries();
  int initialize();
  int populate();
public:
  StockData(std::string N, std::string H);
  int printInfo();
  float variance(int);
  int entryCount();
  float highPoint(std::string, std::string, std::string, std::string);
};
  

std::string loadHistory(std::string name);

