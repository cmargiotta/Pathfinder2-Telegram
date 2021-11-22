#ifndef DICE_EXPRESSION_PARSER_NODE
#define DICE_EXPRESSION_PARSER_NODE

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

namespace pathfinder2::dice
{
	class inode
	{
		public:
		 	std::unique_ptr<inode> left, right; 
			std::string str; 
			int last_result; 
			bool leaf = false;

		protected:
			std::string _print(char _operator);

		public: 
			inode(std::unique_ptr<inode> left, std::unique_ptr<inode> right);
			inode() = default;

			virtual ~inode() = default; 
			
			virtual std::string print() = 0; 
			virtual int compute() = 0;
	};
}

#endif /* DICE_EXPRESSION_PARSER_NODE */
