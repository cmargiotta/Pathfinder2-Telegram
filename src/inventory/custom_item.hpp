#ifndef PATHFINDER2_CUSTOM_ITEM
#define PATHFINDER2_CUSTOM_ITEM

#include <SQLiteCpp/SQLiteCpp.h>

#include "inventory_entry.hpp"

namespace pathfinder2
{
	class custom_item final: public inventory_entry 
	{
		private:  
			SQLite::Database& database; 
		
		public: 
			//Select an existing item from database
			custom_item(const std::string& owner, const std::string& name, SQLite::Database& database); 
			//Select an existing item from database, if it does not exist a new custom item is created
			custom_item(const std::string& owner, 
						const std::string& name, 
						const std::string& category,
						const std::string& bulk,
						SQLite::Database& database); 
			~custom_item() override;

			void update_quantity(int delta) override;

			void set_category(const std::string& category) override;
			void set_bulk(const std::string& bulk) override;
	};
}

#endif