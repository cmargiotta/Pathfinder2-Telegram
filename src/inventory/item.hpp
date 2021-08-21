#ifndef PATHFINDER2_ITEM
#define PATHFINDER2_ITEM

#include <SQLiteCpp/SQLiteCpp.h>

#include "inventory_entry.hpp"
#include "item_database.hpp"

namespace pathfinder2
{
	class item final: public inventory_entry 
	{
		private:  
			const item_database_entry* 	data; 
			SQLite::Database& 			database; 
		
		public: 
			item(const std::string& owner, const std::string& _name, SQLite::Database& database); 
			~item() override;

			const std::string& get_url() const override; 
			const std::string& get_description() const override; 

			void update_quantity(int delta) override;
	};
}

#endif