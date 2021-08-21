#include <string>
#include <vector>
#include <functional>
#include <SQLiteCpp/SQLiteCpp.h>

#include "cache.hpp"

namespace pathfinder2 
{
	struct item 
	{
		std::string url; 
		std::string name; 
		std::string description;
		float	   	bulk; 
	};

	class item_manager
	{
		private:
			static const std::size_t CACHE_SIZE_LIMIT = 3000; 

			SQLite::Database& 					database; 
			common::cache<std::string, item> 	item_cache;

			//Singleton, private constructor
			item_manager(SQLite::Database& database);

		public:  
			static item_manager& get_instance(SQLite::Database* database = nullptr); 

			std::vector<const item*> get_items(std::string name); 
	};
}