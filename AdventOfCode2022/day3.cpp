#pragma once
#include "day3.h"
#include <map>

void Day3::problem3a()
{
	std::string file_in = "in_day3.txt";
	std::vector<std::string> data_in = file_to_vector<std::string>(file_in);

	int priorities_sum = 0;

	for (auto& line : data_in)
	{
		pyStr line_py(line);
		int len_str = line_py.len();
		int len_comp = len_str / 2;

		pyStr first_comp = line_py.substr(0, len_comp - 1);
		pyStr sec_comp = line_py.substr(len_comp, len_str - 1);

		bool found_same_item = false;

		for (auto& first_comp_item : first_comp.std_string())
		{
			if (found_same_item) break;

			for (auto& sec_comp_item : sec_comp.std_string())
			{
				if (sec_comp_item == first_comp_item)
				{
					if (std::isupper(sec_comp_item))
						priorities_sum += sec_comp_item - 'A' + 27;
					else
						priorities_sum += sec_comp_item - 'a' + 1;

					found_same_item = true;
					break;
				}
			}
		}
		if (!found_same_item) std::cout << "Error: couldn't find common character" << std::endl;
	}

	std::cout << "Problem 3a solution = " << priorities_sum << std::endl;
}

void Day3::problem3b()
{
	std::string file_in = "in_day3.txt";
	std::vector<std::string> data_in = file_to_vector<std::string>(file_in);

	int priorities_sum = 0;

	for (int i = 2; i < data_in.size(); i += 3)
	{
		pyStr line1 = pyStr(data_in[i - 2]);
		pyStr line2 = pyStr(data_in[i - 1]);
		pyStr line3 = pyStr(data_in[i]);

		line1 = line1.unique_chars();
		line2 = line2.unique_chars();
		line3 = line3.unique_chars();

		pyStr all_lines = line1 + line2 + line3;

		std::map<char, int> char_occurances;
		std::string unique_chars_str;

		for (auto& char_i : all_lines.std_string())
		{
			if (char_occurances.find(char_i) == char_occurances.end())
				char_occurances[char_i] = 1;
			else
			{
				char_occurances[char_i] += 1;
				if (char_occurances[char_i] == 3)
				{
					if (std::isupper(char_i))
						priorities_sum += char_i - 'A' + 27;
					else
						priorities_sum += char_i - 'a' + 1;
					break;
				}
			}
		}
	}

	std::cout << "Problem 3b solution = " << priorities_sum << std::endl;
}