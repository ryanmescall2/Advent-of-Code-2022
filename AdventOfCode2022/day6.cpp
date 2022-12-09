#pragma once
#include "day6.h"
#include <map>

double find_last_marker_index(int marker_len)
{
	std::string file_in = "in_day6.txt";
	std::vector<pyStr> data_in_vec = file_lines_to_pystr(file_in);
	pyStr data_in = data_in_vec[0];

	int i = 0;
	int size_data = data_in.len();
	while (i < size_data)
	{
		pyStr substr = data_in.substr(i, i + marker_len-1);
		if (substr.unique_chars().len() == marker_len)
		{
			return i + marker_len;
		}
		i += 1;
	}
}

void Day6::problem6a()
{
	std::cout << "Problem 6a solution = " << find_last_marker_index(4) << std::endl;
}

void Day6::problem6b()
{

	std::cout << "Problem 6b solution = " << find_last_marker_index(14) << std::endl;
}