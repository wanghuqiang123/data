#include<iostream>
#include<string>
#include<stack>
#include<stdexcept>

using namespace std;

enum obj_type { LP, RP, ADD, SUB,MUL,DIV, VAL };

struct obj
{
	obj(obj_type type, double val = 0)
	{
		t = type;
		ov = val;
	}
	obj_type t;
	double ov;
};

inline void skipws(string &exp, size_t &p)
{
	p = exp.find_first_not_of(" ", p);
}

double Stuffix_Result()
{
	size_t p = 0;
	double v;
	stack<obj>s;
	string exp;
	while (cin >> exp)
	{
		if ( exp.find_first_of("0123456789") != -1 )  //返回的string ::npos 默认值为-1
		{
			v = stod(exp);
			s.push(obj(VAL, v));
		}
		else if(exp.find_first_of("+-*/") != -1)
		{
			switch (exp[0])
			{
			case '+':
				s.pop(); v += s.top().ov; s.pop();
				s.push(obj(VAL, v));
				break;
			case '-':
				s.pop(); v = s.top().ov - v; s.pop(); s.push(obj(VAL, v));
				break;
			case '*':
				s.pop(); v *= s.top().ov; s.pop(); s.push(obj(VAL, v));
				break;
			case '/':
				s.pop(); v = s.top().ov / v; s.pop(); s.push(obj(VAL, v));
				break;
			}
		}
		else
		{
			throw invalid_argument("input error");
		}
	}
	return s.top().ov;
}
		

int main()
{
	
	string exp;
	cout << "please input expression:" << endl;
	//getline(cin, exp);
	cout << Stuffix_Result() << endl;

	return 0;
}