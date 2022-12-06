#pragma once
#include "day2.h"

void Day2::problem2a()
{
	std::string file_in = "in_day2.txt";
	std::vector<std::string> data_in = file_to_vector<std::string>(file_in);
	
	std::unordered_map<std::string, int> score_key;
	score_key["AX"] = 1+3;
	score_key["AY"] = 2+6;
	score_key["AZ"] = 3+0;
	score_key["BX"] = 1+0;
	score_key["BY"] = 2+3;
	score_key["BZ"] = 3+6;
	score_key["CX"] = 1+6;
	score_key["CY"] = 2+0;
	score_key["CZ"] = 3+3;

	int total_score = 0;
	for (int i = 0; i < data_in.size(); i += 2)
		total_score += score_key[data_in[i] + data_in[i + 1]];

	std::cout << "Problem 2a solution = " << total_score << std::endl;
}

void Day2::problem2b()
{
	std::string file_in = "in_day2.txt";
	std::vector<std::string> data_in = file_to_vector<std::string>(file_in);

	std::unordered_map<std::string, int> score_key;
	score_key["AX"] = 0 + 3;
	score_key["AY"] = 3 + 1;
	score_key["AZ"] = 6 + 2;
	score_key["BX"] = 0 + 1;
	score_key["BY"] = 3 + 2;
	score_key["BZ"] = 6 + 3;
	score_key["CX"] = 0 + 2;
	score_key["CY"] = 3 + 3;
	score_key["CZ"] = 6 + 1;

	int total_score = 0;
	for (int i = 0; i < data_in.size(); i += 2)
		total_score += score_key[data_in[i] + data_in[i + 1]];

	std::cout << "Problem 2b solution = " << total_score << std::endl;
}