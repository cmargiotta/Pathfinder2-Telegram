#include "item.hpp"

#include "item_database.hpp"

using std::string;
using SQLite::Database;
using SQLite::Statement;
using pathfinder2::item;
using SQLite::Transaction;
using pathfinder2::item_database;

item::item(const string& _owner, const string& _name, SQLite::Database& _database):
	database(_database)
{
	auto& item_db = item_database::get_instance();

	Statement query(database, "SELECT quantity FROM inventory WHERE owner = ? AND name = ?");
	query.bind(1, _owner);
	query.bind(2, _name);

	while (query.executeStep())
	{
		quantity = query.getColumn(0);
		break;
	}

	data = item_db.get_item(_name);
	name = _name;
	owner = _owner;
}

item::~item()
{}

float item::get_bulk() const 
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

void item::update_quantity(int delta)
{
	inventory_entry::update_quantity(delta);

	Transaction transaction(database);

	if (quantity > 0)
	{	
		Statement query(database, "UPDATE inventory SET quantity = ? WHERE owner = ? AND name = ?");
		query.bind(1, quantity);
		query.bind(2, owner);
		query.bind(3, name);
		query.exec(); 	
	}
	else  
	{
		//Quantity reached 0, remove this item
		Statement query(database, "DELETE FROM inventory WHERE owner = ? AND name = ?");
		query.bind(1, owner);
		query.bind(2, name);
		query.exec(); 	
	}

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