#ifndef PATHFINDER2_ITEM_DATABASE
#define PATHFINDER2_ITEM_DATABASE

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <SQLiteCpp/SQLiteCpp.h>

#include "cache.hpp"

namespace pathfinder2 
{
	struct item_database_entry
	{
		std::string url; 
		std::string name; 
		std::string description;
		std::string category;
		float		bulk; 
	};

	class item_database
	{
		private:
			static const std::size_t CACHE_SIZE_LIMIT = 3000; 

			SQLite::Database& 									database; 
			common::cache<std::string, item_database_entry> 	item_cache;

			//Singleton, private constructor
			item_database(SQLite::Database& database);

		public:  
			static item_database& get_instance(SQLite::Database* database = nullptr); 

			void update_url(const std::string& name, const std::string& url);
			void update_category(const std::string& name, const std::string& category);
			void update_description(const std::string& name, const std::string& description);
			void update_bulk(const std::string& name, const std::string& bulk);
			void update_bulk(const std::string& name, float bulk);

			const std::vector<std::shared_ptr<const item_database_entry>> search_items(const std::string& name);
			std::shared_ptr<const item_database_entry> get_item(const std::string& name);
	};
}

#endif