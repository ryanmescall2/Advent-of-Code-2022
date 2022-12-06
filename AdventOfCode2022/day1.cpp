#pragma once
#include "day1.h"

void Day1::problem1a()
{
	std::string file_in = "in_day1.txt";
	std::vector<int> data_in = file_to_vector<int>(file_in);
	
	// push back a blank entry so that the i%3 condition gets called on the last input element
	data_in.push_back(0);
	
	int most_elf_cal = 0;
	int cur_elf_cal = 0;
	for (int& cals: data_in)
	{
		if (cals == 0)
		{
			if (cur_elf_cal > most_elf_cal)
				most_elf_cal = cur_elf_cal;
			cur_elf_cal = 0;
		}

		cur_elf_cal += cals;
	}

	std::cout << "Problem 1a solution = " << most_elf_cal << std::endl;
}

void Day1::problem1b()
{
	std::string file_in = "in_day1.txt";
	std::vector<int> data_in = file_to_vector<int>(file_in);

	// push back a blank entry so that the i%3 condition gets called on the last input element
	data_in.push_back(0);

	const int num_top_elves = 3;
	int most_elf_cal[num_top_elves] = {0};
	int cur_elf_cal = 0;
	for (int& cals : data_in)
	{
		if (cals == 0)
		{
			int smallest_cal_i = most_elf_cal[0];
			int idx_smallest_cal_i = 0;
			for (int i = 1; i < num_top_elves; i++)
			{
				if (most_elf_cal[i] < smallest_cal_i)
				{
					smallest_cal_i = most_elf_cal[i];
					idx_smallest_cal_i = i;
				}
			}

			if (cur_elf_cal > smallest_cal_i)
			{
				most_elf_cal[idx_smallest_cal_i] = cur_elf_cal;
			}
			cur_elf_cal = 0;
		}

		cur_elf_cal += cals;
	}

	int total_cal = 0;
	for (int& cal : most_elf_cal)
		total_cal += cal;

	std::cout << "Problem 1b solution = " << total_cal << std::endl;
}