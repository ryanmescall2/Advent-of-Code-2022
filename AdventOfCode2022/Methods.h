#pragma once

#include <cassert>
#include <cstdint>
#include <cstdio>
#include <format>
#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include "pyStr.h"

#define _SOLUTIONDIR R"(C:\Users\rnm36\Documents\AdventOfCode2022\Advent-of-Code-2022\AdventOfCode2022)"

//using U64 = uint64_t;
//static_assert(sizeof(U64) == 8);

template <typename T>
inline std::vector<T> file_to_vector(std::string& file_name)
{ // Read file and put every value seperated by a space or comma into a new index of a vector
	std::string input_path = std::string(_SOLUTIONDIR) + "\\" + file_name;

	std::ifstream infile(input_path);
	std::vector<T> contents;

	std::string line;
	T val = {};
	bool blank_line = true;

	while (std::getline(infile, line)) {
		std::stringstream ss(line);
		while (ss >> val) {
			contents.push_back(val);
			blank_line = false;
		}
		if (blank_line)
			contents.push_back(NULL);
		blank_line = true;
	}

	return contents;
}

inline std::vector<pyStr> file_lines_to_pystr(std::string& file_name)
{ // Read file. Each line is a new entry in vector
	std::vector<pyStr> lines_out;

	std::string input_path = std::string(_SOLUTIONDIR) + "\\" + file_name;
	std::ifstream infile(input_path);
	std::string line;
	while (std::getline(infile, line))
		lines_out.push_back(pyStr(line));

	return lines_out;
}

inline std::vector<int> pystr_to_int_vec(std::vector<pyStr>& pyStr_vec)
{ // Convert a pyStr vector to an int vector
	std::vector<int> int_vec;
	for (int i = 0; i < pyStr_vec.size(); i++)
		int_vec.push_back(atoi(pyStr_vec[i].std_string().c_str()));
	return int_vec;
}

inline int char_to_int(char c)
{
	return (int)(c) - 48;
}

template <typename T>
inline bool val_in_vec(std::vector<T> vec, T val)
{
	for (auto& c : vec)
	{
		if (val == c)
			return true;
	}
	return false;
}

template <typename T>
inline int occurences_in_vec(std::vector<T> vec, T val)
{
	int occurences = 0;
	for (auto& c : vec)
	{
		if (val == c)
			occurences += 1;
	}
	return occurences;
}

inline std::vector<std::string> pystr_to_str_vec(std::vector<pyStr>& pyStr_vec)
{ // Convert a pyStr vector to an int vector
	std::vector<std::string> str_vec;
	for (int i = 0; i < pyStr_vec.size(); i++)
		str_vec.push_back(pyStr_vec[i].std_string());
	return str_vec;
}