#include "item_database.hpp"

#include <stdlib.h>
#include <stdexcept>
#include <algorithm>

using std::string;
using std::make_shared;
using SQLite::Database;
using SQLite::Statement;
using SQLite::Transaction;
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

const std::vector<std::shared_ptr<const item_database_entry>> item_database::search_items(const std::string& name)
{
	std::vector<std::shared_ptr<const item_database_entry>> result;

	//Load item from database
	Statement query(database, "SELECT url, name, bulk, description FROM items WHERE name MATCH ?");
	query.bind(1, name);  

	auto item = make_shared<item_database_entry>();

	while (query.executeStep())
	{
		//Build the new item instance
		item->url = string(query.getColumn(0));
		item->name = string(query.getColumn(1));
		item->description = string(query.getColumn(3));

		auto bulk_str = query.getColumn(2);
		item->bulk = bulk_str[0] == 'L' ? 0.1f : atoi(bulk_str);

		//Insert it in the cache and in the result vector
		result.emplace_back(item_cache.insert(item->name, item));
	}

	return result; 
}

std::shared_ptr<const item_database_entry> item_database::get_item(const std::string& name)
{
	try 
	{
		return item_cache[name];
	}
	catch(...)
	{
		//Load item from database
		Statement query(database, "SELECT url, name, bulk, description FROM items WHERE name MATCH ?");
		query.bind(1, name);  

		auto item = make_shared<item_database_entry>();

		while (query.executeStep())
		{
			item->name = string(query.getColumn(1));

			if (name == item->name)
			{
				//Item found, names match
				item->url = string(query.getColumn(0));
				item->description = string(query.getColumn(3));

				auto bulk_str = string(query.getColumn(2));
				item->bulk = bulk_str[0] == 'L' ? 0.1f : atoi(bulk_str.c_str());

				return item_cache.insert(item->name, item);
			}
		}

		throw std::runtime_error("Name not matching.");
	}
}

void item_database::update_url(const std::string& name, const std::string& url)
{
	item_cache[name]->url = url;
	Transaction transaction(database);
	
	Statement query(database, "UPDATE items SET url = ? WHERE name = ?");
	query.bind(1, url);
	query.bind(2, name);
	query.exec(); 

	transaction.commit();
}

void item_database::update_description(const std::string& name, const std::string& description)
{
	item_cache[name]->description = description;
	Transaction transaction(database);
	
	Statement query(database, "UPDATE items SET description = ? WHERE name = ?");
	query.bind(1, description);
	query.bind(2, name);
	query.exec(); 

	transaction.commit();
}

void item_database::update_bulk(const std::string& name, float bulk)
{
	item_cache[name]->bulk = bulk;
	Transaction transaction(database);
	
	Statement query(database, "UPDATE items SET bulk = ? WHERE name = ?");
	query.bind(1, bulk);
	query.bind(2, name);
	query.exec(); 

	transaction.commit();
}

void item_database::update_category(const std::string& name, const std::string& category)
{
	item_cache[name]->category = category;
	Transaction transaction(database);
	
	Statement query(database, "UPDATE items SET category = ? WHERE name = ?");
	query.bind(1, category);
	query.bind(2, name);
	query.exec(); 

	transaction.commit();
}

void item_database::update_bulk(const std::string& name, const std::string& _bulk)
{
	float bulk = _bulk[0] == 'L' ? 0.1f : atoi(_bulk.c_str());
	update_bulk(name, bulk);
}