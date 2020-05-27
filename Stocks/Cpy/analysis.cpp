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

bool isDigit(char c){
  //cout << c << endl;
  if (c < 48 || c > 57){
    return 0;
  }
  return 1;
}

int StockData::dateTimeIndex(string d){
  if (d < DateTime[0] || d > DateTime[entries-1]){
    return -1;
  }
  return stringBS(DateTime, d, 0, entries-1);
}
/*
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
  history = H;
  //cout << H << endl;
  if (initialize()) exit(-1);
  populate();
}

int StockData::populate(){
  string his = history;
  string temp;
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
  }
  total = 0;
  for(int i = 0; i < ma; i++){
    total += (High[i]+Low[i])/2;
  }
  entries = ma;
  //cout << total << endl;
  return 0;
}

int StockData::printInfo(){
  cout << name << ": \n";
  //cout << history << endl;
  for(int i = 0; i < entries; i++){
    printf("%i: %s, %f, %f, %f, %f, %i\n",i,DateTime[i].c_str(),
	   Open[i],High[i],Low[i],Close[i],Volume[i]);
  }
  return 0;
}

string StockData::getName(){
  return name;
}

string StockData::lastTime(){
  return DateTime[counter];
}

int StockData::entryCount(){
  return entries;
}
/*
float StockData::variance(int ind){
  return High[ind] - Low[ind];
}
*/
int StockData::countEntries(){
  entries = 0;
  int len = history.length();
  for(int i = 0; i < len; i++){
    if (history[i] == '\n') entries++;
    //cout << i << endl;
  }
  return entries;
}

int StockData::initialize(){
  countEntries();
  if (entries == 0) return 1;
  Open = new float [ma];
  High = new float [ma];
  Low = new float [ma];
  Close = new float [ma];
  Volume = new int [ma];
  DateTime = new string [ma];
  //MA = new float [ma];
  counter = ma-1;
  holding = false;
  return 0;
}

string isolate(string up){
  string temp;
  while(up.length() > up.find("\n")+1){
    temp = up.substr(0,up.find("\n"));
    cout << up.length() << " " << up.find("\n") << endl;
    up.erase(0,up.find("\n")+1);
  }
  cout << temp << up << endl;
  return up;
}

int StockData::update(string up){
  isolate(up);
  /*
  string temp;
  temp = extract(&up);
  //If last date is same. Skip this update.
  if (!DateTime[counter].compare(temp)) return 0;
  counter = (counter + 1) % ma;
  DateTime[counter] = temp;
  temp = extract(&up);
  //cout << temp << endl;
  total -= (High[counter]+Low[counter])/2;
  Open[counter] = stof(temp);
  temp = extract(&up);
  High[counter] = stof(temp);
  temp = extract(&up);
  Low[counter] = stof(temp);
  temp = extract(&up);
  Close[counter] = stof(temp);
  temp = extract(&up);
  Volume[counter] = stoi(temp);
  total += (High[counter]+Low[counter])/2;
  //cout << up;*/
  return 1;
} 

float StockData::movingAve(){
  return total/ma;
}

float StockData::high(){
  return High[counter];
}

float StockData::low(){
  return Low[counter];
}

int StockData::buy(FILE * log){
  purchased = Close[counter];
  fprintf(log,"Bought %s at :%f\n",name.c_str(),purchased);
  holding = true;
  return 0;
}

bool StockData::own(){
  return holding;
}

float StockData::sell(FILE * log){
  float net = Close[counter]-purchased;
  fprintf(log,"Sold %s at :%f for %f dollars profit\n",
	  name.c_str(),Close[counter],net);
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
