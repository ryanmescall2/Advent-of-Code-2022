#pragma once
#include "day5.h"
#include <map>

std::vector<std::string> reverse_vector(std::vector<std::string> orig_vec) 
{
	int orig_vec_size = orig_vec.size();
	std::vector<std::string> new_vec(orig_vec_size);
	for (int i = 0; i < orig_vec_size; i++)
		new_vec[orig_vec_size - 1 - i] = orig_vec[i];
	return new_vec;
}

void Day5::problem5a()
{
	std::string file_in = "in_day5.txt";
	std::vector<pyStr> data_in = file_lines_to_pystr(file_in);

	std::string boxes_on_top = "";

	std::unordered_map<int,std::vector<std::string>> crates;

	bool reading_crates = true;
	std::string space = " ";
	std::string empty_line = "";
	pyStr empty_pystr = pyStr(empty_line);

	for (auto& line : data_in)
	{
		pyStr line_py(line);

		if (line_py == empty_pystr)
		{
			reading_crates = false;
			
			for (auto map_key : crates)
			{
				map_key.second.pop_back(); // get rid of stack name, it is already stored in key
				crates[map_key.first] = reverse_vector(map_key.second); // flip crates around to treat as stack
			}
			continue;
		}
		
		if (reading_crates)
		{
			line_py = pyStr(line_py + space);

			int i = 1;
			int stack_number = 1;
			int size_line = line_py.len();
			while (i < size_line)
			{
				std::string crate_i = line_py.at(i).std_string();
				if (crate_i != " ")
					crates[stack_number].push_back(crate_i);
				stack_number += 1;
				i += 4;
			}
		}
		else
		{
			std::vector<pyStr> line_words = line_py.split(" ");
			int crates_to_move = line_words[1].to_int();
			int from_stack     = line_words[3].to_int();
			int to_stack       = line_words[5].to_int();

			for (int i = 0; i < crates_to_move; i++)
			{
				// remove crate from the first stack
				int from_stack_size = crates[from_stack].size();
				std::string crate_to_move = crates[from_stack][from_stack_size - 1];
				crates[from_stack].pop_back();
				// add it to the new stack
				crates[to_stack].push_back(crate_to_move);
			}

		}
	}
		
	int max_key = 0;
	for (auto& map_key : crates)
		max_key = std::max(map_key.first, max_key);

	for (int i = 1; i <= max_key; i++)
	{
		if (crates[i].size() >= 1)
			boxes_on_top += crates[i][crates[i].size() - 1];
	}

	std::cout << "Problem 5a solution = " << boxes_on_top << std::endl;
}

void Day5::problem5b()
{
	std::string file_in = "in_day5.txt";
	std::vector<pyStr> data_in = file_lines_to_pystr(file_in);

	std::string boxes_on_top = "";

	std::unordered_map<int, std::vector<std::string>> crates;

	bool reading_crates = true;
	std::string space = " ";
	std::string empty_line = "";
	pyStr empty_pystr = pyStr(empty_line);

	for (auto& line : data_in)
	{
		pyStr line_py(line);

		if (line_py == empty_pystr)
		{
			reading_crates = false;

			for (auto map_key : crates)
			{
				map_key.second.pop_back(); // get rid of stack name, it is already stored in key
				crates[map_key.first] = reverse_vector(map_key.second); // flip crates around to treat as stack
			}
			continue;
		}

		if (reading_crates)
		{
			line_py = pyStr(line_py + space);

			int i = 1;
			int stack_number = 1;
			int size_line = line_py.len();
			while (i < size_line)
			{
				std::string crate_i = line_py.at(i).std_string();
				if (crate_i != " ")
					crates[stack_number].push_back(crate_i);
				stack_number += 1;
				i += 4;
			}
		}
		else
		{
			std::vector<pyStr> line_words = line_py.split(" ");
			int crates_to_move = line_words[1].to_int();
			int from_stack = line_words[3].to_int();
			int to_stack = line_words[5].to_int();

			for (int i = 0; i < crates_to_move; i++)
			{
				// remove crate from the first stack
				int from_stack_size = crates[from_stack].size();
				std::string crate_to_move = crates[from_stack][from_stack_size - crates_to_move + i];
				// add it to the new stack
				crates[to_stack].push_back(crate_to_move);
			}
			for (int i = 0; i < crates_to_move; i++)
			{
				// remove crate from the first stack
				int from_stack_size = crates[from_stack].size();
				std::string crate_to_move = crates[from_stack][from_stack_size - 1];
				crates[from_stack].pop_back();
			}
		}
	}

	int max_key = 0;
	for (auto& map_key : crates)
		max_key = std::max(map_key.first, max_key);

	for (int i = 1; i <= max_key; i++)
	{
		if (crates[i].size() >= 1)
			boxes_on_top += crates[i][crates[i].size() - 1];
	}

	std::cout << "Problem 5b solution = " << boxes_on_top << std::endl;
}