#include <iostream>
#include <fstream>

using namespace std;


struct rectab {
unsigned int data[2];
int len;
};
struct rectab _cp1251 (unsigned int symb)
{
rectab result;
if(symb < 128)
{
result.len = 1;
result.data[0] = symb;
result.data[1] = 0;
}
else
{
result.len = 2;
if(symb == 168)
{
symb = 0xd081;
}
else if(symb == 184)
{
symb = 0xd191;
}
else
{
if((symb >= 192)&&(symb <= 239))
{
symb = symb + 0xCFD0;
}
else symb = symb + 0xD090;
}
int tmp = 0;
if(symb < 53504)
{
tmp = 0xd0;
result.data[0] = tmp;
}
else
{
tmp = 0xd1;
result.data[0] = tmp;
}
result.data[1] = symb & 0xff;
}
return result;
} 


int main_() {

ofstream o("cp1251_rectab.cpp");

o<<"rectab cp1251_rectab[256] = {"<<endl;
for(int i=0; i<256; i++) {
rectab r = _cp1251(i);
o<<"\t{ {"<<r.data[0]<<", "<<r.data[1]<<"}, "<<r.len<<" }";
if(i != 255) {
o<<",";
}
o<<endl;
}
o<<"};"<<endl;

o.close();
system("pause");
return 0;
}