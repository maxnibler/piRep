//Maximillian H Nibler
//max.nibler@gmail.com
//https://github.com/maxnibler/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include "analysis.h"

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
  printf("%s: %f %f %f %f\n",dateTime.c_str(),open,high,low,close);
  return 0;
}

bool isDigit(char c){
  //cout << c << endl;
  if (c < 48 || c > 57){
    return 0;
  }
  return 1;
}
/*
int StockData::dateTimeIndex(string d){
  if (d < Entries[count].getTime() ||
      d > Entries[ma-1].getTime()){
    return -1;
  }
  return stringBS(DateTime, d, 0, entries-1);
}

float StockData::highPoint(string fDT, string toDT){
  //cout << fDT << toDT << endl;
  int start, end;
  end = dateTimeIndex(toDT);
  start = dateTimeIndex(fDT);
  if (end == -1 || start == -1){
    return -1.0;
  }
  //cout << start << ", " << end << endl;
  return High[findPeak(true, High, start, end)];
}

float StockData::changePerMin(){
  return flux;
}
*/
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
  nwline = his.find("\n");
  while(nwline > 0){
    temp = his.substr(0,nwline);
    his.erase(0,nwline+1);
    //cout << x << endl;
    counter = (counter+1)%ma;
    Entries[counter].fill(temp);
    //Entries[c].print();
    nwline = his.find("\n");
  }/*
  for(int i = 0; i < entries-ma; i++){
    his.erase(0,his.find("\n")+1);
    //cout << his << endl;
  }
  for(int i = 0; i < ma; i++){
    temp = extract(&his);
    if (temp[0] == '\n') temp.erase(0,1);
    DateTime[i] = temp;
    temp = extract(&his);
    Open[i] = stof(temp);
    //cout << Open[i] << " " << i << endl;
    temp = extract(&his);
    High[i] = stof(temp);
    temp = extract(&his);
    Low[i] = stof(temp);
    temp = extract(&his);
    Close[i] = stof(temp);
    temp = extract(&his);
    Volume[i] = stoi(temp);
    his.erase(0, his.find("\n"));
  }*/
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
    // printf("%i: %s, %f, %f, %f, %f, %i\n",i,DateTime[i].c_str(),
    //Open[i],High[i],Low[i],Close[i],Volume[i]);
  }
  return 0;
}

string StockData::getName(){
  return name;
}

string StockData::lastTime(){
  return Entries[counter].getTime();
}

int StockData::entryCount(){
  return ma;
}
/*
float StockData::variance(int ind){
  return High[ind] - Low[ind];
}

int StockData::countEntries(string history){
  entries = 0;
  int len = history.length();
  for(int i = 0; i < len; i++){
    if (history[i] == '\n') entries++;
    //cout << i << endl;
  }
  return entries;
}
*/
int StockData::initialize(){
  Entries = new StockEntry [ma];
  counter = 0;
  holding = false;
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

int StockData::update(string up){
  up = isolate(up);
  StockEntry entry1 = StockEntry();
  StockEntry entry2 = StockEntry();
  entry1.fill(up.substr(0,up.find("\n")));
  up.erase(0,up.find("\n")+1);
  entry2.fill(up);
  cout << endl;
  entry1.print();
  entry2.print();
  counter = (counter+1)%ma;
  if (entry2.isCurrent()){
    immediate = entry2;
    Entries[counter] = entry1;
  }else{
    Entries[counter] = entry2;
  }
  Entries[counter].print();
  return 1;
} 

float StockData::movingAve(){
  return total/ma;
}

float StockData::price(){
  return recent;
}

int StockData::buy(FILE * log){
  purchased = recent;
  fprintf(log,"Bought %s at :%f\n",name.c_str(),purchased);
  holding = true;
  return 0;
}

bool StockData::own(){
  return holding;
}

float StockData::sell(FILE * log){
  float net = recent-purchased;
  fprintf(log,"Sold %s at :%f for %f dollars profit\n",
	  name.c_str(),Entries[counter].getClose(),net);
  holding = false;
  return net;
}

string loadHistory(string name){
  string str = "Database/";
  str.append(name);
  str.append("/");
  str.append(name);
  str.append("_history.txt");
  ifstream file(str.c_str());
  if (file){
    ostringstream ss;
    ss << file.rdbuf();
    str = ss.str();
  }
  //cout << str << endl << endl;
  while(!isDigit(str[0])){
    //cout << "test" << endl;
    int i = str.find('\n');
    str.erase(0,++i);
  }
  return str;
}
