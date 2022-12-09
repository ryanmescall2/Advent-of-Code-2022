#pragma once
#include "day7.h"
#include <map>

class CommandPrompt
{
	pyStr parsing_dir = pyStr("");

	void parse_cd(pyStr line)
	{
		pyStr line_info = line.startat(1);
	};

	void parse_ls(pyStr line)
	{
		pyStr line_info = line.startat(1);
		parsing_dir = line_info;
	};

	void parse_user_command(pyStr line)
	{
		pyStr line_info = line.startat(3);

		if (line_info.substr(0, 1) == "cd")
			parse_cd(line_info);
		else if (line_info.substr(0, 1) == "ls")
			parse_ls(line_info);
	};

	void parse_control_output(pyStr line)
	{
		
	};

	void parse_line(pyStr line)
	{
		if (line.at(0) == "$")
			parse_user_command(line);
		else
			parse_control_output(line);
	};
};

void Day7::problem7a()
{

	std::string file_in = "in_day7.txt";
	std::vector<pyStr> data_in = file_lines_to_pystr(file_in);

	for (auto& line : data_in)
	{

	}
	std::cout << "Problem 7a solution = " << 0 << std::endl;
}

void Day7::problem7b()
{

	std::cout << "Problem 7b solution = " << 0 << std::endl;
}
