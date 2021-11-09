#include "sum_node.hpp"

#include <memory>

using std::unique_ptr; 
using pathfinder2::dice::inode;
using pathfinder2::dice::sum_node;

sum_node::sum_node(unique_ptr<inode> _left, unique_ptr<inode> _right):
	inode(std::move(_left), std::move(_right))
{}

std::string sum_node::print()
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

	res += "+";

	if (left->leaf)
	{
		res += left->print();
	}
	else
	{
		res += "(" + left->print() + ")";
	}

	return res; 
}

int sum_node::compute()
{
	last_result = left->compute() + right->compute(); 
	return last_result;
}

auto stats_sum(const std::unordered_map<int, int>& res1, const std::unordered_map<int, int>& res2)
{
	std::unordered_map<int, int> res;

	for (auto r1: res1)
	{
		for (auto r2: res2)
		{
			res[r1.first + r2.first] = r1.second + r2.second; 
		}
	} 

	return res; 
}

std::unordered_map<int, int> sum_node::get_stats()
{
	return stats_sum(left->get_stats(), right->get_stats());
}