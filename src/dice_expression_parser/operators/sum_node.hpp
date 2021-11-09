#ifndef OPERATORS_SUM_NODE
#define OPERATORS_SUM_NODE

#include "dice_expression_parser/node.hpp"

namespace pathfinder2::dice
{
	struct sum_node: public inode 
	{
		sum_node() = default; 
		sum_node(std::unique_ptr<inode> left, std::unique_ptr<inode> right);
		~sum_node() = default; 

		int compute() override; 
		std::string print() override; 
		std::unordered_map<int, int> get_stats() override;

		static inline const char identifier {'+'}; 
		static inline const unsigned int priority {1};
	};

}

#endif /* OPERATORS_SUM_NODE */
