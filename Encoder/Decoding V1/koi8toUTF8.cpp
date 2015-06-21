#include <iostream>
#include <fstream>
using namespace std;
int d0byte =0xD0;
int d1byte= 0xD1;
int main()
{
ifstream in("KOI8.txt", ios::in|ios::binary);
  ofstream out("2.txt", ios::out|ios::binary);
  if (!in.good())
{
cerr  << "Error opening"<<endl;
return -1;
}
  unsigned int symbolkoi8=0;
    unsigned int table[]={0x00fe, 0x0020, 0x0021, 0x00f6, 0x0024, 
  0x0025, 0x00f4, 0x0023, 0x00f5, 0x0028, 0x0029, 0x002a, 0x002b,
  0x002c, 0x002d, 0x002e, 0x002f, 0x00ff, 0x00f0, 0x00f1, 0x00f2,
  0x00f3, 0x0026, 0x0022, 0x00fc, 0x00fb, 0x0027, 0x00f9, 0x00fd,
  0x00f9, 0x00f7, 0x00fa, 0x001e, 0x0000, 0x0001, 0x0016, 0x0004,
  0x0005, 0x0014, 0x0003, 0x0015, 0x0008, 0x0009, 0x000a, 0x000b,
  0x000c, 0x000d, 0x000e, 0x000f, 0x001f, 0x0010, 0x0011, 0x0012,
  0x0013, 0x0006, 0x0002, 0x001c, 0x001b, 0x0007, 0x0019, 0x001d, 0x0019, 0x0017, 0x001a};
  while(in.good())
  {
  symbolkoi8=in.get();
    if(in.eof())
      break;
  if(symbolkoi8<128)
  {
     out.write((char *)&symbolkoi8,sizeof(char));
  } 
  else 
     {
    if(symbolkoi8==179)
    {
     symbolkoi8=symbolkoi8+0xCFCE;
     out.write((char*)&d0byte,sizeof(char));
    } else
  if(symbolkoi8==163)
    {
      symbolkoi8=symbolkoi8+0xD0EE;
      out.write((char*)&d1byte,sizeof(char));
    } else 
    {
      symbolkoi8=table[symbolkoi8-0xc0]+0xd090;
        //cout<<hex<<symbolkoi8<<endl;
      if(symbolkoi8<0xd100)
      {
        out.write((char*)&d0byte,sizeof(char));  
      }else
      {
        out.write((char*)&d1byte,sizeof(char));
      }
     }
    out.write((char*)&symbolkoi8,sizeof(char));
   }
}
  cout <<endl;
  in.close();
  out.close();
system("pause");
return 0;
}