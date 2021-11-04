#ifndef OPERATORS_LEAF_NODE
#define OPERATORS_LEAF_NODE

#include "dice_expression_parser/node.hpp"

namespace pathfinder2::dice
{
	struct leaf_node: public inode
	{
		int value; 

		leaf_node() = default; 
		leaf_node(int value); 
		leaf_node(const std::string& value);
		~leaf_node() = default; 

		int compute() override;
		std::string print() override; 

		static inline const unsigned int priority {0};
	};
}

#endif /* OPERATORS_LEAF_NODE */
