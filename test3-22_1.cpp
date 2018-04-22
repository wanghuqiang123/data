#include<iostream>
#include<string>
#include<stack>
#include<stdexcept>
#include<vector>

using namespace std;

enum obj_type {  ADD, SUB,MUL ,DIV, LP, RP, VAL };

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
	p = exp.find_first_not_of("=", p);//返回的string ::npos 默认值为-1
}

inline void Stuffix_Result(stack<obj>&s)
{
	double v;
	switch (s.top().t)
	{
	case obj_type::ADD:
		s.pop(); v = s.top().ov; s.pop(); v += s.top().ov; s.pop();
		s.push(obj(VAL, v));
		break;
	case obj_type::SUB:
		s.pop(); v = s.top().ov; s.pop(); v = s.top().ov - v; s.pop(); s.push(obj(VAL, v));
		break;
	case obj_type::MUL:
		s.pop(); v = s.top().ov; s.pop(); v *= s.top().ov; s.pop(); s.push(obj(VAL, v));
		break;
	case obj_type::DIV:
		s.pop(); v = s.top().ov; s.pop(); v = s.top().ov / v; s.pop(); s.push(obj(VAL, v));
		break;
	}
}
double process_string(string& exp)
{
	stack<obj>s;
	stack<obj>s1;
	size_t p = 0 , q,count;
	while (p < (exp.size()-1) && p!= -1)
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
				if (s1.top().t != 4)
				{
					count = s1.size();
					for (size_t i = 0; i < count; i++)
					{
						if (s1.top().t >= 0 && s1.top().t != 4)
						{
							s.push(obj(s1.top().t));
							Stuffix_Result(s);
							s1.pop();
						}
					}
					s1.push(obj(ADD));
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
				if ( s1.top().t != 4)
				{
					count = s1.size();
					for (size_t i = 0; i < count; i++)
					{
						if (s1.top().t >= 0 && s1.top().t != 4)
						{
							s.push(obj(s1.top().t));
							Stuffix_Result(s);
							s1.pop();
						}
					}
					s1.push(obj(SUB));
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
				if (s1.top().t != 4)
				{
					count = s1.size();
					for (size_t i = 0; i < count; i++)
					{
						if (s1.top().t >= 2 && s1.top().t != 4)
						{
							s.push(obj(s1.top().t));
							Stuffix_Result(s);
							s1.pop();
						}
					}
					s1.push(obj(MUL));
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
				if (s1.top().t != 4)
				{
					count = s1.size();
					for (size_t i = 0; i < count; i++)
					{
						if (s1.top().t >= 2 && s1.top().t != 4)
						{
							s.push(obj(s1.top().t));
							Stuffix_Result(s);
							s1.pop();
						}
					}
					s1.push(obj(DIV));
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
			while (s1.top().t != 4)
			{
				s.push(obj(s1.top().t));
				Stuffix_Result(s);
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
		Stuffix_Result(s);
		s1.pop();
	}

	return s.top().ov;
}

int main(int argc,char** argv)
{
	cout << "please input expression:" << endl;
	//getline(cin, exp);
	string exp = "1+2*2+(2*1+2)*2=";
	cout << process_string(exp) << endl;;

	return 0;
}