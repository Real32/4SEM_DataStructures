#include <iostream>
#include <fstream>
using namespace std;
int d0byte =0xD0;
int d1byte= 0xD1;
int main()
{
ifstream in("p.txt", ios::in|ios::binary);
  ofstream out("UTF8", ios::out|ios::binary);
  if (!in.good())
{
cerr  << "Error opening"<<endl;
return -1;
}
  unsigned int symbol866=0;
  while(in.good())
  {
  symbol866=in.get();
    if(in.eof())
      break;
  if(symbol866<128)
  {
     out.write((char *)&symbol866,sizeof(char));
  } 
  else 
     {
    if(symbol866==240)
    {
    symbol866=symbol866+0xCF91;
    out.write((char*)&d0byte,sizeof(char));
    } else
  if(symbol866==241)
    {
    symbol866=symbol866+0xCFA0;
    out.write((char*)&d1byte,sizeof(char));
    } else 
  if((symbol866>=128)&&(symbol866<=175))
    {
    symbol866=symbol866+0xD010; //Difference in codes
    out.write((char*)&d0byte,sizeof(char));
    } else
  if((symbol866>=224)&&(symbol866<=239))
      {
      symbol866=symbol866+0xD0A0;
      out.write((char*)&d1byte,sizeof(char));
     }
    out.write((char *)&symbol866,sizeof(char));
   }
}
  cout <<endl;
  in.close();
  out.close();
system("pause");
return 0;
}