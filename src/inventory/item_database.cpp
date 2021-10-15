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
	Statement query(database, "SELECT url, name, bulk, description, category FROM items WHERE name = ?");
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

			Statement data_query(database, "SELECT image FROM item_data WHERE name = ?");
			data_query.bind(1, name);

			while (data_query.executeStep())
			{
				item->image = data_query.getColumn(0).getString();
			}

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

void item_database::register_new_item(const string& name, const string& url, const string& category, const string& description, const string& _bulk)
{
	if (item_cache.contains(name))
	{
		throw std::runtime_error("no_duplicate_items");
	}

	float bulk;
	auto bulk_string = _bulk;
	if (bulk_string.back() == 'l')
	{
		bulk_string.back() = 'L';
	}

	if (bulk_string.empty() || 
		bulk_string[0] == '-' ||
		!(common::is_number(bulk_string) || (bulk_string.back() == 'L' && (
											common::is_number(bulk_string.substr(0, bulk_string.size() - 1)) ||
											bulk_string.size() == 1))))
	{
		throw std::runtime_error("bulk_error");
	}

	if (bulk_string == "1L")
	{
		bulk_string = "L";
	}

	if (bulk_string.back() == 'L')
	{
		if (bulk_string.size() == 1)
		{
			bulk = 0.1;
		}
		else 
		{
			bulk_string.back() = '\0';

			bulk = 0.1 * atoi(bulk_string.c_str());
			bulk_string.back() = 'L';
		}
	}
	else 
	{
		bulk = static_cast<double>(atoi(bulk_string.c_str()));
	}

	Transaction transaction (database);

	Statement query (database, "INSERT INTO items (name, url, category, description, bulk) VALUES (?, ?, ?, ?, ?)");
	query.bind(1, name);
	query.bind(2, url);
	query.bind(3, category);
	query.bind(4, description);
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

const std::vector<std::string> item_database::search_items(const std::string& name)
{
	std::vector<std::string> result;

	//Load item from database
	Statement query(database, "SELECT name FROM items WHERE name MATCH ?");
	query.bind(1, name);  

	while (query.executeStep())
	{
		result.emplace_back(std::string(query.getColumn(0)));
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
	auto a = get_nonconst_item(name);
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

void item_database::update_image(const std::string& name, const std::string& data)
{
	get_nonconst_item(name)->image = data;

	Statement _query(database, "SELECT name FROM item_data WHERE name = ?");
	_query.bind(1, name);
	bool found = false;

	while (_query.executeStep())
	{
		found = true;
	}

	Transaction transaction(database);

	if (!found)
	{
		Statement query (database, "INSERT INTO item_data (name, image) VALUES (?, ?)");
		query.bind(1, name);
		query.bindNoCopy(2, data);
		query.exec();
	}
	else  
	{
		Statement query(database, "UPDATE item_data SET image = ? WHERE name = ?");
		query.bindNoCopy(1, data);
		query.bind(2, name);
		query.exec(); 
	}

	transaction.commit();
}
