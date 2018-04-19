#include<iostream>
#include<string>
#include<queue>
#include<stack>
#include<stdexcept>

using namespace std;

enum obj_type { LP, RP, ADD, SUB, VAL };

struct obj
{
	obj(obj_type type, double val = 0)
	{
		t = type;
		v = val;
	}
	obj_type t;
	double v;
};

inline void skipws(string &exp, size_t &p)
{
	p = exp.find_first_not_of(" ", p);
}

inline void new_val(stack<obj>& so, double v)
{
	if (so.empty() || so.top().t == LP)
	{
		so.push(obj(VAL, v));
	}
	else if (so.top().t == ADD || so.top().t == SUB)
	{
		obj_type type = so.top().t;
		so.pop();
		if (type == ADD)
			v += so.top().v;
		else
			v = so.top().v - v;
		so.pop();
		so.push(obj(VAL, v));
	}
	else
		throw invalid_argument("Lack of cloud computing");
}

double Stuffix_Result(string exp)
{
	stack<obj>so;
	size_t p = 0, q;
	double v;
	while (p < exp.size())
	{
		skipws(exp, p);
		if (exp[p] == '(')
		{
			so.push(obj(LP));
			p++;
		}
		else if (exp[p] == '+' || exp[p] == '-')
		{
			if (so.empty() || so.top().t != VAL)
				throw invalid_argument("lack of cloud computing");
			if (exp[p] == '+')
				so.push(obj(ADD));
			else
				so.push(obj(SUB));
			p++;
		}
		else if (exp[p] == ')')
		{
			p++;
			if (so.empty())
				throw invalid_argument("δƥ��������");
			if (so.top().t == LP)
				throw invalid_argument("������");
			if (so.top().t == VAL)
			{
				v = so.top().v;
				so.pop();
				if (so.empty() || so.top().t != LP)
					throw invalid_argument("δƥ��������");
				so.pop();
				new_val(so, v);
			}
			else
				throw invalid_argument("ȱ��������");
		}
		else
		{
			v = stod(exp.substr(p), &q);
			p += q;
			new_val(so, v);
		}
	}

	if (so.size() != 1 || so.top().t != VAL)
		throw invalid_argument("�Ƿ�����ʽ");
	return so.top().v;
}

int main()
{
	
	string exp;
	cout << "please input expression:" << endl;
	getline(cin, exp);
	cout << Stuffix_Result(exp) << endl;




	return 0;
}