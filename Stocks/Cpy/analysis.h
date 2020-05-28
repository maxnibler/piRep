//Maximillian H Nibler
//max.nibler@gmail.com
//https://github.com/maxnibler/

#include <string>

#define MININDAY 390

class StockEntry{
private:
  std::string dateTime;
  float open;
  float high;
  float low;
  float close;
  int volume;
public:
  StockEntry();
  int fill(std::string);
  std::string getTime();
  float getOpen();
  float getLow();
  float getHigh();
  float getClose();
  int getVolume();
  bool isCurrent();
  int print();
  bool isBefore(StockEntry);
};

class StockData{
private:
  //Base Values
  int ma;
  std::string name;
  float total;
  int counter;
  bool holding;
  float purchased;
  float recent;
  
  //Storage
  StockEntry immediate;
  StockEntry* Entries;
  //float * MA;

  //Member Functions
  int dateTimeIndex(std::string);
  int countEntries(std::string);
  int initialize();
  int populate(std::string);
  
public:
  //float changePerMin();
  StockData(std::string N, std::string H, int);
  int printInfo();
  std::string getName();
  //float variance(int);
  int entryCount();
  //loat highPoint(std::string, std::string);
  float movingAve();
  int update(std::string);
  std::string lastTime();
  bool own();
  int buy(FILE*);
  float price();
  float sell(FILE*);
};

std::string loadHistory(std::string name);

bool isDigit(char c);
