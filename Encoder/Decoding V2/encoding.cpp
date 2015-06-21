#include "encoding_table.h"
#include <iostream>
#include <fstream>


int detect_code(ifstream &in)
{
unsigned char symfile=NULL;
int j=0;
int sum=0;
int range=NULL;
int symbol=0;

  while(!in.eof())
  {
  in>>symfile;
  symbol = (int)symfile;
  if((symbol>127)&&(symbol<255))
   {
     sum+=symbol;
    j++;
   }
  }
  range = sum/j;
  in.clear();//clear flags
//in.seekg(0, ios::beg); // in a beginning
  in.seekg(0, in.beg);
  return range;
}

void encoding(ifstream&in,rectab*encoding_table)
{
//
  ofstream out("UTF8.txt", ios::out| ios::binary);
unsigned int symbol=0;
while(in.good())
{
  symbol=in.get();
  if(in.eof())
      break;
  if(encoding_table[symbol].len==1)
  {
    out.write((char*)(&encoding_table[symbol].data[0]),sizeof(char));
  } 
  else
  {
    out.write((char*)(&encoding_table[symbol].data[0]),sizeof(char));
    out.write((char*)(&encoding_table[symbol].data[1]),sizeof(char));
  }
}
in.close();
out.close();
}

int main()
{
    int choice = NULL;
  ifstream in("koi8.txt");
    if (in.good())
{
//  detect_code(in);
  choice =  detect_code(in);
  if ((choice >=180)&&(choice<=200))
  { 
    cout << "cp866" << endl;
    encoding(in,cp866_rectab);
  } else{
  if ((choice >=230)&&(choice<=239))
  { 
    cout << "cp1251" << endl;
    encoding(in,cp1251_rectab);
  } else {
  if ((choice >=200)&&(choice<=209))
  { 
    cout << "koi8-r" << endl;
    encoding(in,koi8r_rectab);
  } 
  else {cout << "Undefined. Error" << endl;
        return 1;}
  }
 }
}else cerr  << "Error"<<endl;

system("pause");
return 0;
}