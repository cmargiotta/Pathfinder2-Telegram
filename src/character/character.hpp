#ifndef CHARACTER_CHARACTER_HPP
#define CHARACTER_CHARACTER_HPP

#include <set>
#include <string>
#include <SQLiteCpp/SQLiteCpp.h>

#include "inventory/inventory.hpp"

namespace pathfinder2
{
	class character
	{
		private:
			int					id;
			int					cp;
			int					capacity;
			std::string 		username;
			std::string			context;
			std::string			data;

			SQLite::Database& 	database;
			inventory 			_inventory;

		public:
			character(int id, SQLite::Database& database);
			~character() = default;

			inventory& get_inventory();
			const std::string& get_context();
			const std::string& get_data();
			const std::string& get_username();
			int get_id();
			int get_cp();
			int get_capacity();

			void update_cp(int delta);
			void set_capacity(int capacity);
			void set_context(const std::string& context);
			void set_data(const std::string& data);
			void set_username(const std::string& username);

			static const std::set<int> get_characters_ids(SQLite::Database& database);
	};
}
#endif /* CHARACTER_CHARACTER_HPP */
