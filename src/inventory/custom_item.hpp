#ifndef PATHFINDER2_CUSTOM_ITEM
#define PATHFINDER2_CUSTOM_ITEM

#include <SQLiteCpp/SQLiteCpp.h>

#include "inventory_entry.hpp"

namespace pathfinder2
{
	class custom_item final: public inventory_entry 
	{
		private:  
			SQLite::Database& 			database; 
		
		public: 
			custom_item(const std::string& owner, const std::string& _name, SQLite::Database& database); 
			~custom_item() override;

			void update_quantity(int delta) override;
	};
}

#endif