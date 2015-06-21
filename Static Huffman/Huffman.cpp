#include <iostream>
#include <fstream>
#include <cstring>
#include <time.h>
#include <vector>
#include <map>
using namespace std;


struct tree
{
 unsigned long frequency;
 unsigned char symbol;
 tree * left;
 tree * right;
};


  void get_statistic(ifstream&is);
  void BuildCodeTable(tree*root);
  tree* create_tree(tree *psym[],int k);
  void makeCodes(tree *root);
  void CodeHuffman(char*input,char* output);
  void DeCodeHuffman(char*input,char* output);


unsigned long mystat[256]={0};
tree simbols[256] ={0};//initialize array for simbols 
tree *psym[256];//pointers
int NUM=0; int summir=0;
/*################################################################################*/

vector<bool> code;
map<char,vector<bool>>table;  /* map change to char!*/

void BuildCodeTable(tree*root) //Create code table
{
  if(root->left!=NULL)
  {code.push_back(0);BuildCodeTable(root->left);}
  if(root->right!=NULL)
  {code.push_back(1);BuildCodeTable(root->right);}
  if((root->right==NULL) &&(root->left==NULL)) table[root->symbol]=code;
  code.pop_back();
}

tree* create_tree(tree *psym[],int k) //Create tree
{
    int i, j;
    tree *temp;
    temp = new tree;
    temp->frequency = psym[k-1]->frequency+psym[k-2]->frequency;
    temp->left = psym[k-1];
    temp->right = psym[k-2];
    if ( k == 2 )
        return temp;
    else 
    {
 
      for ( i = 0; i < k; i++)
        if ( temp->frequency > psym[i]->frequency )
        {
          for( j = k - 1; j > i; j--)
          psym[j] = psym[j-1]; 
          psym[i] = temp;
          break;
        } 
      }
  return create_tree(psym,k-1);

}


 void get_statistic(ifstream & is) //Get statistic
{
  int i, j;

 	unsigned char x = 0;
	while(true) 
  {
    is.read((char*)&x,sizeof(char));
		if(is.eof()) break;
    mystat[x]++;
	}

  for(int i=0; i<256; i++) //Del zero from array
  {  
    if(mystat[i]!=0)
    { 
      simbols[NUM].frequency = mystat[i];
      simbols[NUM].symbol = (char)i;
      NUM++;
    }
  }
 
  for ( i = 0; i < NUM; i++) 
    psym[i] = &simbols[i];
  //Sort \/
  tree tempp;
  for ( i = 1; i < NUM; i++)
    for ( j = 0; j < NUM - 1; j++)
      if ( simbols[j].frequency < simbols[j+1].frequency )
      {
        tempp = simbols[j];
        simbols[j] = simbols[j+1];
        simbols[j+1] = tempp;
      }
 

    for( i=0;i<NUM;i++) 
    {

      summir+=simbols[i].frequency; 
      printf("CODE= %d\ Frequency= %d\t Symbol = %c\t\n",simbols[i].symbol,
      simbols[i].frequency,psym[i]->symbol,i);
    }
  printf("\n Symbols = %d\t types = %d\n",NUM,summir);

 }

 

void CodeHuffman(char*input,char* output) //Code
{
  ifstream is(input, ios::in|ios::binary);
  ofstream out(output, ios::out|ios::binary); 
   
  get_statistic(is);
  tree *symbols = new tree;
  tree *root = create_tree(psym,NUM);
  BuildCodeTable(root);
  
  is.clear();//clear flags
  is.seekg(0, is.beg);//in a beginnig
  out<<"HUF ";
for(int i=0;i<256;i++)
	{
		out.write((char*)&(mystat[i]),sizeof(unsigned long));
	}
    cout << endl;
    unsigned char c =0;
    int count = 0;
    char buf=0; 
    char last=0;

   while(!is.eof())
   {
      is.read((char*)&c,sizeof(char));
      vector<bool> x = table[c];
      for (int  i = 0; i < x.size(); i++)
      {
         buf = buf | x[i]<<(7-count);
         count++;
         if(count==8) { count=0; out<<buf;buf=0;}
      }//for
    }
   if(count <8)
   {
     char last=0;
     last = last| buf << (7-count);
     out<<buf;
   }
   is.close();
   out.close();
}



void DeCodeHuffman(char*input,char* output) //Decode
{
   ifstream huf(input, ios::in|ios::binary);
   ofstream file(output, ios::out|ios::binary);

   if(huf.get()=='H'&&huf.get()=='U'&&huf.get()=='F'&&huf.get()==' ') //Read key
	  {

      for(int i=0; i<256;i++)
       { 
         huf.read((char*)&mystat[i],sizeof(unsigned long));
       }
      for(int i=0; i<256; i++) // Del zero
       { 
         if(mystat[i]!=0)
         { 
          simbols[NUM].frequency = mystat[i];
           simbols[NUM].symbol = (char)i;
          NUM++;
         }
      }
  for ( int i = 0; i < NUM; i++) 
  psym[i] = &simbols[i];
  //Sort \/
  tree tempp;
  for ( int i = 1; i < NUM; i++)
  for ( int j = 0; j < NUM - 1; j++)
  if ( simbols[j].frequency < simbols[j+1].frequency )
  {
    tempp = simbols[j];
    simbols[j] = simbols[j+1];
    simbols[j+1] = tempp;
  }
    int summir=0;
    for(int i=0;i<NUM;i++)
  {

    summir+=simbols[i].frequency; 
    printf("CODE= %d\ Frequency= %d\t Symbol = %c\t\n",simbols[i].symbol,
    simbols[i].frequency,psym[i]->symbol,i);
  }
  printf("\n Symbols = %d\t types = %d\n",NUM,summir);

  tree *symbols = new tree;
  tree *root = create_tree(psym,NUM);
  tree*p=root;
  BuildCodeTable(root);

int count=0; char byte=0; // Start decode
huf.read((char*)&byte,sizeof(char));
  while(!huf.eof() && summir!=0)
    {
      bool b=byte & (1<<(7-count));
      if(b) p=p->right; else p=p->left;
      if ((p->left==NULL && p->right==NULL ))
      {
        file.write((char*)&(p->symbol),sizeof(char));
        summir--;
        p=root;
      }
      count++;
      if(count==8) {count=0; huf.read((char*)&byte,sizeof(char));}
    }
  }
}


int main( int argc, char *argv[], char *envp[] )
{
  setlocale(LC_ALL,"rus");
  clock_t time;
  time = clock();


    CodeHuffman("Krale – Combat.mp3","out.huf");
    //   DeCodeHuffman("out.huf","encode.png");
    cout << endl;
    time = clock() - time;
  printf("\nTIMER: %f\n", (double)time/CLOCKS_PER_SEC); //Execution time
  system("pause");
	return 0;
}
