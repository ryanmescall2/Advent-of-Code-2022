#pragma once
#include "day9.h"
#include <unordered_map>
#include <map>

typedef std::tuple<int, int> Pos;

int first(Pos& pos)
{
	return std::get<0>(pos);
}

int second(Pos& pos)
{
	return std::get<1>(pos);
}

int sgn(int val) 
{
	return (0 < val) - (val < 0);
}

void Day9::problem9a()
{
	std::string file_in = "in_day9.txt";
	std::vector<pyStr> data_in = file_lines_to_pystr(file_in);

	std::map<Pos, bool> tail_hist;
	Pos pos_head = std::make_tuple(0, 0);
	Pos pos_tail = std::make_tuple(0, 0);

	tail_hist[pos_tail] = true;

	for (auto& line : data_in)
	{
		std::vector<pyStr> line_split = line.split(" ");
		int num_steps = line_split[1].to_int();
		std::string direction = line_split[0].std_string();

		for (int step = 0; step < num_steps; step++)
		{
			if (direction == "U")
				std::get<0>(pos_head) += 1;
			else if (direction == "D")
				std::get<0>(pos_head) -= 1;
			else if (direction == "R")
				std::get<1>(pos_head) += 1;
			else if (direction == "L")
				std::get<1>(pos_head) -= 1;

			int diff_row = first(pos_head) - first(pos_tail);
			int diff_col = second(pos_head) - second(pos_tail);

			int diff_row_sgn = sgn(diff_row);
			int diff_col_sgn = sgn(diff_col);

			if (std::abs(diff_row) == 2) // we have moved up or down and the diff is 2 rows
			{
				std::get<0>(pos_tail) += diff_row_sgn;

				if (diff_col != 0)
					std::get<1>(pos_tail) += diff_col_sgn;
			}

			else if (std::abs(diff_col) == 2) // we have moved left or right and the diff is 2 cols
			{
				std::get<1>(pos_tail) += diff_col_sgn;

				if (diff_row != 0)
					std::get<0>(pos_tail) += diff_row_sgn;
			}

			tail_hist[pos_tail] = true;
		}

	}

	int sol = 0;
	for (auto& key : tail_hist)
	{
		if (key.second)
			sol += 1;
	}
	
	std::cout << "Problem 9a solution = " << sol << std::endl;
}

void Day9::problem9b()
{
	std::string file_in = "in_day9.txt";
	std::vector<pyStr> data_in = file_lines_to_pystr(file_in);

	std::map<Pos, bool> tail_hist;
	std::vector<Pos> knots;
	for (int i = 0; i < 10; i++)
		knots.push_back(std::make_tuple(0, 0));

	tail_hist[std::make_tuple(0, 0)] = true;

	for (auto& line : data_in)
	{
		std::vector<pyStr> line_split = line.split(" ");
		int num_steps = line_split[1].to_int();
		std::string direction = line_split[0].std_string();

		for (int step = 0; step < num_steps; step++)
		{
			if (direction == "U")
				std::get<0>(knots[0]) += 1;
			else if (direction == "D")
				std::get<0>(knots[0]) -= 1;
			else if (direction == "R")
				std::get<1>(knots[0]) += 1;
			else if (direction == "L")
				std::get<1>(knots[0]) -= 1;

			for (int i = 0; i < 9; i++)
			{
				int diff_row = first(knots[i]) - first(knots[i + 1]);
				int diff_col = second(knots[i]) - second(knots[i + 1]);

				int diff_row_sgn = sgn(diff_row);
				int diff_col_sgn = sgn(diff_col);

				if (std::abs(diff_row) == 2) // we have moved up or down and the diff is 2 rows
				{
					std::get<0>(knots[i + 1]) += diff_row_sgn;

					if (diff_col != 0)
						std::get<1>(knots[i + 1]) += diff_col_sgn;
				}

				else if (std::abs(diff_col) == 2) // we have moved left or right and the diff is 2 cols
				{
					std::get<1>(knots[i + 1]) += diff_col_sgn;

					if (diff_row != 0)
						std::get<0>(knots[i + 1]) += diff_row_sgn;
				}
			}

			tail_hist[knots[9]] = true;
		}

	}

	int sol = 0;
	for (auto& key : tail_hist)
	{
		if (key.second)
			sol += 1;
	}

	std::cout << "Problem 9b solution = " << sol << std::endl;
}
