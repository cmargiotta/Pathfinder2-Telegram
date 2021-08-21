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
	bulk = data->bulk;
	category = data->category;
	name = _name;
	owner = _owner;
}

item::~item()
{}

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
	Statement query(database, "UPDATE inventory SET quantity = ? WHERE owner = ? AND name = ?");
	query.bind(1, quantity);
	query.bind(2, owner);
	query.bind(3, name);
	query.exec(); 
	transaction.commit();
}