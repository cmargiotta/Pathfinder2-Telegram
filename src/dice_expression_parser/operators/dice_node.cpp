#include "dice_node.hpp"

#include <memory>
#include <random>
#include <stdexcept>

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

	if (dice_size < 1)
	{
		throw std::runtime_error("dice_error");
	}

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

auto dice_results(int size)
{
	std::unordered_map<int, int> res;
	res.reserve(size); 
	
	for (int i = 1; i <= size; ++i)
	{
		res[i] = 1;
	}

	return res; 
}

auto dice_sum(const std::unordered_map<int, int>& res1, const std::unordered_map<int, int>& res2)
{
	std::unordered_map<int, int> res;

	for (auto r1: res1)
	{
		for (auto r2: res2)
		{
			res[r1.first + r2.first] += r1.second + r2.second; 
		}
	} 

	return res; 
}

//TODO optimize
std::unordered_map<int, int> dice_node::get_stats()
{
	auto dice_size_stats = left->get_stats(); 
	auto rolls_stats = right->get_stats(); 

	std::unordered_map<int, int> res;

	for (auto rolls: rolls_stats)
	{
		for (auto dice_size: dice_size_stats)
		{
			auto dice_stats = dice_results(dice_size.first); 
			auto current_stats = dice_stats;

			for (int roll = 1; roll < rolls.first; ++roll)
			{
				current_stats = dice_sum(current_stats, dice_stats); 
			}

			for (auto s: current_stats)
			{
				res[s.first] += (s.second*rolls.second*dice_size.second); 
			}
		}
	}

	return res; 
}