//Maximillian H Nibler
//max.nibler@gmail.com
//https://github.com/maxnibler/

#include <string>

#define MININDAY 390

class StockData{
private:
  //Base Values
  int ma;
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
  float * MA;

  //Member Functions
  int dateTimeIndex(std::string);
  int countEntries();
  int initialize();
  int populate();
  
public:
  //float changePerMin();
  StockData(std::string N, std::string H, int);
  int printInfo();
  //float variance(int);
  int entryCount();
  //loat highPoint(std::string, std::string);
  float movingAve();
  //int update(std::string,float,float,float,float,int);
};

std::string loadHistory(std::string name);

