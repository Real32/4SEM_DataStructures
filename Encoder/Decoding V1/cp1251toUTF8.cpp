#include <iostream>
#include <fstream>
using namespace std;
int d0byte =0xD0;
int d1byte= 0xD1;
int main()
{
ifstream in("cp1251.txt", ios::in|ios::binary);
  ofstream out("UTF8", ios::out|ios::binary);
  if (!in.good())
{
cerr  << "Error opening"<<endl;
return -1;
}
  unsigned int symbol1251=0;
  while(in.good())
  {
  symbol1251=in.get();
    if(in.eof())
      break;
  if(symbol1251<128)
  {
     out.write((char *)&symbol1251,sizeof(char));
  } 
  else 
     {
    if(symbol1251==168)
    {
    symbol1251=symbol1251+0xCFD9;
    out.write((char*)&d0byte,sizeof(char));
    } else
  if(symbol1251==184)
    {
    symbol1251=symbol1251+0xCFD9;
    out.write((char*)&d1byte,sizeof(char));
    } else 
  if((symbol1251>=128)&&(symbol1251<=239))
    {
    symbol1251=symbol1251+0xCFD0; //Difference in codes
    out.write((char*)&d0byte,sizeof(char));
    } else
  if((symbol1251>=240)&&(symbol1251<=255))
      {
      symbol1251=symbol1251+0xCF90;
      out.write((char*)&d1byte,sizeof(char));
     }
    out.write((char *)&symbol1251,sizeof(char));
   }
}
  cout <<endl;
  in.close();
  out.close();
system("pause");
return 0;
}