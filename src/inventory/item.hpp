#ifndef PATHFINDER2_ITEM
#define PATHFINDER2_ITEM

#include <memory>
#include <SQLiteCpp/SQLiteCpp.h>

#include "inventory_entry.hpp"
#include "item_database.hpp"

namespace pathfinder2
{
	class item final: public inventory_entry 
	{
		private:  
			std::shared_ptr<const item_database_entry> 	data; 
			SQLite::Database& 							database; 
		
		public: 
			item(int owner, const std::string& _name, SQLite::Database& database); 
			~item() override;

			const std::string& get_url() const override; 
			const std::string& get_description() const override; 
			const std::string& get_category() const override;
			const std::string& get_bulk_string() const override;
			double get_bulk() const override;

			void update_quantity(int delta) override;
			void set_url(const std::string& url) override;
			void set_bulk(const std::string& bulk) override;
			void set_category(const std::string& category) override;
			void set_description(const std::string& description) override;
			void remove() override;

			bool is_valid() override;
	};
}

#endif