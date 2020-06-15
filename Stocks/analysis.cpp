//Maximillian H Nibler
//max.nibler@gmail.com
//https://github.com/maxnibler/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include "analysis.h"
#include "python.h"

using namespace std;



//Set max to "true" to find max and "false" to find min
int findPeak(bool max, float* A, int start, int end){
  int ret = start;
  if (end < start) return -1;
  while(start <= end){
    if (max){
      if (A[start] > A[ret]) ret = start;
    }else{
      if (A[start] < A[ret]) ret = start;
    }
    start++;
  }
  return ret;
}

int stringBS(string* A, string str, int s, int e){
  int m = (e + s)/2;
  if (s == e) return s;
  if (A[m] == str) return m;
  else if(str < A[m]){
    return stringBS(A, str, s, m);
  }else{
    return stringBS(A, str, m+1, e);
  }
}

string extract(string* H){
  //cout << "Extract Found: " << stop << endl;
  while((*H).find(" ") == 0){
    (*H).erase(0,1);
  }
  int stop = (*H).find("  ");
  string ret;
  ret = (*H).substr(0,stop);
  (*H).erase(0,stop+2);
  return ret;
}

StockEntry::StockEntry(){
}

int StockEntry::printLog(FILE * log){
  fprintf(log,"%s: %f %f %f %f\n",dateTime.c_str(),open,high,low,close);
  return 0;
}

bool StockEntry::isBefore(StockEntry e){
  //cout << dateTime << " " << e.getTime() << endl;
  if (dateTime >= e.getTime())  return 0;
  return 1;
}     

int StockEntry::fill(string str){
  string temp = extract(&str);
  //cout << str;
  dateTime = temp;
  temp = extract(&str);
  open = stof(temp);
  temp = extract(&str);
  high = stof(temp);
  temp = extract(&str);
  low = stof(temp);
  temp = extract(&str);
  close = stof(temp);
  temp = extract(&str);
  volume = stoi(temp);
  //cout << str;
  return 0;
}

float StockEntry::getOpen(){
  return open;
}

float StockEntry::getLow(){
  return low;
}

float StockEntry::getHigh(){
  return high;
}

float StockEntry::getClose(){
  return close;
}

int StockEntry::getVolume(){
  return volume;
}

string StockEntry::getTime(){
  return dateTime;
}

bool StockEntry::isCurrent(){
  if (open != low) return 0;
  if (close != high) return 0;
  if (high != low) return 0;
  if (volume != 0) return 0;
  return 1;
}

int StockEntry::print(){
  printf("%s: %f %f %f %f",dateTime.c_str(),open,high,low,close);
  return 0;
}

bool isDigit(char c){
  //cout << c << endl;
  if (c < 48 || c > 57){
    return 0;
  }
  return 1;
}

StockData::StockData(string N, string H, int m){
  name = N;
  ma = m;
  //cout << N << ": " << endl;
  //cout << H << endl;
  if (initialize()) exit(-1);
  populate(H);
}

int StockData::populate(string his){
  string temp;
  int nwline;
  StockEntry entry;
  nwline = his.find("\n");
  while(nwline > 0){
    temp = his.substr(0,nwline);
    his.erase(0,nwline+1);
    //cout << x << endl;
    counter = (counter+1)%ma;
    entry.fill(temp);
    if (!entry.isCurrent()) Entries[counter] = entry;
    //Entries[c].print();
    nwline = his.find("\n");
  }
  total = 0;
  for(int i = 0; i < ma; i++){
    total += (Entries[i].getHigh()+Entries[i].getLow())/2;
  }
  //cout << total << endl;
  return 0;
}

int StockData::printInfo(){
  cout << name << ": \n";
  //cout << history << endl;
  for(int i = 0; i < ma; i++){
    Entries[i].print();
    cout << endl;
  }
  return 0;
}

string StockData::getName(){
  return name;
}

string StockData::lastTime(){
  return Entries[counter].getTime();
}

int StockData::initialize(){
  Entries = new StockEntry [ma];
  counter = 0;
  holding = false;
  crossed = false;
  return 0;
}

string isolate(string up){
  string temp;
  while(up.length() > up.find("\n")+1){
    temp = up.substr(0,up.find("\n"));
    //cout << up.length() << " " << up.find("\n") << endl;
    up.erase(0,up.find("\n")+1);
  }
  temp.append("\n");
  temp.append(up);
  //cout << temp;
  return temp;
}

float testEntry(string str){
  str.erase(0,str.find("\n")+1);
  string temp = extract(&str);
  //cout << temp << endl;
  temp = extract(&str);
  //cout << temp << endl;
  for (int i = 0; i < 3; i++){
    if (temp.compare(extract(&str))) return -1;
  }
  return stof(temp);
}

int StockData::replace(StockEntry e,FILE* log){
  counter = (counter+1)%ma;
  totalUpdate(false);
  fprintf(log,"Updated: ");
  Entries[counter].printLog(log);
  fprintf(log,"With: ");
  e.printLog(log);
  Entries[counter] = e;
  totalUpdate(true);
  return 0;
}

bool verify(string up){
  //cout << up << endl;
  if (isDigit(up[0])) return false;
  return true;
}

int StockData::update(string up,FILE* log){
  if (verify(up)) return 2; 
  up = isolate(up);
  StockEntry entry1 = StockEntry();
  StockEntry entry2 = StockEntry();
  entry1.fill(up.substr(0,up.find("\n")));
  up.erase(0,up.find("\n")+1);
  entry2.fill(up);
  //entry2.print();
  if (entry2.isCurrent()){
    if (immediate.isBefore(entry2)){
      entry2.print();
      cout << " [MA]: " << movingAve() << endl;
    }
    immediate = entry2;
    if (Entries[counter].isBefore(entry1)){
      replace(entry1,log);
    }
  }else{
    immediate = entry2;
    if (Entries[counter].isBefore(entry2)){
      replace(entry2,log);
    }
  }  //Entries[counter].print();
  return 0;
}

int StockData::totalUpdate(bool up){
  float ave;
  ave = Entries[counter].getHigh();
  ave += Entries[counter].getLow();
  if (up){
    total += ave/2;
  }else{
    total -= ave/2;
  }
  return 0;
}

float StockData::movingAve(){
  return total/ma;
}

float StockData::price(){
  return immediate.getClose();
}

int StockData::buy(FILE * log){
  buyShares(name, 100);
  purchased = immediate.getClose();
  //cout << purchased << endl;
  fprintf(log,"Bought %s at :%f\n",name.c_str(),purchased);
  holding = true;
  return 0;
}

int StockData::firstCross(){
  crossed = 1;
  return 0;
}

bool StockData::hasCrossed(){
  return crossed;
}

bool StockData::own(){
  return holding;
}

float StockData::sell(FILE * log){
  sellShares(name, 100);
  float net = immediate.getClose()-purchased;
  fprintf(log,"Sold %s at :%f for %f dollars profit\n",
	  name.c_str(),immediate.getClose(),net);
  holding = false;
  return net;
}

string loadHistory(string name, string path){
  //cout << path << endl;
  path.append("History/");
  path.append(name);
  path.append("/");
  path.append(name);
  path.append("_history.txt");
  //cout << path << endl;
  string str;
  ifstream file(path.c_str());
  if (file){
    ostringstream ss;
    ss << file.rdbuf();
    str = ss.str();
  }
  while(!isDigit(str[0])){
    //cout << "test" << endl;
    int i = str.find('\n');
    str.erase(0,++i);
  }
  return str;
}
