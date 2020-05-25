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
  float total;
  int counter;
  bool holding;
  float purchased;
  
  //Storage
  std::string history;
  std::string * DateTime;
  float * Open;
  float * High;
  float * Low;
  float * Close;
  int * Volume;
  //float * MA;

  //Member Functions
  int dateTimeIndex(std::string);
  int countEntries();
  int initialize();
  int populate();
  
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
  float high();
  float low();
  float sell(FILE*);
};

std::string loadHistory(std::string name);

bool isDigit(char c);
