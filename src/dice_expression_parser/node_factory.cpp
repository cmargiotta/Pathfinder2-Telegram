#include "node_factory.hpp"

#include <functional>
#include <unordered_map>

using std::set;
using std::string;
using std::function; 
using std::unique_ptr;
using std::make_unique; 
using std::unordered_map;

using namespace pathfinder2::dice; 

const unordered_map<char, function<unique_ptr<inode>()>> pathfinder2::dice::operators = 
{
	{dice_node::identifier, [](){return make_unique<dice_node>();}},
	{sum_node::identifier, [](){return make_unique<sum_node>();}}
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