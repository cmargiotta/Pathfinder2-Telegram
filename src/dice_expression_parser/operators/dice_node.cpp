#include "dice_node.hpp"

#include <memory>
#include <random>

using std::unique_ptr; 
using pathfinder2::dice::inode;
using pathfinder2::dice::dice_node;

dice_node::dice_node(unique_ptr<inode> _left, unique_ptr<inode> _right):
	inode(std::move(_left), std::move(_right))
{}

std::string dice_node::print()
{
	std::string res;
	
	if (right->leaf)
	{
		res += right->print();
	}
	else
	{
		res += "(" + right->print() + ")";
	}

	res += "d";

	if (left->leaf)
	{
		res += left->print();
	}
	else
	{
		res += "(" + left->print() + ")";
	}
	
	res += "["; 

	while (!results.empty())
	{
		res += std::to_string(results.front());
		results.pop(); 

		if (!results.empty())
		{
			res += ",";
		} 
	}

	res += "]";
	return res; 
}

int dice_node::compute()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());

	leaf = right->leaf && left->leaf;

	results = std::queue<int>(); 

	int rolls = right->compute(); 
	int dice_size = left->compute(); 
	last_result = 0; 

	std::uniform_int_distribution<> distrib(1, dice_size);

	while (rolls) 
	{
		auto res = distrib(gen);
		results.push(res); 

		last_result += res; 
		rolls--; 
	}

	return last_result; 
}