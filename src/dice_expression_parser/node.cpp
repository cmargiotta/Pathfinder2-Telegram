#include "node.hpp"

#include <list>
#include <stack>
#include <deque>
#include <random>
#include <cstdlib>
#include <utility>
#include <stdexcept>
#include <algorithm>
#include <exception>

#include "node_factory.hpp"
#include "common/string_utils.hpp"

using std::pair; 
using std::stack; 
using std::deque;
using std::string; 
using std::unique_ptr; 
using std::make_unique;
using std::unordered_map;

using namespace pathfinder2::dice; 

inode::inode(unique_ptr<inode> _left, unique_ptr<inode> _right):
	left{std::move(_left)},
	right{std::move(_right)}
{}

std::string inode::get_ascii_stats_chart(int reference_roll)
{
	auto stats = get_stats(); 
	int min_value = std::min_element(stats.begin(), 
							stats.end(), 
							[](const decltype(stats)::value_type& o1, const decltype(stats)::value_type& o2)
							{
								return o1.first < o2.first; 
							})->first;
	int max_value = std::max_element(stats.begin(), 
							stats.end(), 
							[](const decltype(stats)::value_type& o1, const decltype(stats)::value_type& o2)
							{
								return o1.first < o2.first; 
							})->first;
	int max_rolls = std::max_element(stats.begin(), 
							stats.end(), 
							[](const decltype(stats)::value_type& o1, const decltype(stats)::value_type& o2)
							{
								return o1.second < o2.second; 
							})->first;

	double total_rolls = 0.0; 
	for (auto& r: stats)
	{
		total_rolls += r.second; 
	}

	std::list<std::pair<int, double>> compressed_stats; 
	for (auto& r: stats)
	{
		compressed_stats.emplace_back(std::make_pair(r.first, r.second));
	}

	compressed_stats.sort([](const std::pair<int, int>& first, const std::pair<int, int>& second)
						{
							return first.first < second.first; 
						});

	constexpr int bar_width = 25;
	constexpr int max_bars = 20;

	double scale_factor = (bar_width-2.0)/max_rolls;

	while (compressed_stats.size() > max_bars)
	{
		std::list<std::pair<int, double>> temp; 

		while (!compressed_stats.empty())
		{
			auto data1 = compressed_stats.front(); 
			compressed_stats.pop_front(); 
			if (compressed_stats.size() >= 2)
			{
				auto data2 = compressed_stats.front(); 
				compressed_stats.pop_front(); 

				data1.first = data2.first; 
				data1.second = (data1.second + data2.second)/2.0; 
			}
			
			temp.push_back(data1);
		}

		compressed_stats = std::move(temp);
		temp.clear();  
	}

	std::string chart = std::to_string(min_value) + "\n";
	int last_roll = 0; 
	for (auto& r: compressed_stats)
	{
		int pos = r.second * scale_factor;

		for (int i = 0; i < bar_width; ++i)
		{
			if (i <= pos) 
			{
				if (reference_roll <= r.first && reference_roll > last_roll)
				{
					chart += "═";
				}
				else 
				{
					chart += "█";
				}
			}
			else 
			{
				chart += "░";
			}
		}

		last_roll = r.first; 
		chart += "\n";
	}

	chart += std::to_string(max_value) + "\n";

    return chart;
}

unique_ptr<inode> parse_token(stack<string>& tokens)
{
	auto token = tokens.top(); 
	tokens.pop(); 

	auto node = node_factory(token); 

	if (common::is_number(token))
	{
		return node; 
	}
	else 
	{
		node->left = parse_token(tokens); 
		node->right = parse_token(tokens);
	}

	return node; 
}

unique_ptr<inode> parse_tokens(deque<string>& tokens, unique_ptr<inode> root = unique_ptr<inode>())
{
	stack<string> output; 
	stack<pair<string, unsigned int>> operators_; 

	while (!tokens.empty())
	{
		auto token = tokens.front(); 
		tokens.pop_front();

		if (common::is_number(token))
		{
			output.push(token); 
		}
		else if (token[0] == '(')
		{
			operators_.push(std::make_pair(token, 0)); 
		}
		else if (token[0] == ')')
		{
			while (operators_.top().first[0] != '(')
			{
				if (operators_.empty())
				{
					throw std::runtime_error("invalid_expression");
				}

				output.push(operators_.top().first);
				operators_.pop(); 
			}
			//Popping '('
			operators_.pop(); 
		}
		else if (functions.count(token))
		{
			operators_.emplace(make_pair(token, 0)); 
		}
		else 
		{
			unsigned int priority;

			if (token[0] == dice_node::identifier)
			{
				priority = dice_node::priority;
			}
			else 
			{
				priority = sum_node::priority;
			}

			while (operators_.top().first[0] != '(' &&
					operators_.top().second >= priority)
			{
				output.push(operators_.top().first);
				operators_.pop(); 
			}

			operators_.push(std::make_pair(token, priority));
		}
	}

	if (!operators_.empty())
	{
		throw std::runtime_error("invalid_expression");
	}

	return parse_token(output);
}

unique_ptr<inode> pathfinder2::dice::build_dice_tree(const string& expression)
{
	deque<string> tokens; 
	tokens.emplace_back("(");

	auto c = expression.begin();
	while (c < expression.end())
	{
		while (*c == ' ')
		{
			++c; 
		}

		if (*c == '(' || *c == ')')
		{
			tokens.emplace_back(std::string() + *c); 
			++c;
		}
		else 
		{
			std::string token; 

			if (common::is_number(token + *c))
			{
				while (c < expression.end() && common::is_number(token + *c))
				{
					token += *c;
					++c;
				}
			}
			else
			{
				auto c_backup = c+1; 

				while (c < expression.end() && !functions.count(token))
				{
					token += *c; 
					++c;
				}

				if (!functions.count(token))
				{
					if (!operators.count(token[0]))
					{
						throw std::runtime_error("invalid_expression");
					}

					c = c_backup; 
					token = std::string() + token[0]; 
				}
			}

			tokens.push_back(token);
		}
	}

	tokens.emplace_back(")");
	return parse_tokens(tokens);
}