//Maximillian H Nibler
//max.nibler@gmail.com
//https://github.com/maxnibler/

#include <chrono>
#include <fstream>
#include <sstream>
#include "utils.h"

using namespace std;

string dateTime(){
  time_t tt;
  time(&tt);
  struct tm * ti = localtime(&tt);
  string time = asctime(ti);
  return time;
}

string timeExtract(string* tt){
  int f = (*tt).find(":");
  string ret = (*tt).substr(0,f);
  (*tt).erase(0,f+1);
  return ret;
}

string hyphenate(string date){
  int len = date.length();
  for(int i = 0; i < len; i++){
    if (date[i] == ' '){
      date[i] = '-';
    }
  }
  return date;
}

string splitDateTime(string dt, bool date){
  int len = dt.length();
  int count = 0;
  for(int i = 0; i < len; i++){
    if (dt[i] == ' ') count++;
    if (count == 3){
      count = i;
      break;
    }
  }
  string ret = dt.substr(0,count);
  dt.erase(0,count+1);
  string temp = dt.substr(dt.find(" "),dt.length()-3);
  //cout << temp << endl;
  ret.append(temp);
  ret.erase(ret.find("\n"),ret.find("\n")+1);
  dt.erase(dt.find(" "),dt.length()-1);
  ret = hyphenate(ret);
  if (date) return ret;
  else return dt;
}

string getDate(){
  return splitDateTime(dateTime(),1);
}

string theTime(){
  return splitDateTime(dateTime(),0);
}

string loadPath(){
  ifstream file(".config");
  string temp;
  if (file){
    ostringstream ss;
    ss << file.rdbuf();
    temp = ss.str();
  }
  int f = temp.find("=");
  string path = temp.substr(f+1,temp.find("\n")-2);
  path = path.substr(0,path.find("\n"));
  //cout << path << endl;
  return path;
}

int timeComp(string time1, string time2){
  int h1, h2, m1, m2, s1, s2;
  //cout << time1 << " " << time2 << endl;
  string temp = timeExtract(&time1);
  h1 = stoi(temp);
  temp = timeExtract(&time1);
  m1 = stoi(temp);
  //cout << h1 << " " << m1 << endl;
  temp = timeExtract(&time1);
  s1 = stoi(temp);
  //cout << s1 << endl;
  temp = timeExtract(&time2);
  h2 = stoi(temp);
  temp = timeExtract(&time2);
  m2 = stoi(temp);
  temp = timeExtract(&time2);
  s2 = stoi(temp);
  if (h1 < h2) return 1;
  if (m1 < m2) return 1;
  if (s1 < s2) return 1;
  return 0;
}
