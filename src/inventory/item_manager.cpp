#include "item_manager.hpp"

#include <stdlib.h>
#include <stdexcept>

using std::string;
using SQLite::Database;
using SQLite::Statement;
using pathfinder2::item;
using std::reference_wrapper;
using pathfinder2::item_manager;

item_manager::item_manager(Database& _database): 
	database(_database),
	item_cache(CACHE_SIZE_LIMIT)
{}

item_manager& item_manager::get_instance(Database* database)
{
	static bool initialized = false;

	if (!initialized && database == nullptr)
	{
		throw std::runtime_error("Cannot initialize item manager without a valid database.");
	}

	initialized = true;
	static item_manager instance(*database);  

	return instance;
}

std::vector<const item*> item_manager::get_items(std::string name)
{
	std::vector<const item*> result;

	try 
	{
		result.emplace_back(&item_cache[name]);
	}
	catch(...)
	{
		//Item not in cache, load from database
		Statement query(database, "SELECT url, name, bulk, description FROM items WHERE name = ?");
		query.bind(1, name);  

		while (query.executeStep())
		{
			//Build the new item instance
			item item_;

			item_.url = string(query.getColumn(0));
			item_.name = string(query.getColumn(1));
			item_.description = string(query.getColumn(3));

			const char* bulk = query.getColumn(2);
			//Convert "L" bulk in 0.1
			float bulk_f = bulk[0] == 'L' ? 0.1f : atoi(bulk);
			item_.bulk = bulk_f;

			//Insert it in the cache and in the result vector
			result.emplace_back(&item_cache.insert(item_.name, item_));
		}
	}

	return result; 
}