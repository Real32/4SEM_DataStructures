#include <iostream>
#include <fstream>

using namespace std;

struct rectab {
unsigned int data[2];
int len;
};
struct rectab _koi8 (unsigned int symb)
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
if(symb == 163)
{
symb = 0xd191;
}else if(symb == 179)
{
symb = 0xd081;
}else if(symb == 192)
{
symb = 0xd18e;
}else if(symb == 193)
{
symb = 0xd0b0;
}else if(symb == 194)
{
symb = 0xd0b1;
}else if(symb == 195)
{
symb = 0xd186;
}else if(symb == 196)
{
symb = 0xd0b4;
}else if(symb == 197)
{
symb = 0xd0b5;
}else if(symb == 198)
{
symb = 0xd184;
}else if(symb == 199)
{
symb = 0xd0b3;
}else if(symb == 200)
{
symb = 0xd185;
}else if(symb == 201)
{
symb = 0xd0b8;
}else if(symb == 202)
{
symb = 0xd0b9;
}else if(symb == 203)
{
symb = 0xd0ba;
}else if(symb == 204)
{
symb = 0xd0bb;
}else if(symb == 205)
{
symb = 0xd0bc;
}else if(symb == 206)
{
symb = 0xd0bd;
}else if(symb == 207)
{
symb = 0xd0be;
}else if(symb == 208)
{
symb = 0xd0bf;
}else if(symb == 209)
{
symb = 0xd18f;
}else if(symb == 210)
{
symb = 0xd180;
}else if(symb == 211)
{
symb = 0xd181;
}else if(symb == 212)
{
symb = 0xd182;
}else if(symb == 213)
{
symb = 0xd183;
}else if(symb == 214)
{
symb = 0xd0b6;
}else if(symb == 215)
{
symb = 0xd0b2;
}else if(symb == 216)
{
symb = 0xd18c;
}else if(symb == 217)
{
symb = 0xd18b;
}else if(symb == 218)
{
symb = 0xd0b7;
}else if(symb == 219)
{
symb = 0xd188;
}else if(symb == 220)
{
symb = 0xd18d;
}else if(symb == 221)
{
symb = 0xd189;
}else if(symb == 222)
{
symb = 0xd187;
}else if(symb == 223)
{
symb = 0xd18a;
}else if(symb == 224)
{
symb = 0xd0ae;
}else if(symb == 225)
{
symb = 0xd090;
}else if(symb == 226)
{
symb = 0xd091;
}else if(symb == 227)
{
symb = 0xd0a6;
}else if(symb == 228)
{
symb = 0xd094;
}else if(symb == 229)
{
symb = 0xd095;
}else if(symb == 230)
{
symb = 0xd0a4;
}else if(symb == 231)
{
symb = 0xd093;
}else if(symb == 232)
{
symb = 0xd0a5;
}else if(symb == 233)
{
symb = 0xd098;
}else if(symb == 234)
{
symb = 0xd099;
}else if(symb == 235)
{
symb = 0xd09a;
}else if(symb == 236)
{
symb = 0xd09b;
}else if(symb == 237)
{
symb = 0xd09c;
}else if(symb == 238)
{
symb = 0xd09d;
}else if(symb == 239)
{
symb = 0xd09e;
}else if(symb == 240)
{
symb = 0xd09f;
}else if(symb == 241)
{
symb = 0xd0af;
}else if(symb == 242)
{
symb = 0xd0a0;
}else if(symb == 243)
{
symb = 0xd0a1;
}else if(symb == 244)
{
symb = 0xd0a2;
}else if(symb == 245)
{
symb = 0xd0a3;
}else if(symb == 246)
{
symb = 0xd096;
}else if(symb == 247)
{
symb = 0xd092;
}else if(symb == 248)
{
symb = 0xd0ac;
}else if(symb == 249)
{
symb = 0xd0ab;
}else if(symb == 250)
{
symb = 0xd097;
}else if(symb == 251)
{
symb = 0xd0a8;
}else if(symb == 252)
{
symb = 0xd0ad;
}else if(symb == 253)
{
symb = 0xd0a9;
}else if(symb == 254)
{
symb = 0xd0a7;
}else if(symb == 255)
{
symb = 0xd0aa;
}else symb = symb + 0xD0CE;
int tmp = 0;
//else
//{
//if((symb >= 192)&&(symb <= 239))
//{
//symb = symb + 0xCFD0;
//}

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

ofstream o("koi8r_rectab.cpp");

o<<"rectab koi8r_rectab[256] = {"<<endl;
for(int i=0; i<256; i++) {
rectab r = _koi8(i);
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
