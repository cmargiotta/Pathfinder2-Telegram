#include "leaf_node.hpp"

#include <memory>
#include <random>

using std::unique_ptr; 
using pathfinder2::dice::inode;
using pathfinder2::dice::leaf_node;

leaf_node::leaf_node(int _value): 
	value{_value}
{
	leaf = true; 
}

leaf_node::leaf_node(const std::string& _value): 
	value{std::stoi(_value)}
{
	leaf = true; 
}

std::string leaf_node::print()
{
	return std::to_string(value); 
}

int leaf_node::compute()
{
	return value; 
}

std::unordered_map<int, int> leaf_node::get_stats()
{
	return {{value, 1}};
}