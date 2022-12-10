#pragma once
#include "day7.h"
#include <unordered_map>

struct Node
{
	Node* p_parent;
	std::vector<Node*> p_children;
	bool is_dir;
	pyStr name;
	int size_content;

	Node(pyStr name_) { name = name_; };
	Node(Node* p_parent_, pyStr name_, bool is_dir_, int size_content_ = 0) 
		: p_parent(p_parent_)
		, name(name_)
		, is_dir(is_dir_) 
		, size_content(size_content_)
	{};

	bool node_name_is_child(pyStr pot_child_name)
	{
		bool node_is_child = false;
		for (auto child : p_children)
		{
			if (child->name == pot_child_name)
			{
				node_is_child = true;
				break;
			}
		}
		return node_is_child;
	};
};

struct CommandPrompt
{
	Node* p_root = new Node(NULL, pyStr('/'), true);
	pyStr root_name = p_root->name;
	Node* p_curnode = p_root;
	Node* p_lsnode  = p_root;

	void add_file_size_to_parents(Node* p_fnode)
	{
		int file_size = p_fnode->size_content;
		Node* p_parentnode = p_fnode->p_parent;

		while (p_parentnode)
		{
			p_parentnode->size_content += file_size;
			p_parentnode = p_parentnode->p_parent;
		}
	};

	Node* create_new_dir_node(pyStr new_dir_name)
	{
		if (!p_curnode->node_name_is_child(new_dir_name))
		{
			Node* new_node = new Node(p_curnode, new_dir_name, true);
			p_curnode->p_children.push_back(new_node);
			return new_node;
		}
		else
		{
			for (auto child : p_curnode->p_children)
			{
				if (child->name == new_dir_name)
					return child;
			}
		}
	};

	void parse_cd(pyStr line)
	{
		pyStr line_info = line;
		if (p_curnode->node_name_is_child(line_info))
		{
			for (auto child : p_curnode->p_children)
			{
				if (child->name == line_info)
					p_curnode = child;
			}
		}
		else if (line == "..")
			p_curnode = p_curnode->p_parent;
		else if (line_info != p_curnode->name)
			p_curnode = create_new_dir_node(line_info);
	};

	void parse_ls()
	{
		return;
	};

	void parse_user_command(pyStr line)
	{
		pyStr line_info = line.startat(5);

		if (line.substr(2, 3) == "cd")
			parse_cd(line_info);
		else if (line.startat(2) == "ls")
			parse_ls();
	};

	void parse_control_output(pyStr line)
	{
		if (line.substr(0, 2) == "dir")
		{
			pyStr dir_name = line.startat(4);
			create_new_dir_node(dir_name);
		}
		else
		{
			std::vector<pyStr> file_contents = line.split(" ");
			int file_size = file_contents[0].to_int();
			pyStr file_name = file_contents[1];

			if (!p_curnode->node_name_is_child(file_name))
			{
				Node* new_node = new Node(p_curnode, file_name, false, file_size);
				add_file_size_to_parents(new_node);
			}
		}

	};

	void parse_line(pyStr line)
	{
		if (line.at(0) == "$")
			parse_user_command(line);
		else
			parse_control_output(line);
	};

	std::unordered_map<std::string, int> get_map_dir_sizes()
	{
		std::unordered_map<std::string, int> map_dir_size;

		std::vector<Node*> tree_traverse_stack;
		tree_traverse_stack.push_back(p_root);

		while (tree_traverse_stack.size() > 0)
		{
			p_curnode = tree_traverse_stack[tree_traverse_stack.size()-1];

			if (!p_curnode->is_dir)
				tree_traverse_stack.pop_back();
			else
			{
				std::string map_key = p_curnode->name.std_string();
				if (p_curnode->p_parent)
					map_key = p_curnode->p_parent->name.std_string() + map_key;
				map_dir_size[map_key] = p_curnode->size_content;
				tree_traverse_stack.pop_back();

				for (auto child : p_curnode->p_children)
					tree_traverse_stack.push_back(child);
			}
		}

		return map_dir_size;
	};

};

void Day7::problem7a()
{
	std::string file_in = "in_day7.txt";
	std::vector<pyStr> data_in = file_lines_to_pystr(file_in);

	CommandPrompt cmd;

	for (auto& line : data_in)
	{
		cmd.parse_line(line);
	}

	std::unordered_map<std::string, int> map_dir_size = cmd.get_map_dir_sizes();

	int sol = 0;
	for (auto& key : map_dir_size)
	{
		if (key.second <= 100000)
			sol += key.second;
	}

	std::cout << "Problem 7a solution = " << sol << std::endl;
}

void Day7::problem7b()
{
	std::string file_in = "in_day7.txt";
	std::vector<pyStr> data_in = file_lines_to_pystr(file_in);

	CommandPrompt cmd;

	for (auto& line : data_in)
	{
		cmd.parse_line(line);
	}

	std::unordered_map<std::string, int> map_dir_size = cmd.get_map_dir_sizes();

	int size_root = map_dir_size[cmd.root_name.std_string()];
	int unused_space = 70000000 - size_root;
	int space_needed = 30000000;
	int space_needed_to_delete = space_needed - unused_space;

	std::tuple<int, int> sol_extraspacedel(0,1000000000);
	for (auto& key : map_dir_size)
	{
		int spc_left_after_del = key.second - space_needed_to_delete;
		if (spc_left_after_del >= 0 && spc_left_after_del < std::get<1>(sol_extraspacedel))
			sol_extraspacedel = std::make_tuple(key.second, spc_left_after_del);
	}

	std::cout << "Problem 7b solution = " << std::get<0>(sol_extraspacedel) << std::endl;
}
