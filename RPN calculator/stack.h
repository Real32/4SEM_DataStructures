#include<iostream>
#include<string>
 
using namespace std;

template <typename T>
class Stack
{
private:
    T *stackPtr; // poiter to stack
    int size; // stack size
public:
    Stack(int size);
    ~Stack(); // destructor
    bool empty();
    void push(const T); // push to stack
    T pop(); // pop from stack
    T top();// show last element
};

template <typename T>
Stack<T>::Stack(int Maxsize)
{
    stackPtr = new T[Maxsize]; // allocate memory
    size=0;
}
 
// destructor
template <typename T>
Stack<T>::~Stack()
{
    delete [] stackPtr; //delete stack
}
 
template <typename T>
void Stack<T>::push(T value)
{
    stackPtr[++size] = value; //get element to stack
}

template <typename T>
T Stack<T>::pop()
{
   if (size == 0)
        return false; // stack is empty
    return stackPtr[--size] ;  // GET OUT OF HERE
}

template <typename T>
T Stack<T>::top()
{
  return stackPtr[size];
}


template <typename T>
bool Stack<T>::empty()
{
  if(size==0)
  return 1;
         else return 0;
}