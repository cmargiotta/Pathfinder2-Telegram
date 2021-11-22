#ifndef OPERATORS_SUBSTRACTION_NODE
#define OPERATORS_SUBSTRACTION_NODE

#include "dice_expression_parser/node.hpp"

namespace pathfinder2::dice
{
	struct substraction_node: public inode 
	{
		substraction_node() = default; 
		substraction_node(std::unique_ptr<inode> left, std::unique_ptr<inode> right);
		~substraction_node() = default; 

		int compute() override; 
		std::string print() override; 

		static inline const char identifier {'-'}; 
		static inline const unsigned int priority {1};
	};

}

#endif /* OPERATORS_SUBSTRACTION_NODE */
