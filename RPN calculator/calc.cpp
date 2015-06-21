#include "stack.h"

bool is_operand(char operand);
bool is_operator(char op);
 int HigherPrecedence(char op1, char op2);
 string InfixToPostfix(string expression);
void calculate(string input);
int main() 
{
    //string expression="(4+8)*(6-5)/((3-2)*(2+2))"; //4 8 + 6 5 - * 3 2 Ц 2 2 + * /
    // string expression="(300+23)*(43-21)/(84+7)"; //300 23 + 43 21 - * 84 7 + /
    //string expression="3+4*5/6"; // 3 4 5 * 6 / +
    string expression ="22.11 + 8.9";
    cout<<"Infix Expression = "<<expression<<endl;
    // string expression;
    //getline(cin,expression); //for console input
    string postfix = InfixToPostfix(expression);
    cout<<"Output = "<<postfix<<endl;
    //cout << inp << endl;
    //cout<<"Calculate = "<<calculate(postfix)<<endl;
    calculate( postfix);
    system("pause");
}



string InfixToPostfix(string expression)
{
  int N =expression.length();
	Stack<char> S(N);
	string postfix = ""; //Postfix is an empty string
	for(int i = 0;i< N;i++) {

		if(expression[i] == ' ') continue; 
     if(expression[i] == '.')
        postfix+=".";
		else if(is_operator(expression[i])) 
		{
      postfix+=" "; //for a big numbers adding space
			while(!S.empty() && S.top() != '(' && HigherPrecedence(S.top(),expression[i]))
			{
				postfix+= S.top();
        postfix+=" ";
				S.pop();
			}
			S.push(expression[i]);
		}

		else if(is_operand(expression[i]))
		{
			postfix +=expression[i];

		}
 
		else if (expression[i] == '(') 
		{
			S.push(expression[i]);
		}
 
		else if(expression[i] == ')') 
		{
			while(!S.empty() && S.top() !=  '(') {
        postfix+=" ";
				postfix += S.top();
				S.pop();
			}
			S.pop();
		}
	}
 
	while(!S.empty()) {
    postfix+=" ";
		postfix += S.top();
		S.pop();
	}
 
	return postfix;
}
 

bool is_operand(char operand) 
{
	if(operand >= '0' && operand <= '9') return true;

	return false;
}
 

bool is_operator(char op)
{
	if(op == '+' || op == '-' || op == '*' || op == '/')
		return true;
 
	return false;
}
 
int GetOperatorPrecedence(char op)
{
	int weight = 0; 
	switch(op)
	{
	case '+':
	case '-':
		weight = 1;
    break;
	case '*':
	case '/':
    weight = 2;
	}
	return weight;
}

int HigherPrecedence(char op1, char op2)
{
	int op1Precedence = GetOperatorPrecedence(op1);
	int op2Precedence = GetOperatorPrecedence(op2);
	return op1Precedence >= op2Precedence ?  true: false;
}



void calculate(string input) //кос€к
{
  int N =input.length();
 Stack<float> S(N);
 float digit=0;
 float result=0;
    for (int i = 0; i < N; i++)
      {
        if(input[i]==' ') continue;
             switch(input[i])
        {
            case '+':{ // if +
                float op1=S.top();
                S.pop();
                float op2=S.top();
                S.pop();
                 result=op2 + op1;
                S.push(result);
            }break;
              case '-':{ 
                float op1=S.top();
                S.pop();
                float op2=S.top();
                S.pop();
                 result=op2 - op1;
                S.push(result);
            }break;
                case '*':{ 
                float op1=S.top();
                S.pop();
                float op2=S.top();
                S.pop();
                 result=op2 * op1;
                S.push(result);
            }break;
                  case '/':{ 
                float op1=S.top();
                S.pop();
                float op2=S.top();
                S.pop();
                if(op1!=0)
                 result=op2 / op1;
                else 
                  {cerr<<"Division by zero!"<<endl;
                exit(1); }
                S.push(result);
            }break;
            
            default: // if digit
               {
                 float digit=0;
                 float grade=10;
                 char flag=0;
                 int j;
                 for(j=0; ;j++)
                 {

                   if(input[i+j]=='.')
                   {
                     flag=1;
                     continue;
                   }
                    if((input[i+j]>='0')&&(input[i+j]<='9'))
                    {
                      if(!flag)
                      {
                        digit*=10;
                        digit+=(float)(input[i+j]-'0');//by explicit casting
                      }
                      else
                      {
                        digit+=(input[i+j]-'0')/grade;
                         grade*=10;
                      }

                    }

                    else break;
                 }
                 i+=j;
                 S.push(digit);
        }
      }
    }
    cout << result << endl;
}