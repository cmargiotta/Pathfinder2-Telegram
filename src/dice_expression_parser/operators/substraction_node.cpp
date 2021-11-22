#include "substraction_node.hpp"

#include <memory>

using std::unique_ptr; 
using pathfinder2::dice::inode;
using pathfinder2::dice::substraction_node;

substraction_node::substraction_node(unique_ptr<inode> _left, unique_ptr<inode> _right):
	inode(std::move(_left), std::move(_right))
{}

std::string substraction_node::print()
{
	return inode::_print(identifier);
}

int substraction_node::compute()
{
	last_result = left->compute() - right->compute(); 
	return last_result;
}