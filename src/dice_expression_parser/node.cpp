#include "node.hpp"

using std::unique_ptr;

using namespace pathfinder2::dice; 

inode::inode(unique_ptr<inode> _left, unique_ptr<inode> _right):
	left{std::move(_left)},
	right{std::move(_right)}
{}

std::string inode::_print(char _operator)
{
	std::string res;

	if (left->leaf)
	{
		res += left->print();
	}
	else
	{
		res += "(" + left->print() + ")";
	}

	res += _operator;
	
	if (right->leaf)
	{
		res += right->print();
	}
	else
	{
		res += "(" + right->print() + ")";
	}

	return res;
}