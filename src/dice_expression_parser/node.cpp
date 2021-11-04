#include "node.hpp"

#include <stack>
#include <deque>
#include <random>
#include <cstdlib>
#include <utility>
#include <stdexcept>
#include <exception>

#include "operators/sum_node.hpp"
#include "operators/leaf_node.hpp"
#include "common/string_utils.hpp"
#include "operators/dice_node.hpp"

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

unique_ptr<inode> node_factory(string& token)
{
	switch (token[0])
	{
		case (dice_node::identifier): 
			return make_unique<dice_node>(); 
		case (sum_node::identifier):
			return make_unique<sum_node>(); 
		default: 
			return make_unique<leaf_node>(token); 
	}
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

unique_ptr<inode> parse_tokens(deque<string>& tokens, unique_ptr<inode>& root)
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
	tokens.emplace_back("");

	for (char c: expression)
	{
		switch (c)
		{
			case ' ': 
				break; 
			case dice_node::identifier: 
				if (tokens.empty() || !common::is_number(tokens.back()))
				{
					tokens.emplace_back("1");
				}
			case sum_node::identifier:
				tokens.emplace_back(std::string() + c);
				tokens.emplace_back("");
				break;
			case '(':
				tokens.emplace_back("(");
				tokens.emplace_back("");
				break; 
			case ')':
				tokens.emplace_back(")");
				tokens.emplace_back("");
				break; 
			default:
				tokens.back() += c;
				break; 
		}
	}

	tokens.emplace_back(")");
	unique_ptr<inode> root; 
	return parse_tokens(tokens, root);
}