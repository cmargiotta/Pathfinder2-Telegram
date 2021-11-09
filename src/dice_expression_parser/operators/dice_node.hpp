#ifndef OPERATORS_DICE_NODE
#define OPERATORS_DICE_NODE

#include "dice_expression_parser/node.hpp"

#include <queue>

namespace pathfinder2::dice
{
	struct dice_node: public inode
	{
		dice_node() = default;
		dice_node(std::unique_ptr<inode> left, std::unique_ptr<inode> right);
		~dice_node() = default; 

		int compute() override;
		std::string print() override; 
		std::unordered_map<int, int> get_stats() override;

		static inline const char identifier {'d'};   
		static inline const uint8_t priority {255};

		std::queue<int> results; 
	};
}

#endif /* OPERATORS_DICE_NODE */
