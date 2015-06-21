#include <iostream>
#include <fstream>
#include <stdio.h>
using namespace std;

int detect_code()
{
ifstream in("cp1251.txt");
  if (!in.good())
{
cerr  << "Error"<<endl;
return -1;
}
unsigned char symfile=NULL;
int j=0;
int sum=0;
int range=NULL;
int symbol=0;
in.seekg(0, ios::beg); // in a beginning
  while(in.good())
  {
  in>>symfile;
  symbol = (int)symfile;
    if(in.eof())
      break;
  if((symbol>127)&&(symbol<255))
   {
     sum+=symbol;
    j++;
   }
  }
  range = sum/j;
  in.close();
  return range;
}
int main()
{
  detect_code();
  setlocale(LC_ALL, "Russian");
  int choice = NULL;
  choice =  detect_code();
  if ((choice >=220)&&(choice<=229))
  { 
    cout << "cp866" << endl;
  } else{
  if ((choice >=230)&&(choice<=239))
  { 
    cout << "cp1251" << endl;
  } else {
  if ((choice >=200)&&(choice<=209))
  { 
    cout << "koi8-r" << endl;
  } 
  else {cout << "another code" << endl;
          return 1;}
  }
}
system("pause");
return 0;
}