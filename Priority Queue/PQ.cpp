#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
using namespace std;



struct data
{
int priority;
string message;
};

class PQ
{
private:
  data*link;
  int N;
public:
  PQ(){ link = new data[100]; N =0;}
  ~PQ(){ delete[]link;}
  void insert(int pr, string str);
  void out();
  void heapsort( int size);
};

void PQ::heapsort( int size)  
{
    int shift = 0; 
    bool flag = false;
    while( (shift + 2) != size ) 		      //Have no input data
    {
	flag = false;
	for ( int i = 0; i < size; i++ )
	{
	    if( i * 2 + 2 + shift < size )
	    {
		if( ( link[i + shift].priority > /*<*/ link[i * 2 + 1 + shift].priority ) || ( link[i + shift].priority > /*<*/ link[i * 2 + 2 + shift].priority ) )
		{
		    if ( link[i * 2 + 1 + shift].priority < /*>*/ link[i * 2 + 2 + shift].priority )
		    {
                data temp = link[i + shift];
                link[i + shift] = link[i * 2 + 1 + shift];
                link[i * 2 + 1 + shift] = temp;
			flag = true;
		    }
		    else if ( link[i * 2 + 2 + shift].priority < /*>*/ link[ i * 2 + 1 + shift].priority)
		         {
                   data temp = link[ i + shift];
                   link[ i + shift] = link[ i * 2 + 2 + shift];
                   link[ i * 2 + 2 + shift] = temp;
		             flag = true;
		         }
		}
    /*additional check for the last two elements
    this check it is possible to sort a pyramid
    consists of a three elements*/
		    if( link[i*2 + 2 + shift].priority < /*>*/ link[i*2 + 1 + shift].priority )
			{
            data temp = link[i*2+1+shift];
            link[i*2+1+shift] = link[i * 2 +2+ shift];
            link[i * 2 +2+ shift] = temp;
                        flag = true;
			}
	   }
	    else if( i * 2 + 1 + shift < size )
	         {
	             if( link[i + shift].priority > /*<*/ link[ i * 2 + 1 + shift].priority )
	             {
                           data temp = link[i + shift];
                           link[i + shift] = link[ i * 2 + 1 + shift];
                           link[ i * 2 + 1 + shift] = temp;
	                 flag = true;
	             }
	         }
	}
	if (!flag) shift++; //shift up

    } 

}

void PQ::insert(int precendence, string str)
{
link[N].priority = precendence;
link[N].message = str;

   N++;
}
 
void PQ::out() {
  
  heapsort(N);
	for (int i = 0; i < N; i++ /* int i = N-1 ; i >= 0; i--*/) { 
		cout << link[i].priority << " - " ;
    cout << link[i].message << endl;
	}
	cout << endl;
}
int main()
{
    setlocale(LC_ALL,"rus");
  PQ pq;
  //        pq.out();
  string buff;
  int prec;
  ifstream in("input.txt", ios::in);
  if (!in.is_open())
  cout << "error opening file"<<endl; 
  ios::pos_type mark = in.tellg();
  while(true)
    {
      ifstream in("input.txt", ios::in);
      in.seekg(0, ios::end);
      int sizef = in.tellg();
      in.seekg(0, ios::beg); 
      in.seekg (mark, ios::beg);
      while(in.good())  
         { 
           if(sizef==mark) break;
          in >> prec; // get priority
          getline(in, buff); // read buff from file
          pq.insert(prec,buff); 
        }
      mark = in.tellg();
      pq.out();
      in.close();
      Sleep(10000);
  }

  
system("pause");
return 0;
}