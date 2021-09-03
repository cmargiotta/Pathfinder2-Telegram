#include "item.hpp"

#include <stdlib.h>

#include "item_database.hpp"

using std::string;
using SQLite::Database;
using SQLite::Statement;
using pathfinder2::item;
using SQLite::Transaction;
using pathfinder2::item_database;

item::item(int _owner, const string& _name, SQLite::Database& _database):
	database(_database)
{
	auto& item_db = item_database::get_instance();
	bool found = false;

	Statement query(database, "SELECT quantity FROM inventory WHERE owner = ? AND name = ?");
	query.bind(1, _owner);
	query.bind(2, _name);

	while (query.executeStep())
	{
		found = true;
		quantity = query.getColumn(0);

		break;
	}

	data = item_db.get_item(_name);
	name = _name;
	owner = _owner;

	if (!found)
	{
		Transaction transaction (database);
		Statement query1 (database, "INSERT INTO inventory (owner, name, quantity) VALUES (?, ?, 1)");
		query1.bind(1, owner);
		query1.bind(2, name);
		query1.exec();
		transaction.commit();
		
		quantity = 1;
	}
}

item::~item()
{}

double item::get_bulk() const 
{
	return data->bulk;
}

const std::string& item::get_category() const
{
	return data->category;
}

const std::string& item::get_url() const
{
	return data->url;
} 

const std::string& item::get_description() const
{
	return data->description;
}

const std::string& item::get_bulk_string() const
{
	if (data->bulk > 0 && data->bulk < 1)
	{
		bulk_string = "L";
	}
	else 
	{
		bulk_string = std::to_string(static_cast<int>(data->bulk));
	}

	return bulk_string;
}

void item::update_quantity(int delta)
{
	inventory_entry::update_quantity(delta);

	if (quantity > 0)
	{	
		Transaction transaction(database);
		
		Statement query(database, "UPDATE inventory SET quantity = ? WHERE owner = ? AND name = ?");
		query.bind(1, quantity);
		query.bind(2, owner);
		query.bind(3, name);
		query.exec(); 	

		transaction.commit();
	}
	else  
	{
		//Quantity reached 0, remove this item
		remove();
	}
}

void item::remove()
{
	Transaction transaction(database);	
	Statement query(database, "DELETE FROM inventory WHERE owner = ? AND name = ?");
	query.bind(1, owner);
	query.bind(2, name);
	query.exec(); 
	transaction.commit();	
}

void item::set_url(const string& url)
{
	auto& item_db = item_database::get_instance();
	item_db.update_url(name, url);
}

void item::set_bulk(const string& bulk)
{
	auto& item_db = item_database::get_instance();
	item_db.update_bulk(name, bulk);
}

void item::set_category(const string& category)
{
	auto& item_db = item_database::get_instance();
	item_db.update_category(name, category);
}

void item::set_description(const std::string& description)
{
	auto& item_db = item_database::get_instance();
	item_db.update_description(name, description);
}

bool item::is_valid()
{
	return !data->deleted;
}