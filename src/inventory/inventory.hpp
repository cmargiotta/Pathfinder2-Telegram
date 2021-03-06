#ifndef INVENTORY_HPP_
#define INVENTORY_HPP_

#include <set>
#include <list>
#include <string>
#include <memory>
#include <unordered_map>
#include <SQLiteCpp/SQLiteCpp.h>

#include "inventory_entry.hpp"

namespace pathfinder2
{
	class inventory
	{
		private: 
			int																 				owner;
			SQLite::Database& 																database; 
			std::unordered_map<std::string, std::list<std::shared_ptr<inventory_entry>>>	content_category;
			std::unordered_map<std::string, std::shared_ptr<inventory_entry>> 				content_name;
			std::set<std::string>															item_names_full, item_names_user;

			void delete_invalid_items();
			void erase_item(const std::string& name);

		public: 
			inventory(int owner, SQLite::Database& database); 
			~inventory() = default;

			//Add an item from database or an item already in this inventory
			void add_item(const std::string& name);
			//Add a new custom item
			void add_item(const std::string& name, const std::string& bulk, const std::string& category);

			void remove_item(const std::string& name);

			std::shared_ptr<const inventory_entry> get_item(const std::string& name) const;

			double get_occupied_bulk();
			const std::set<std::string>& get_item_list(bool master = false);

			const decltype(content_category)& get_categorised_items();

			void reset();
	};
}

#endif // INVENTORY_HPP_