#include "custom_item.hpp"

#include <stdlib.h>

using std::string;
using SQLite::Database;
using SQLite::Statement;
using SQLite::Transaction;
using pathfinder2::custom_item;

custom_item::custom_item(int _owner, const string& _name, Database& _database):
	database(_database)
{
	Statement query(database, "SELECT quantity, bulk, category FROM custom_items WHERE owner = ? AND name = ?");
	query.bind(1, _owner);
	query.bind(2, _name);

	while (query.executeStep())
	{
		quantity = query.getColumn(0);
		double bulk = query.getColumn(1);

		if (bulk > 0 && bulk < 1)
		{
			set_bulk("L");
		}
		else 
		{
			set_bulk(std::to_string(static_cast<int>(bulk)));
		}

		category = string(query.getColumn(2));
		
		break;
	}

	name = _name;
	owner = _owner;
}

custom_item::custom_item(	int _owner, 
							const string& _name, 
							const string& _category,
							const string& _bulk,
							Database& _database):
	database(_database)
{
	owner = _owner;
	quantity = 1;
	name = _name;
	category = _category;
	
	inventory_entry::set_bulk(_bulk);

	Transaction transaction(database);
	Statement query (database, "INSERT INTO custom_items (owner, name, category, bulk, quantity) VALUES (?, ?, ?, ?, 1)");
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

	if (quantity > 0)
	{	
		Transaction transaction(database);

		Statement query(database, "UPDATE custom_items SET quantity = ? WHERE owner = ? AND name = ?");
		query.bind(1, quantity);
		query.bind(2, owner);
		query.bind(3, name);
		query.exec();

		transaction.commit();
	}
}

void custom_item::set_bulk(const string& _bulk)
{
	inventory_entry::set_bulk(_bulk);

	Transaction transaction(database);
	Statement query(database, "UPDATE custom_items SET bulk = ? WHERE owner = ? AND name = ?");

	query.bind(1, bulk);
	query.bind(2, owner);
	query.bind(3, name);

	query.exec();
	transaction.commit();
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

void custom_item::remove()
{
	Transaction transaction(database);
	Statement query(database, "DELETE FROM custom_items WHERE owner = ? AND name = ?");

	query.bind(1, owner);
	query.bind(2, name);

	query.exec();
	transaction.commit();

	quantity = 0;
}