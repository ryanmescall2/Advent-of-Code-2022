# pragma once

# include "pyStr.h"
# include <vector>
# include <string>
# include <unordered_map>
# include <map>

pyStr::pyStr(std::string str) // constructor
	: _str(str)
{}

pyStr::pyStr(char ch) // constructor
{
	_str = ch;
}

pyStr::pyStr() // default constructor
	: _str("")
{}

std::string pyStr::std_string() // convert back to std::string
{
	return _str;
}

int pyStr::to_int() // convert to int
{
	return atoi(_str.c_str());
}

void pyStr::init(std::string str) // assign an std::string to initialize
{
	_str = str;
}

/////////////////////////////////////////
// Replicated Python string functions: //
/////////////////////////////////////////

pyStr pyStr::operator+(pyStr& s) // add two pyStrs
{
	return std_string() + s.std_string();
}

pyStr pyStr::operator+(std::string& s) // add pyStr and string
{
	return std_string() + s;
}

bool pyStr::operator==(pyStr& s)
{
	return s.std_string() == _str;
}

bool pyStr::operator==(const char* s)
{
	std::string s_std = s;
	return s == _str;
}

bool pyStr::operator!=(pyStr& s)
{
	return s.std_string() != _str;
}

bool pyStr::operator!=(const char* s)
{
	std::string s_std = s;
	return s != _str;
}

int pyStr::len() // length - size of pyStr
{
	return (int) std_string().size();
}

pyStr pyStr::substr(int start, int end) // equivalent to string[start:end] in python
{
	std::string subString = "";
	for (int i = 0; i < len(); i++)
	{
		if (i >= start && i <= end)
			subString += _str[i];
	}

	return pyStr(subString);
}

pyStr pyStr::startat(int start) // equivalent to string[start:] in python
{
	std::string subString = "";
	if (start >= 0)
	{
		for (int i = start; i < len(); i++)
				subString += _str[i];
		return pyStr(subString);
	}
	else
	{
		return endat(-start);
	}
}

pyStr pyStr::endat(int end) // equivalent to string[:end] in python
{
	std::string subString = "";
	if (end >= 0)
	{
		for (int i = 0; i < end; i++)
			subString += _str[i];
		return pyStr(subString);
	}
	else
	{
		return startat(-end);
	}
}

std::vector<pyStr> pyStr::split(std::string split_at) // equivalent to python split
{
	std::vector<pyStr> split_return;
	std::string stack_chars;
	std::string _str_copy;

	int j = 0;
	int last_idx = 0;
	for (int i = 0; i < len(); i++) { // loop through all chars in _str
		if (split_at[j] == _str[i])
		{
			stack_chars += split_at[j];
			j += 1;

			if (stack_chars == split_at)
			{
				pyStr pyStr_str = pyStr(_str);
				split_return.push_back(pyStr_str.substr(last_idx, i - (int)split_at.size()));
				_str_copy = pyStr_str.startat(i + 1).std_string();

				last_idx = i+1;
				j = 0;
				stack_chars = "";

				if (_str_copy.size() == 0)
					return remove_empty_strs(split_return);
			}
		}
		else
		{
			j = 0;
			stack_chars = "";
		}
		
	}
	if (split_return.size() != 0)
		split_return.push_back(pyStr(_str_copy));
	return remove_empty_strs(split_return);
}

pyStr pyStr::replace(std::string rplc, std::string rplc_with) // equivalent to python replace
{
	std::string new_str = "";

	int rplc_size = rplc.size();

	for (int i = 0; i < _str.size(); i++)
	{ // iterate through _str and replace and rplc sub strings with rplc_with
		std::string substr_i = "";
		for (int j = 0; j < rplc_size; j++)
			substr_i += _str[i + j];
		
		if (substr_i == rplc)
		{
			new_str += rplc_with;
			i += rplc_size-1;
		}
		else
			new_str += _str[i];
	}

	return pyStr(new_str);
}

pyStr pyStr::at(int i) // returns value at index
{
	return pyStr(_str[i]);
}

pyStr pyStr::strip() // Not working yet
{
	pyStr stripped_str = pyStr(_str);
	std::unordered_map<std::string, bool> remove_chars;
	remove_chars["\t"] = true;
	remove_chars["\n"] = true;
	remove_chars[" "] = true;
	
	return stripped_str;
}

bool pyStr::is_upper() // check if all characters are upper case
{
	for (auto& c : _str) {
		if (!isupper(c))
			return false;
	}
	return true;
}

bool pyStr::is_lower() // check if all characters are lower case
{
	for (auto& c : _str) {
		if (isupper(c))
			return false;
	}
	return true;
}

bool pyStr::in(std::string& s) // check if string exists as a substring in the pyStr
{
	std::vector<pyStr> check = split(s);
	if (check.size() == 0)
		return false;
	return true;
}

std::vector<pyStr> pyStr::remove_empty_strs(std::vector<pyStr> in_vec)
{
	std::vector<pyStr> return_vec;
	for (int i = 0; i < in_vec.size(); i++) {
		if (in_vec[i].std_string() != "")
			return_vec.emplace_back(in_vec[i]);
	}
	return return_vec;

}

pyStr pyStr::unique_chars()
{
	std::map<char, bool> char_occurances;
	std::string unique_chars_str;

	for (auto char_i : _str)
	{
		if (char_occurances.find(char_i) == char_occurances.end())
		{
			char_occurances[char_i] = true;
			unique_chars_str += char_i;
		}
	}

	return pyStr(unique_chars_str);
}