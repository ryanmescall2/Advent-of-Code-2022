#pragma once
#include "day4.h"
#include <map>

std::tuple<int, int> get_elf_sections(pyStr elf_input_line)
{
	std::vector<pyStr> elf_sections = elf_input_line.split("-");
	std::tuple<int, int> elf_sections_range = std::make_tuple(
		elf_sections[0].to_int(), elf_sections[1].to_int());
	return elf_sections_range;
}

bool elf1_within_elf2_range(std::tuple<int, int> elf1_sections, std::tuple<int, int> elf2_sections)
{
	if (std::get<0>(elf1_sections) >= std::get<0>(elf2_sections) &&
		std::get<1>(elf1_sections) <= std::get<1>(elf2_sections))
		return true;
	else
		return false;
}

bool elf1_overlaps_elf2_range(std::tuple<int, int> elf1_sections, std::tuple<int, int> elf2_sections)
{
	if (std::get<0>(elf1_sections) >= std::get<0>(elf2_sections) &&
		std::get<0>(elf1_sections) <= std::get<1>(elf2_sections))
		return true;
	else if (std::get<1>(elf1_sections) >= std::get<0>(elf2_sections) &&
		std::get<1>(elf1_sections) <= std::get<1>(elf2_sections))
		return true;
	else
		return false;
}

void Day4::problem4a()
{
	std::string file_in = "in_day4.txt";
	std::vector<std::string> data_in = file_to_vector<std::string>(file_in);

	int overlapping_elves = 0;

	for (auto& line : data_in)
	{
		pyStr line_py(line);
		std::vector<pyStr> elves = line_py.split(",");
		std::tuple<int, int> elf1_sections = get_elf_sections(elves[0]);
		std::tuple<int, int> elf2_sections = get_elf_sections(elves[1]);

		if (elf1_within_elf2_range(elf1_sections, elf2_sections)) 
		{
			overlapping_elves += 1;
			continue;
		}
		if (elf1_within_elf2_range(elf2_sections, elf1_sections))
		{
			overlapping_elves += 1;
			continue;
		}

	}

	std::cout << "Problem 4a solution = " << overlapping_elves << std::endl;
}

void Day4::problem4b()
{
	std::string file_in = "in_day4.txt";
	std::vector<std::string> data_in = file_to_vector<std::string>(file_in);

	int overlapping_elves = 0;

	for (auto& line : data_in)
	{
		pyStr line_py(line);
		std::vector<pyStr> elves = line_py.split(",");
		std::tuple<int, int> elf1_sections = get_elf_sections(elves[0]);
		std::tuple<int, int> elf2_sections = get_elf_sections(elves[1]);

		if (elf1_overlaps_elf2_range(elf1_sections, elf2_sections))
		{
			overlapping_elves += 1;
			continue;
		}
		if (elf1_overlaps_elf2_range(elf2_sections, elf1_sections))
		{
			overlapping_elves += 1;
			continue;
		}

	}

	std::cout << "Problem 4b solution = " << overlapping_elves << std::endl;
}