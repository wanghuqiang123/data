@ -6,7 +6,7 @@
  
  using namespace std;
  
 -enum obj_type {  ADD, SUB = 0,MUL ,DIV = 1, LP, RP, VAL };
 +enum obj_type {  ADD, SUB,MUL ,DIV, LP, RP, VAL };
  
  struct obj
  {
 @@ -21,10 +21,30 @@ struct obj
  
  inline void skipws(string &exp, size_t &p)
  {
 -	p = exp.find_first_not_of("=", p);
 +	p = exp.find_first_not_of("=", p);//返回的string ::npos 默认值为-1
  }
  
 -void process_string(string& exp)
 +inline void Stuffix_Result(stack<obj>&s)
 +{
 +	double v;
 +	switch (s.top().t)
 +	{
 +	case obj_type::ADD:
 +		s.pop(); v = s.top().ov; s.pop(); v += s.top().ov; s.pop();
 +		s.push(obj(VAL, v));
 +		break;
 +	case obj_type::SUB:
 +		s.pop(); v = s.top().ov; s.pop(); v = s.top().ov - v; s.pop(); s.push(obj(VAL, v));
 +		break;
 +	case obj_type::MUL:
 +		s.pop(); v = s.top().ov; s.pop(); v *= s.top().ov; s.pop(); s.push(obj(VAL, v));
 +		break;
 +	case obj_type::DIV:
 +		s.pop(); v = s.top().ov; s.pop(); v = s.top().ov / v; s.pop(); s.push(obj(VAL, v));
 +		break;
 +	}
 +}
 +double process_string(string& exp)
  {
  	stack<obj>s;
  	stack<obj>s1;
 @@ -41,14 +61,15 @@ void process_string(string& exp)
  		{
  			if (!s1.empty())
  			{
 -				if (s1.top().t != 2)
 +				if (s1.top().t != 4)
  				{
  					count = s1.size();
  					for (size_t i = 0; i < count; i++)
  					{
 -						if (s1.top().t >= 0 && s1.top().t != 2)
 +						if (s1.top().t >= 0 && s1.top().t != 4)
  						{
  							s.push(obj(s1.top().t));
 +							Stuffix_Result(s);
  							s1.pop();
  						}
  					}
 @@ -69,14 +90,15 @@ void process_string(string& exp)
  		{
  			if (!s1.empty())
  			{
 -				if ( s1.top().t != 2)
 +				if ( s1.top().t != 4)
  				{
  					count = s1.size();
  					for (size_t i = 0; i < count; i++)
  					{
 -						if (s1.top().t >= 0 && s1.top().t != 2)
 +						if (s1.top().t >= 0 && s1.top().t != 4)
  						{
  							s.push(obj(s1.top().t));
 +							Stuffix_Result(s);
  							s1.pop();
  						}
  					}
 @@ -97,14 +119,15 @@ void process_string(string& exp)
  		{
  			if (!s1.empty())
  			{
 -				if (s1.top().t != 2)
 +				if (s1.top().t != 4)
  				{
  					count = s1.size();
  					for (size_t i = 0; i < count; i++)
  					{
 -						if (s1.top().t >= 1 && s1.top().t != 2)
 +						if (s1.top().t >= 2 && s1.top().t != 4)
  						{
  							s.push(obj(s1.top().t));
 +							Stuffix_Result(s);
  							s1.pop();
  						}
  					}
 @@ -125,14 +148,15 @@ void process_string(string& exp)
  		{
  			if (!s1.empty())
  			{
 -				if (s1.top().t != 2)
 +				if (s1.top().t != 4)
  				{
  					count = s1.size();
  					for (size_t i = 0; i < count; i++)
  					{
 -						if (s1.top().t >= 1 && s1.top().t != 2)
 +						if (s1.top().t >= 2 && s1.top().t != 4)
  						{
  							s.push(obj(s1.top().t));
 +							Stuffix_Result(s);
  							s1.pop();
  						}
  					}
 @@ -156,9 +180,10 @@ void process_string(string& exp)
  		}
  		else if (exp[p] == ')')
  		{
 -			while (s1.top().t != 2)
 +			while (s1.top().t != 4)
  			{
  				s.push(obj(s1.top().t));
 +				Stuffix_Result(s);
  				s1.pop();
  			}
  			s1.pop();
 @@ -172,56 +197,19 @@ void process_string(string& exp)
  	while (!s1.empty())
  	{
  		s.push(obj(s1.top().t));
 +		Stuffix_Result(s);
  		s1.pop();
  	}
 -}
  
 -/*double Stuffix_Result()
 -{
 -	double v;
 -	stack<obj>s;
 -	string exp;
 -	while (cin >> exp)
 -	{
 -		if ( exp.find_first_of("0123456789") != -1 )  //返回的string ::npos 默认值为-1
 -		{
 -			v = stod(exp);
 -			s.push(obj(VAL, v));
 -		}
 -		else if(exp.find_first_of("+-/*") != -1)
 -		{
 -			switch (exp[0])
 -			{
 -			case '+':
 -				s.pop(); v += s.top().ov; s.pop();
 -				s.push(obj(VAL, v));
 -				break;
 -			case '-':
 -				s.pop(); v = s.top().ov - v; s.pop(); s.push(obj(VAL, v));
 -				break;
 -			case '*':
 -				s.pop(); v *= s.top().ov; s.pop(); s.push(obj(VAL, v));
 -				break;
 -			case '/':
 -				s.pop(); v = s.top().ov / v; s.pop(); s.push(obj(VAL, v));
 -				break;
 -			}
 -		}
 -		else
 -		{
 -			throw invalid_argument("input error");
 -		}
 -	}
  	return s.top().ov;
 -}*/
 +}
  
  int main(int argc,char** argv)
  {
 -	
  	cout << "please input expression:" << endl;
  	//getline(cin, exp);
  	string exp = "1+2*2+(2*1+2)*2=";
 -	process_string(exp);
 +	cout << process_string(exp) << endl;;
  
  	return 0;
  } 