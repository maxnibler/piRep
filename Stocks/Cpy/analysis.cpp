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
  

StockData::StockData(string N, string H){
  name = N;
  //cout << N << ": " << endl;
  history = H;
  //cout << H << endl;
  if (initialize()) exit(-1);
  populate();
}

int StockData::populate(){
  string his = history;
  string temp;
  for(int i = 0; i < entries; i++){
    temp = extract(&his);
    if (temp[0] == '\n') temp.erase(0,1);
    DateTime[i] = temp;
    temp = extract(&his);
    Open[i] = stof(temp);
    //cout << Open[i] << endl;
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
  for(int i = 0; i < entries; i++){
    flux += abs(Close[i] - Open[i]);
  }
  flux /= entries;
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

int StockData::entryCount(){
  return entries;
}

float StockData::variance(int ind){
  return High[ind] - Low[ind];
}

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
  flux = 0;
  countEntries();
  if (entries == 0) return 1;
  Open = new float [entries];
  High = new float [entries];
  Low = new float [entries];
  Close = new float [entries];
  Volume = new int [entries];
  DateTime = new string [entries];
  return 0;
}

int StockData::movingAve(int mins){
  //cout << entries << endl;
  MA = new float [entries-ma];
  float temp = 0, start = 0, total = 0;
  bool breaking = false;
  for(int i = 0; i < ma; i++){
    temp += (High[i] + Low[i]) / 2;
  }
  //cout << temp/(mins) << " " << Close[mins-1] << endl;
  for(int i = 0; i < entries-ma; i++){
    temp -= (High[i]+Low[i])/2;
    temp += (High[i+mins]+Low[i+mins])/2;
    MA[i] = temp/mins;
    if (MA[i] < High[i+mins]){
      if (!breaking){
	breaking = 1;
	start = Low[i+mins+1];
	cout << DateTime[i+mins] << " ";
      }else if (MA[i] > Low[i+mins]){
	breaking = 0;
	total += High[i+mins+1]-start;
	cout << DateTime[i+mins+1] << " " << High[i+mins+1]-start
	     << endl;
      }
    }
  }
  cout << "total %: " << total/185*100<< endl;
  return 0;
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
