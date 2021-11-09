#include "node.hpp"

#include <stack>
#include <deque>
#include <random>
#include <cstdlib>
#include <utility>
#include <stdexcept>
#include <exception>

#include "node_factory.hpp"
#include "common/string_utils.hpp"

using std::pair; 
using std::stack; 
using std::deque;
using std::string; 
using std::unique_ptr; 
using std::make_unique;

using namespace pathfinder2::dice; 

inode::inode(unique_ptr<inode> _left, unique_ptr<inode> _right):
	left{std::move(_left)},
	right{std::move(_right)}
{}

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
	stack<pair<string, unsigned int>> operators; 

	while (!tokens.empty())
	{
		auto token = tokens.front(); 
		tokens.pop_front(); 

		if (token.empty())
		{
			continue;
		}

		if (common::is_number(token))
		{
			output.push(token); 
		}
		else if (token[0] == '(')
		{
			operators.push(std::make_pair(token, 0)); 
		}
		else if (token[0] == ')')
		{
			while (operators.top().first[0] != '(')
			{
				if (operators.empty())
				{
					throw std::runtime_error("invalid_expression");
				}

				output.push(operators.top().first);
				operators.pop(); 
			}
			//Popping '('
			operators.pop(); 
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

			while (operators.top().first[0] != '(' &&
					operators.top().second >= priority)
			{
				output.push(operators.top().first);
				operators.pop(); 
			}

			operators.push(std::make_pair(token, priority));
		}
	}

	if (!operators.empty())
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

				while (c < expression.end() && !functions.contains(token))
				{
					token += *c; 
					++c;
				}

				if (!functions.contains(token))
				{
					if (!operators.contains(token[0]))
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