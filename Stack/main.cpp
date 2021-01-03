#include <iostream>

using namespace std;

class Stack
{
private:
	struct Node
	{
		char data;
		Node* next;
		Node(char _data) { data = _data; next = nullptr; }
	};

	Node* top;

public:
	Stack();
	~Stack();

	void Push(char _data);
	char Pop();
	char Peek(int index);

	bool IsEmpty();
	bool IsFull();

	void Display();
};

string Postfix(string exp);
bool IsOperand(char x);
int Pre_out(char x);
int Pre_in(char x);

int Evaluate(string exp);

int main()
{
	string exp;

	cout << "Enter Mathematical expression (no spaces): ";
	cin >> exp;

	string postFix = Postfix(exp);

	cout << postFix << endl;

	cout << Evaluate(postFix) << endl;

	return 0;
}

Stack::Stack()
{
	top = nullptr;
}

Stack::~Stack()
{
	Node* ptr = top;
	while (ptr != nullptr)
	{
		Node* del = ptr;
		ptr = ptr->next;
		delete del;
	}
}

void Stack::Push(char _data)
{
	Node* add = new Node(_data);
	if (top == nullptr)
		top = add;
	else
	{
		add->next = top;
		top = add;
	}
}

char Stack::Pop()
{
	if (top == nullptr)
		return -1;
	else
	{
		Node* del = top;
		char data = del->data;
		top = top->next;
		delete del;

		return data;
	}
}

char Stack::Peek(int index)
{
	Node* ptr = top;
	int count = 0;
	while (count < index && ptr != nullptr)
	{
		count++;
		ptr = ptr->next;
	}

	if (ptr == nullptr)
		return -1;
	else
		return ptr->data;
}

bool Stack::IsEmpty()
{
	if (top == nullptr)
		return true;
	else
		return false;
}

bool Stack::IsFull()
{
	Node* node = new Node('0');

	if (node == nullptr)
	{
		delete node;
		return true;
	}
	else
	{ 
		delete node;
		return false;
	}
}

void Stack::Display()
{
	Node* ptr = top;
	while (ptr != nullptr)
	{
		cout << ptr->data << " ";
		ptr = ptr->next;
	}
	cout << endl;
}

string Postfix(string exp)
{
	Stack s;
	string result = "";
	int i = 0;

	while (exp[i] != '\0')
	{
		if (IsOperand(exp[i]))
		{
			result += exp[i++];
		}
		else
		{
			if (s.IsEmpty())
				s.Push(exp[i++]);
			else if (Pre_out(exp[i]) == 0 && Pre_in(s.Peek(0)) > Pre_out(exp[i]))
				result += s.Pop();
			else if (Pre_out(exp[i]) == Pre_in(s.Peek(0)))
			{
				s.Pop();
				i++;
			}
			else if (Pre_out(exp[i]) > Pre_in(s.Peek(0)))
				s.Push(exp[i++]);
			else
				result += s.Pop();
		}
	}

	while (!s.IsEmpty())
		result += s.Pop();

	return result;
}

bool IsOperand(char x)
{
	if (x == '+' || x == '-' || x == '*' || x == '/' || x == '(' || x == ')' || x == '^')
		return false;
	else
		return true;
}

int Pre_out(char x)
{
	if (x == '+' || x == '-')
		return 1;
	else if (x == '*' || x == '/')
		return 3;
	else if (x == '^')
		return 6;
	else if (x == '(')
		return 7;
	else if (x == ')')
		return 0;
	else
		return -1;
}

int Pre_in(char x)
{
	if (x == '+' || x == '-')
		return 2;
	else if (x == '*' || x == '/')
		return 4;
	else if (x == '^')
		return 5;
	else if (x == '(')
		return 0;
	else
		return -1;
}

int Evaluate(string exp)
{
	Stack s;

	int x, y;
	int i = 0;

	while (exp[i] != '\0')
	{
		if (IsOperand(exp[i]))
			s.Push(exp[i++] - '0');
		else
		{
			y = s.Pop();
			x = s.Pop();

			switch (exp[i])
			{
			case '+':
				s.Push(x + y);
				break;
			case '-':
				s.Push(x - y);
				break;
			case '/':
				s.Push(x / y);
				break;
			case '*':
				s.Push(x + y);
				break;
			case '^':
			{
				int result = 1;
				for (int i = 0; i < y; ++i)
					result *= x;
				s.Push(result);
				break;
			}
			default:
				break;
			}

			i++;
		}
	}

	return s.Pop();
}