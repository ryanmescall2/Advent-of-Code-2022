# pragma once
# include <string>
# include <vector>

class pyStr
{
public :
	pyStr();
	pyStr(std::string str);
	pyStr(char ch);
	std::string std_string();
	int to_int();
	void init(std::string str); 

	int len();
	pyStr operator+(pyStr& s);
	pyStr operator+(std::string& s);
	bool operator==(pyStr& s);
	std::vector<pyStr> split(std::string split_at);
	pyStr substr(int start, int end);
	pyStr startat(int start);
	pyStr endat(int end);
	pyStr strip();
	pyStr replace(std::string rplc, std::string rplc_with);
	pyStr at(int i);
	bool is_upper();
	bool is_lower();
	bool in(std::string& s);
	pyStr unique_chars();


private:
	std::string _str;
	std::vector<pyStr> RemoveEmptyStrs(std::vector<pyStr> in_vec);
};