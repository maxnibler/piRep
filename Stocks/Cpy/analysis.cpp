//Maximillian H Nibler
//max.nibler@gmail.com
//https://github.com/maxnibler/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
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
  for(int i = 0; i <= entries-ma; i++){
    his.erase(0,his.find("\n"));
    //cout << i << " " << entries << endl;
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
  return 0;
}

int StockData::update(string up){
  counter = (counter + 1) % ma;
  string temp;
  temp = extract(&up);
  DateTime[counter] = temp;
  temp = extract(&up);
  cout << temp << endl;
  /*
  total -= (High[counter]+Low[counter])/2;
  DateTime[counter] = d;
  Open[counter] = o;
  Close[counter] = c;
  High[counter] = h;
  Low[counter] = l;
  Volume[counter] = v;
  total += (h+l)/2;
  */
  cout << up;
  return 0;
} 

float StockData::movingAve(){
  return total/ma;
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
