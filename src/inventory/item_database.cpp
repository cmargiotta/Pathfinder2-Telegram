#include "item_database.hpp"

#include <stdlib.h>
#include <stdexcept>
#include <algorithm>

using std::string;
using SQLite::Database;
using SQLite::Statement;
using std::reference_wrapper;
using pathfinder2::item_database;
using pathfinder2::item_database_entry;

item_database::item_database(Database& _database): 
	database(_database),
	item_cache(CACHE_SIZE_LIMIT)
{}

item_database& item_database::get_instance(Database* database)
{
	static bool initialized = false;

	if (!initialized && database == nullptr)
	{
		throw std::runtime_error("Cannot initialize item manager without a valid database.");
	}

	initialized = true;
	static item_database instance(*database);  

	return instance;
}

std::vector<const item_database_entry*> item_database::search_items(const std::string& name)
{
	std::vector<const item_database_entry*> result;

	//Load item from database
	Statement query(database, "SELECT url, name, bulk, description FROM items WHERE name MATCH ?");
	query.bind(1, name);  

	item_database_entry item;

	while (query.executeStep())
	{
		//Build the new item instance
		item.url = string(query.getColumn(0));
		item.name = string(query.getColumn(1));
		item.description = string(query.getColumn(3));

		auto bulk_str = string(query.getColumn(2));
		item.bulk = bulk_str[0] == 'L' ? 0.1f : atoi(bulk_str.c_str());

		//Insert it in the cache and in the result vector
		result.emplace_back(&item_cache.insert(item.name, item));
	}

	return result; 
}

const item_database_entry* item_database::get_item(const std::string& name)
{
	try 
	{
		return &item_cache[name];
	}
	catch(...)
	{
		//Load item from database
		Statement query(database, "SELECT url, name, bulk, description FROM items WHERE name MATCH ?");
		query.bind(1, name);  

		item_database_entry item;

		while (query.executeStep())
		{
			item.name = string(query.getColumn(1));

			if (std::equal(name.begin(), name.end(), item.name.begin(), item.name.end()))
			{
				//Item found, names match
				item.url = string(query.getColumn(0));
				item.description = string(query.getColumn(3));

				auto bulk_str = string(query.getColumn(2));
				item.bulk = bulk_str[0] == 'L' ? 0.1f : atoi(bulk_str.c_str());

				return &item_cache.insert(item.name, item);
			}
		}

		throw std::runtime_error("Name not matching.");
	}
}