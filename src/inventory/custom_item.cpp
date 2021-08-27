#include "custom_item.hpp"

#include <stdlib.h>

using std::string;
using SQLite::Database;
using SQLite::Statement;
using SQLite::Transaction;
using pathfinder2::custom_item;

custom_item::custom_item(const string& _owner, const string& _name, Database& _database):
	database(_database)
{
	Statement query(database, "SELECT quantity, bulk, category FROM custom_items WHERE owner = ? AND name = ?");
	query.bind(1, _owner);
	query.bind(2, _name);

	while (query.executeStep())
	{
		quantity = query.getColumn(0);
		category = string(query.getColumn(2));

		auto bulk_str = query.getColumn(1);
		bulk = bulk_str[0] == 'L' ? 0.1f : atoi(bulk_str);

		break;
	}

	name = _name;
	owner = _owner;
}

custom_item::custom_item(	const string& _owner, 
							const string& _name, 
							const string& _category,
							const string& _bulk,
							Database& _database):
	database(_database)
{
	quantity = 1;
	name = _name;
	category = _category;
	bulk = _bulk[0] == 'L' ? 0.1f : atoi(_bulk.c_str());

	Transaction transaction(database);
	Statement query (database, "INSERT INTO custom_items (owner, name, category, bulk) VALUES (?, ?, ?, ?)");
	query.bind(1, owner);
	query.bind(2, name);
	query.bind(3, category);
	query.bind(4, bulk);

	query.exec();
	transaction.commit();
}

custom_item::~custom_item()
{}

void custom_item::update_quantity(int delta)
{
	inventory_entry::update_quantity(delta);

	Transaction transaction(database);

	if (quantity > 0)
	{	
		Statement query(database, "UPDATE custom_items SET quantity = ? WHERE owner = ? AND name = ?");
		query.bind(1, quantity);
		query.bind(2, owner);
		query.bind(3, name);
		query.exec(); 	
	}
	else  
	{
		//Quantity reached 0, remove this item
		Statement query(database, "DELETE FROM custom_items WHERE owner = ? AND name = ?");
		query.bind(1, owner);
		query.bind(2, name);
		query.exec(); 	
	}

	transaction.commit();
}

void custom_item::set_bulk(const string& bulk)
{
	Transaction transaction(database);
	Statement query(database, "UPDATE custom_items SET bulk = ? WHERE owner = ? AND name = ?");

	query.bind(1, bulk);
	query.bind(2, owner);
	query.bind(3, name);

	query.exec();
	transaction.commit();

	inventory_entry::set_bulk(bulk);
}

void custom_item::set_category(const string& category)
{
	Transaction transaction(database);
	Statement query(database, "UPDATE custom_items SET category = ? WHERE owner = ? AND name = ?");

	query.bind(1, category);
	query.bind(2, owner);
	query.bind(3, name);

	query.exec();
	transaction.commit();

	inventory_entry::set_category(category);
}