#include "node_factory.hpp"

#include <list>
#include <stack>
#include <deque>
#include <string>
#include <random>
#include <cstdlib>
#include <utility>
#include <stdexcept>
#include <algorithm>
#include <exception>
#include <functional>
#include <unordered_map>

#include "common/string_utils.hpp"
#include "operators/sum_node.hpp"
#include "operators/leaf_node.hpp"
#include "operators/dice_node.hpp"
#include "operators/substraction_node.hpp"

using std::set;
using std::pair; 
using std::stack; 
using std::deque;
using std::string;
using std::function; 
using std::unique_ptr;
using std::make_unique; 
using std::unordered_map;

using namespace pathfinder2::dice; 

const unordered_map<char, function<unique_ptr<inode>()>> pathfinder2::dice::operators = 
{
	{dice_node::identifier, [](){return make_unique<dice_node>();}},
	{sum_node::identifier, [](){return make_unique<sum_node>();}},
	{substraction_node::identifier, [](){return make_unique<substraction_node>();}}
};

const unordered_map<string, function<unique_ptr<inode>()>> pathfinder2::dice::functions = {

};

unique_ptr<inode> pathfinder2::dice::node_factory(const string& token)
{
	try 
	{
		if (token.size() == 1)
		{
			return operators.at(token[0])();
		}
		else
		{
			return functions.at(token)();
		}
	}
	catch(...)
	{
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
		node->right = parse_token(tokens); 
		node->left = parse_token(tokens);
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

			switch(token[0])
			{
				case dice_node::identifier:
					priority = dice_node::priority;
					break;
				case sum_node::identifier:
					priority = sum_node::priority;
					break;
				case substraction_node::identifier:
					priority = substraction_node::priority;
					break;
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