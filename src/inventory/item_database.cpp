#include "item_database.hpp"

#include <stdlib.h>
#include <stdexcept>
#include <algorithm>
#include <functional>

#include "common/string_utils.hpp"

using std::string;
using std::make_shared;
using SQLite::Database;
using SQLite::Statement;
using SQLite::Transaction;
using pathfinder2::item_database;
using pathfinder2::item_database_entry;

std::shared_ptr<item_database_entry> item_database::build_entry(const std::string& name)
{
	//Load item from database
	Statement query(database, "SELECT url, name, bulk, description, category FROM items WHERE name MATCH ?");
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
			item->category = string(query.getColumn(4));

			item->bulk = query.getColumn(2);

			return item;
		}
	}

	throw std::runtime_error("item_not_found");
}

item_database::item_database(Database& _database): 
	database(_database),
	item_cache(CACHE_SIZE_LIMIT, std::bind(&item_database::build_entry, this, std::placeholders::_1))
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

void item_database::register_new_item(const string& name, const string& url, const string& category, const string& description, const string& bulk)
{
	if (item_cache.contains(name))
	{
		throw std::runtime_error("no_duplicate_items");
	}

	if (bulk.empty() || (!std::all_of(bulk.begin(), bulk.end(), ::isdigit) && !(bulk.size() == 1 && bulk[0] == 'L')))
	{
		throw std::runtime_error("bulk_error");
	}

	Transaction transaction (database);

	Statement query (database, "INSERT INTO items (name, url, category, description, bulk) VALUES (?, ?, ?, ?, ?)");
	query.bind(1, name);
	query.bind(2, url);
	query.bind(3, category);
	query.bind(4, common::escape(description, common::to_escape, '\\'));
	query.bind(5, bulk);
	query.exec();

	transaction.commit();
}

void item_database::delete_item(const std::string& name)
{
	item_cache[name]->deleted = true;
	
	Transaction transaction (database);

	Statement query (database, "DELETE FROM inventory WHERE name = ?");
	query.bind(1, name);
	query.exec();

	Statement query1 (database, "DELETE FROM items WHERE name = ?");
	query1.bind(1, name);
	query1.exec();

	transaction.commit();

	item_cache.remove(name);
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

std::shared_ptr<item_database_entry> item_database::get_nonconst_item(const std::string& name)
{
	return item_cache[name];
}

std::shared_ptr<const item_database_entry> item_database::get_item(const std::string& name)
{
	return get_nonconst_item(name);
}

void item_database::update_url(const std::string& name, const std::string& url)
{
	get_nonconst_item(name)->url = url;
	Transaction transaction(database);
	
	Statement query(database, "UPDATE items SET url = ? WHERE name = ?");
	query.bind(1, url);
	query.bind(2, name);
	query.exec(); 

	transaction.commit();
}

void item_database::update_description(const std::string& name, const std::string& description)
{
	get_nonconst_item(name)->description = description;
	Transaction transaction(database);
	
	Statement query(database, "UPDATE items SET description = ? WHERE name = ?");
	query.bind(1, description);
	query.bind(2, name);
	query.exec(); 

	transaction.commit();
}

void item_database::update_bulk(const std::string& name, double bulk)
{
	Transaction transaction(database);
	
	Statement query(database, "UPDATE items SET bulk = ? WHERE name = ?");
	query.bind(1, bulk);
	query.bind(2, name);
	query.exec(); 

	transaction.commit();

	get_nonconst_item(name)->bulk = bulk;
}

void item_database::update_category(const std::string& name, const std::string& category)
{
	get_nonconst_item(name)->category = category;
	Transaction transaction(database);
	
	Statement query(database, "UPDATE items SET category = ? WHERE name = ?");
	query.bind(1, category);
	query.bind(2, name);
	query.exec(); 

	transaction.commit();
}

void item_database::update_bulk(const std::string& name, const std::string& _bulk)
{
	double bulk = _bulk[0] == 'L' ? 0.1f : atoi(_bulk.c_str());
	update_bulk(name, bulk);
}