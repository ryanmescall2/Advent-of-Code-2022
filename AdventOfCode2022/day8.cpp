#pragma once
#include "day8.h"
#include <unordered_map>

void Day8::problem8a()
{
	std::string file_in = "in_day8.txt";
	std::vector<pyStr> data_in = file_lines_to_pystr(file_in);

	int num_row = data_in.size();
	int num_col = data_in[0].len();

	std::vector<std::vector<int>> tree_array;
	for (int i = 0; i < num_row; i++)
	{
		std::vector<int> empty_vec(num_col);
		tree_array.push_back(empty_vec);
	}
	for (int r = 0; r < num_row; r++)
	{
		for (int c = 0; c < num_col; c++)
		{
			tree_array[r][c] = data_in[r].at(c).to_int();
		}
	}

	int sol = 2 * num_row + 2 * (num_col - 2);
	for (int r = 1; r < num_row - 1; r++)
	{
		for (int c = 1; c < num_col - 1; c++)
		{
			int cur_tree_hght = tree_array[r][c];

			bool cur_tree_visible = true;
			for (int idx = 0; idx < c; idx++) // left trees
			{
				if (tree_array[r][idx] >= cur_tree_hght)
				{
					cur_tree_visible = false;
					break;
				}

			}
			if (cur_tree_visible)
			{
				sol += 1;
				continue;
			}

			cur_tree_visible = true;
			for (int idx = 0; idx < r; idx++) // top trees
			{
				if (tree_array[idx][c] >= cur_tree_hght)
				{
					cur_tree_visible = false;
					break;
				}

			}
			if (cur_tree_visible)
			{
				sol += 1;
				continue;
			}

			cur_tree_visible = true;
			for (int idx = c+1; idx < num_col; idx++) // right trees
			{
				if (tree_array[r][idx] >= cur_tree_hght)
				{
					cur_tree_visible = false;
					break;
				}

			}
			if (cur_tree_visible)
			{
				sol += 1;
				continue;
			}

			cur_tree_visible = true;
			for (int idx = r + 1; idx < num_row; idx++) // bottom trees
			{
				if (tree_array[idx][c] >= cur_tree_hght)
				{
					cur_tree_visible = false;
					break;
				}

			}
			if (cur_tree_visible)
			{
				sol += 1;
				continue;
			}
		}
	}

	std::cout << "Problem 8a solution = " << sol << std::endl;
}

void Day8::problem8b()
{
	std::string file_in = "in_day8.txt";
	std::vector<pyStr> data_in = file_lines_to_pystr(file_in);

	int num_row = data_in.size();
	int num_col = data_in[0].len();

	std::vector<std::vector<int>> tree_array;
	for (int i = 0; i < num_row; i++)
	{
		std::vector<int> empty_vec(num_col);
		tree_array.push_back(empty_vec);
	}
	for (int r = 0; r < num_row; r++)
	{
		for (int c = 0; c < num_col; c++)
		{
			tree_array[r][c] = data_in[r].at(c).to_int();
		}
	}

	int max_score = 0;
	for (int r = 1; r < num_row - 1; r++)
	{
		for (int c = 1; c < num_col - 1; c++)
		{
			int cur_tree_score = 1;

			int cur_tree_hght = tree_array[r][c];

			int idx_sol = 0;
			for (int idx = c - 1; idx >= 0; idx--) // left trees
			{
				if (tree_array[r][idx] < cur_tree_hght)
					idx_sol += 1;
				else if (tree_array[r][idx] == cur_tree_hght)
				{
					idx_sol += 1;
					break;
				}
				else
				{
					if (idx_sol == 0)
						idx_sol += 1;
					break;
				}
			}

			cur_tree_score *= idx_sol;
			idx_sol = 0;
			for (int idx = r-1; idx >= 0; idx--) // top trees
			{
				if (tree_array[idx][c] < cur_tree_hght)
					idx_sol += 1;
				else if (tree_array[idx][c] == cur_tree_hght)
				{
					idx_sol += 1;
					break;
				}
				else
				{
					if (idx_sol == 0)
						idx_sol += 1;
					break;
				}
			}

			cur_tree_score *= idx_sol;
			idx_sol = 0;
			for (int idx = c + 1; idx <= num_col - 1; idx++) // right trees
			{
				if (tree_array[r][idx] < cur_tree_hght)
					idx_sol += 1;
				else if (tree_array[r][idx] == cur_tree_hght)
				{
					idx_sol += 1;
					break;
				}
				else
				{
					if (idx_sol == 0)
						idx_sol += 1;
					break;
				}
			}

			cur_tree_score *= idx_sol;
			idx_sol = 0;
			for (int idx = r + 1; idx <= num_col - 1; idx++) // bottom trees
			{
				if (tree_array[idx][c] < cur_tree_hght)
					idx_sol += 1;
				else if (tree_array[idx][c] == cur_tree_hght)
				{
					idx_sol += 1;
					break;
				}
				else
				{
					if (idx_sol == 0)
						idx_sol += 1;
					break;
				}
			}

			cur_tree_score *= idx_sol;
			max_score = std::max(max_score, cur_tree_score);
		}
	}
	
	std::cout << "Problem 8b solution = " << max_score << std::endl;
}
