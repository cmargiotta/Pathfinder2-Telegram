#include "character.hpp"

#include <exception>

using std::string;
using SQLite::Database;
using SQLite::Statement;
using SQLite::Transaction;
using pathfinder2::character;
using pathfinder2::inventory;

character::character(int _id, Database& _database):
	id(_id),
	database(_database),
	_inventory(_id, _database)
{
	Statement query (database, "SELECT cp, capacity, context, data FROM character WHERE id = ?");
	query.bind(1, id);

	while (query.executeStep())
	{
		cp = query.getColumn(0);
		capacity = query.getColumn(1);
		context = string(query.getColumn(2));
		data = string(query.getColumn(3));

		break;
	}
}

inventory& character::get_inventory()
{
	return _inventory;
}

int character::get_cp()
{
	return cp;
}

int character::get_id()
{
	return id;
}

int character::get_capacity()
{
	return capacity;
}

const string& character::get_context()
{
	return context;
}

const string& character::get_data()
{
	return data;
}

void character::update_cp(int delta)
{
	if (delta > cp)
	{
		throw std::runtime_error("Cannot have negative money.");
	}

	cp += delta;

	Transaction transaction (database);

	Statement query (database, "UPDATE character SET cp = ? WHERE id = ?");
	query.bind(1, cp);
	query.bind(2, id);
	query.exec();

	transaction.commit();
}

void character::set_capacity(int capacity)
{
	this->capacity = capacity;

	Transaction transaction (database);
	
	Statement query (database, "UPDATE character SET capacity = ? WHERE id = ?");
	query.bind(1, capacity);
	query.bind(2, id);
	query.exec();

	transaction.commit();
}

void character::set_context(const string& context)
{
	this->context = context;

	Transaction transaction (database);
	
	Statement query (database, "UPDATE character SET context = ? WHERE id = ?");
	query.bind(1, context);
	query.bind(2, id);
	query.exec();

	transaction.commit();
}

void character::set_data(const string& data)
{
	this->data = data;

	Transaction transaction (database);
	
	Statement query (database, "UPDATE character SET data = ? WHERE id = ?");
	query.bind(1, data);
	query.bind(2, id);
	query.exec();

	transaction.commit();
}