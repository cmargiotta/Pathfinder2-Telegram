#ifndef DICE_EXPRESSION_PARSER_NODE_FACTORY
#define DICE_EXPRESSION_PARSER_NODE_FACTORY

#include <set>
#include <string>
#include <memory>
#include <functional>
#include <unordered_map>

#include "node.hpp"

namespace pathfinder2::dice
{
	extern const std::unordered_map<char, std::function<std::unique_ptr<inode>()>> operators;
	extern const std::unordered_map<std::string, std::function<std::unique_ptr<inode>()>> functions; 

	std::unique_ptr<inode> node_factory(const std::string& token);

	std::unique_ptr<inode> build_dice_tree(const std::string& expression);
}

#endif /* DICE_EXPRESSION_PARSER_NODE_FACTORY */
