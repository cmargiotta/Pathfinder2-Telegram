#ifndef DICE_EXPRESSION_PARSER_NODE
#define DICE_EXPRESSION_PARSER_NODE

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

namespace pathfinder2::dice
{
	struct inode
	{
		std::unique_ptr<inode> left, right; 
		std::string str; 
		int last_result; 
		bool leaf = false;

		inode(std::unique_ptr<inode> left, std::unique_ptr<inode> right);
		inode() = default;

		virtual ~inode() = default; 
		
		virtual std::string print() = 0; 
		virtual int compute() = 0;
		virtual std::unordered_map<int, int> get_stats() = 0;

		std::string get_ascii_stats_chart(int reference_roll = -1); 
	};

	std::unique_ptr<inode> build_dice_tree(const std::string& expression);
}

#endif /* DICE_EXPRESSION_PARSER_NODE */
