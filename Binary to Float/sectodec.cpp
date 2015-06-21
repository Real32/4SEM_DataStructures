#include <iostream>
using namespace std;

int main()
{
    int number = 0;
    float* num=NULL;
    char* binary_number="00000000000000000000000000000101";
    cout << binary_number << endl;
    int mult = 1;
    for(int i = 0; i<strlen(binary_number); i++)
    {
         if(number>0) number <<=1;
         if(binary_number[i] == '1') number++;
         else if(binary_number[i] != '0')
         {
             cout << "error" << endl;
           //  exit(1);
         }
    
     }
     num =(float*)&number; //Num2= (float)Num
     cout << number << endl;
     cout << *num << endl;
     system ("pause");
     return 0;
}
