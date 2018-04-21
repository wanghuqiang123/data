#include<iostream>
#include<string>
#include<stack>
#include<stdexcept>
#include<vector>

using namespace std;

enum obj_type {  ADD, SUB = 0,MUL ,DIV = 1, LP, RP, VAL };

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
	p = exp.find_first_not_of("=", p);
}

void process_string(string& exp)
{
	stack<obj>s;
	stack<obj>s1;
	size_t p = 0 , q;
	while (p < exp.size() && p!= -1)
	{
		skipws(exp, p);
		if (exp[p] > '0' && exp[p] < '9')
		{
			s.push(obj(VAL, stod(exp.substr(p), &q)));  //q保存从p开始的第一个分数值字符的下标；
			p += q;
		}
		else if(exp[p] == '+')
		{
			if (!s1.empty())
			{
				if (s1.top().t >= 0 && s1.top().t != 2)
				{
					s.push(obj(s1.top().t));
					s.pop();
					s.push(obj(ADD));
				}
				else
				{
					s1.push(obj(ADD));
				}
			}
			else
			{
				s1.push(obj(ADD));
			}
			p++;
		}
		else if (exp[p] == '-')
		{
			if (!s1.empty())
			{
				if (s1.top().t >= 0 && s1.top().t != 2)
				{
					s.push(obj(s1.top().t));
					s.pop();
					s.push(obj(SUB));
				}
				else
				{
					s1.push(obj(SUB));
				}
			}
			else
			{
				s1.push(obj(SUB));
			}
			p++;
		}
		else if (exp[p] == '*')
		{
			if (!s1.empty())
			{
				if (s1.top().t >= 1 && s1.top().t != 2)
				{
					s.push(obj(s1.top().t));
					s.pop();
					s.push(obj(MUL));
				}
				else
				{
					s1.push(obj(MUL));
				}
			}
			else
			{
				s1.push(obj(MUL));
			}
			p++;
		}
		else if (exp[p] == '/')
		{
			if (!s1.empty())
			{
				if (s1.top().t >= 1 && s1.top().t != 2)
				{
					s.push(obj(s1.top().t));
					s.pop();
					s.push(obj(DIV));
				}
				else
				{
					s1.push(obj(DIV));
				}
			}
			else
			{
				s1.push(obj(DIV));
			}
			p++;
		}
		else if (exp[p] == '(')
		{
			s1.push(obj(LP));
			p++;
		}
		else if (exp[p] == ')')
		{
			while (s1.top().t != '(')
			{
				s.push(obj(s1.top().t));
				s1.pop();
			}
			s1.pop();
			p++;
		}
		else
		{
			throw invalid_argument("input error!");
		}
	}
	while (!s1.empty())
	{
		s.push(obj(s1.top().t));
		s1.pop();
	}
}

/*double Stuffix_Result()
{
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
		else if(exp.find_first_of("+-/*") != -1)
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
}*/

int main(int argc,char** argv)
{
	
	string exp;
	cout << "please input expression:" << endl;
	getline(cin, exp);
	process_string(exp);

	return 0;
}