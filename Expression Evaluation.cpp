#include <iostream>
#include<fstream>
using namespace std;

template <typename T>
class stack{
	T *data;
	int size;
	int top;
public:
	stack(){
		size=0;
		data=new T[size];
		top=0;
	}
	
	stack(int s){
		size=s;
		data=new T[size];
		top=0;
	}

	bool isFull(){
		return (top==size);
	}
	
	bool isEmpty(){
		return (top==0);
	}
	
	bool push(T x){
		if(isFull())
			grow();
		data[top++]=x;
		return true;
	}
	
	bool pop(T &x){
		if(isEmpty())
			return false;
		x=data[--top];
		return true;
	}

	void print(){
		bool isNumber=false;
		for (int i=0;i<top;i++){
			if(isNumber==false)
				cout<<' ';
			if(data[i]>='0' && data[i]<='9')
				isNumber=true;
			else
				isNumber=false;
			if(data[i]=='#')
				continue;
			cout<<data[i];
		}
		cout<<endl;
	}
	
	void grow(){
		T *temp=new T[size];
		for (int i=0;i<size;i++)
			temp[i]=data[i];
		delete data;
		data=new T[++size];
		for (int i=0;i<size-1;i++)
			data[i]=temp[i];
		delete temp;
	}

	void reverseInOrder(){
	
		char x;
		stack<char> temp(size);
		while(!isEmpty()){
			pop(x);
			temp.push(x);
		}
		*this=temp;
	}
};

bool checkPrecedence(char a,char b)
{
	if(a=='(' || b=='(')
		return true;
	if( (a=='*' || a=='/') && (b=='+' || b=='-') )
		return true;
	return false;
}

stack<char> POSTFIX(char input[]){
	
	stack<char> post_fix;
	stack<char> operators;
	char x;
	bool isNumber=false;
	for (int i=0;i<strlen(input);i++){
		if(input[i]>='0' && input[i]<='9'){
			post_fix.push(input[i]);
			isNumber=true;
		}
		else{
			if(isNumber==true){
				x='#';
				post_fix.push(x);
				isNumber=false;
			}
			if(input[i]==')'){
				operators.pop(x);
				while(x!='('){
					post_fix.push(x);
					operators.pop(x);
				}
			}
			else{
				if(input[i]=='+' || input[i]=='-' || input[i]=='*' || input[i]=='/' || input[i]=='('){
					if(operators.isEmpty())
						operators.push(input[i]);
					else{
						while(!operators.isEmpty()){
							operators.pop(x);
							if(checkPrecedence(input[i],x)){
								operators.push(x);
								operators.push(input[i]);
								break;
							}
							else
								post_fix.push(x);
						}
						if(operators.isEmpty())
							operators.push(input[i]);
					}
				}
			}
		}
	}
	while(!operators.isEmpty()){
		operators.pop(x);
		if(x=='(')
			continue;
		post_fix.push(x);
	}
	return post_fix;
}

float EVALUATE(stack<char> post_fix)
{
	float num=0,temp_num=0,op1,op2,result=0;
	char x;
	bool isNumber;
	stack<float> operands;
	while(!post_fix.isEmpty()){
		post_fix.pop(x);
		if(x>='0' && x<='9'){
			isNumber=true;
			temp_num=x-48;
			num*=10;
			num+=temp_num;
		}
		else{
			if(isNumber==true){
				operands.push(num);
				isNumber=false;
				num=0;
			}
			if(x!='#'){
				operands.pop(op2);
				operands.pop(op1);
				if(x=='+')
					result=op1+op2;
				if(x=='-')
					result=op1-op2;
				if(x=='*')					
					result=op1*op2;
				if(x=='/')
					result=op1/op2;
				
				operands.push(result);
			}
		}
	}
	operands.pop(result);
	return result;
}

int main()
{
	char input[1000],x;
	stack<char> post_fix;
	cout<<"How do you want to give input\t(1)File\t(2)Keyboard\n";
	cin>>x;
	if(x=='1'){
		ifstream fin("input.txt");
		fin.getline(input,999);
	}
	else{
		cin.ignore();
		cin.getline(input,999);
	}
	system("cls");
	cout<<"--> IN-FIX:    "<<input;
	post_fix=POSTFIX(input);
	cout<<"\n\n\n--> POST-FIX:  ";
	post_fix.print();
	post_fix.reverseInOrder();
	cout<<"\n\n--> ANSWER:    "<<EVALUATE(post_fix)<<"\n\n\n\n";
	system("pause");
	return 0;
}