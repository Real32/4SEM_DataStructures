#include <iostream>
#include <fstream>
#include <windows.h>
#include <stdio.h>
#define HEIGHT 6 
#define WIDTH 8
#define NUM ( WIDTH * HEIGHT )
using namespace std;

unsigned char map[HEIGHT][WIDTH]; //Карта
struct coordinate
{
int unit_x;
int unit_y;

int target_x;
int target_y;
int target_count;

int Box_X;
int Box_Y;
int Box_count;
}coord;


unsigned long int factorial(unsigned long int value);
unsigned long int posListMax = factorial(NUM) / 2;

unsigned long int factorial(unsigned long int value) {
	if(value < 2) {
		return 1;
	}
	return value * factorial(value - 1);
}

void load_map(ifstream & in)
{

int symbol = 0;
  for (int j=0; j < HEIGHT; j++)
    {
      for(int i=0; i < WIDTH; i++)
        {
        map[i][j]=in.get();
      //cout<< (char)in.get();
        }
	    in.get();
    }
}

void show_map(unsigned char (&arr)[HEIGHT][WIDTH])
{ 
  cout<<endl;
    for (int j=0; j <HEIGHT; j++)
    {
      for(int i=0; i < WIDTH; i++)
      {
          cout<<arr[i][j];
      }
	  cout<<endl;
  }
}

void search_objects()
{
     show_map(map);
     coord.target_count=0;
   for (int j=0; j <HEIGHT; j++)
    {
      for(int i=0; i < WIDTH; i++)
      {
         if(map[i][j]=='@')
         { 
            cout<<"@ "<<i <<" ; "<< j <<" Unit";cout << endl;
            coord.unit_x=i;
            coord.unit_y=j;
         }
        
         if(map[i][j]=='%')
          { cout<<"% "<<i <<" ; "<< j <<" Box";
            cout << endl;
             coord.Box_X=i;
             coord.Box_Y=j;
             coord.Box_count++;
          }
         if(map[i][j]=='+')
           { 
             cout<<"+ "<<i <<" ; "<< j<<" Target";
             cout << endl;
             coord.target_x=i;
             coord.target_y=j;
             coord.target_count++;
          }
      }
    }
   cout << endl;
}

int check_exit()
{
coord.target_count--;
  if(coord.target_count==0)
  {
    cout<<endl<< "====Solve has found!====" << endl << endl;
    show_map(map);
    system("pause");
    return 0;
  }
}

bool move_down()
{
bool can_move = false;
//Движение юнита
  if(map[coord.unit_x][coord.unit_y+1]==' ')
    {
      map[coord.unit_x][coord.unit_y] = ' ';   //  убрать объект  со старой координаты
      coord.unit_y++;                         // изменяем координаты
      map[coord.unit_x][coord.unit_y] = '@'; // добавляю объект  на новом месте
      can_move=true;
    }
//Движение юнита+коробки
  if((can_move==false)&&(map[coord.unit_x][coord.unit_y+1]=='%')&&(map[coord.unit_x][coord.unit_y+2]==' '))
    {
      map[coord.unit_x][coord.unit_y] = ' ';   //  убрать объект  со старой координаты
      coord.unit_y++;                         // изменяем координаты
      map[coord.unit_x][coord.unit_y] = '@'; // добавляю объект  на новом месте

         int box_y=coord.unit_y;
         box_y++;                         // изменяем координаты
         map[coord.unit_x][box_y] = '%'; // добавляю объект  на новом месте
         can_move=true;
    }
//Коробка перед целью
  if((can_move==false)&&(map[coord.unit_x][coord.unit_y+1]=='%')&&(map[coord.unit_x][coord.unit_y+2]=='+'))
    {
      map[coord.unit_x][coord.unit_y] = ' ';   //  убрать объект  со старой координаты
      coord.unit_y++;                         // изменяем координаты
      map[coord.unit_x][coord.unit_y] = '@'; // добавляю объект  на новом месте

         int box_y=coord.unit_y;
         box_y++;                         // изменяем координаты
         map[coord.unit_x][box_y] = 'X'; // добавляю объект  на новом месте
         can_move=true;
         check_exit();
    }
    return can_move;
}

bool move_up()
{
  bool can_move = false;
  if(map[coord.unit_x][coord.unit_y-1]==' ')
    {
      map[coord.unit_x][coord.unit_y] = ' ';   //  убрать объект  со старой координаты
      coord.unit_y--;                          // изменяем координаты
      map[coord.unit_x][coord.unit_y] = '@'; // добавляю объект  на новом месте
      can_move = true;
    }

  if((can_move==false)&&(map[coord.unit_x][coord.unit_y-1]=='%')&&(map[coord.unit_x][coord.unit_y-2]==' '))
    {
      map[coord.unit_x][coord.unit_y] = ' ';   //  убрать объект  со старой координаты
      coord.unit_y--;                         // изменяем координаты
      map[coord.unit_x][coord.unit_y] = '@'; // добавляю объект  на новом месте

         int box_y=coord.unit_y;
         box_y--;                         // изменяем координаты
         map[coord.unit_x][box_y] = '%'; // добавляю объект  на новом месте
         can_move=true;
    }

    if((can_move==false)&&(map[coord.unit_x][coord.unit_y-1]=='%')&&(map[coord.unit_x][coord.unit_y-2]=='+'))
    {
      map[coord.unit_x][coord.unit_y] = ' ';   //  убрать объект  со старой координаты
      coord.unit_y--;                         // изменяем координаты
      map[coord.unit_x][coord.unit_y] = '@'; // добавляю объект  на новом месте

         int box_y=coord.unit_y;
         box_y--;                         // изменяем координаты
         map[coord.unit_x][box_y] = 'X'; // добавляю объект  на новом месте
         can_move=true;
         check_exit();
    }
    return can_move;
}

bool move_left()
{
  bool can_move = false;
  if(map[coord.unit_x - 1][coord.unit_y]==' ')
    {
      map[coord.unit_x][coord.unit_y] = ' ';   //  убрать объект  со старой координаты
      coord.unit_x--;                         // изменяем координаты
      map[coord.unit_x][coord.unit_y] = '@'; // добавляю объект  на новом месте
      can_move = true;
    }

   if((can_move==false)&&(map[coord.unit_x - 1][coord.unit_y]=='%')&&(map[coord.unit_x - 2][coord.unit_y]==' '))
    {
      map[coord.unit_x][coord.unit_y] = ' ';   //  убрать объект  со старой координаты
      coord.unit_x--;                         // изменяем координаты
      map[coord.unit_x][coord.unit_y] = '@'; // добавляю объект  на новом месте

         int box_x=coord.unit_x;
         box_x--;                         // изменяем координаты
         map[box_x][coord.unit_y] = '%'; // добавляю объект  на новом месте
         can_move=true;
    }
 
   if((can_move==false)&&(map[coord.unit_x - 1][coord.unit_y]=='%')&&(map[coord.unit_x - 2][coord.unit_y]=='+'))
    {
      map[coord.unit_x][coord.unit_y] = ' ';   //  убрать объект  со старой координаты
      coord.unit_x--;                         // изменяем координаты
      map[coord.unit_x][coord.unit_y] = '@'; // добавляю объект  на новом месте

         int box_x=coord.unit_x;
         box_x--;                         // изменяем координаты
         map[box_x][coord.unit_y] = 'X'; // добавляю объект  на новом месте
         check_exit();
         can_move=true;
    }
 
    return can_move;
}

bool move_right()
{
  bool can_move = false;
  if(map[coord.unit_x + 1][coord.unit_y]==' ')
    {
      map[coord.unit_x][coord.unit_y] = ' ';   //  убрать объект  со старой координаты
		  coord.unit_x++;                         // изменяем координаты
		  map[coord.unit_x][coord.unit_y] = '@'; // добавляю объект  на новом месте
      can_move=true;
    }
  if((can_move==false)&&(map[coord.unit_x + 1][coord.unit_y]=='%')&&(map[coord.unit_x + 2][coord.unit_y]==' '))
    {
      map[coord.unit_x][coord.unit_y] = ' ';   //  убрать объект  со старой координаты
      coord.unit_x++;                         // изменяем координаты
      map[coord.unit_x][coord.unit_y] = '@'; // добавляю объект  на новом месте

         int box_x=coord.unit_x;
         box_x++;                         // изменяем координаты
         map[box_x][coord.unit_y] = '%'; // добавляю объект  на новом месте
         can_move=true;
    }

   if((can_move==false)&&(map[coord.unit_x + 1][coord.unit_y]=='%')&&(map[coord.unit_x + 2][coord.unit_y]=='+'))
    {
      map[coord.unit_x][coord.unit_y] = ' ';   //  убрать объект  со старой координаты
      coord.unit_x++;                         // изменяем координаты
      map[coord.unit_x][coord.unit_y] = '@'; // добавляю объект  на новом месте

         int box_x=coord.unit_x;
         box_x++;                         // изменяем координаты
         map[box_x][coord.unit_y] = 'X'; // добавляю объект  на новом месте
         check_exit();
         can_move=true;
    }
    return can_move;
}


void copy(unsigned char (&arr)[HEIGHT][WIDTH])
{
for (int j=0; j <HEIGHT; j++)
  {
    for(int i=0; i < WIDTH; i++)
      {
          arr[i][j]=map[i][j];
      }
   cout<<endl;
  }

for (int j=0; j <HEIGHT; j++)
  {
    for(int i=0; i < WIDTH; i++)
      {
          cout<<arr[i][j] ;
      }
   cout<<endl;
  }
}



int main()
{
ifstream in("map.txt", ios::in);
load_map(in);
search_objects();
move_left();
show_map(map);
move_left();
show_map(map);
move_left();
show_map(map);
move_left();
show_map(map);

  in.close();
system("pause");
return 0;

/* 
 while(TRUE)
    {
        if(GetAsyncKeyState(VK_LEFT))
        {
            keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0);//Отжимаем кнопку
            move_left();
            system("cls");
            show_map(map);
            
        }
        if(GetAsyncKeyState(VK_RIGHT))
        {
            keybd_event(VK_RIGHT, 0, KEYEVENTF_KEYUP, 0);//Отжимаем кнопку
            move_right();
            system("cls");
            show_map(map);
        }
        if(GetAsyncKeyState(VK_UP))
        {
            keybd_event(VK_UP, 0, KEYEVENTF_KEYUP, 0);//Отжимаем кнопку
            move_up();
            system("cls");
            show_map(map);
        }
        if(GetAsyncKeyState(VK_DOWN))
        {
            keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0);//Отжимаем кнопку
            move_down();
            system("cls");
            show_map(map);
        }
    } */ 
}
