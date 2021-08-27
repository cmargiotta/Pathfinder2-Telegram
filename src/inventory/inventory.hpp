#ifndef INVENTORY_HPP_
#define INVENTORY_HPP_

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
			std::string														 				owner;
			SQLite::Database& 																database; 
			std::unordered_map<std::string, std::list<std::shared_ptr<inventory_entry>>>	content_category;
			std::unordered_map<std::string, std::shared_ptr<inventory_entry>> 				content_name;

		public: 
			inventory(const std::string& owner, SQLite::Database& database); 
			~inventory() = default;

			//Add an item from database or an item already in this inventory
			void add_item(const std::string& name);
			//Add a new custom item
			void add_item(const std::string& name, const std::string& bulk, const std::string& category);

			void remove_item(const std::string& name);
	};
}

#endif // INVENTORY_HPP_