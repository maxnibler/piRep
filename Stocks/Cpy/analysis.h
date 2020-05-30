//Maximillian H Nibler
//max.nibler@gmail.com
//https://github.com/maxnibler/

#include <string>
#include <fstream>

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
  int printLog(FILE*);
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

  //Member Functions
  int initialize();
  int populate(std::string);
  int totalUpdate(bool);
  int replace(StockEntry,FILE*);
  
public:
  StockData(std::string N, std::string H, int);
  int printInfo();
  std::string getName();
  float movingAve();
  int update(std::string, FILE*);
  std::string lastTime();
  bool own();
  int buy(FILE*);
  float price();
  float sell(FILE*);
};

std::string loadHistory(std::string name);

bool isDigit(char c);
