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
	bool found = false;

	Statement query (database, "SELECT cp, capacity, context, data, username FROM character WHERE id = ?");
	query.bind(1, id);

	while (query.executeStep())
	{
		found = true;
		cp = query.getColumn(0);
		capacity = query.getColumn(1);
		context = string(query.getColumn(2));
		data = string(query.getColumn(3));
		username = string(query.getColumn(4));

		break;
	}

	if (!found)
	{
		//New character
		Transaction transaction (database);
		Statement query1 (database, "INSERT INTO character (id, cp, capacity, context, data) VALUES (?, 0, 0, '', '')");
		query1.bind(1, id);
		query1.exec();
		transaction.commit();
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

const std::string& character::get_username()
{
	return username;
}

const string& character::get_data()
{
	return data;
}

void character::update_cp(int delta)
{
	if (abs(delta) > cp && delta < 0)
	{
		throw std::runtime_error("no_money_error");
	}

	cp += delta;

	Transaction transaction (database);

	Statement query (database, "UPDATE character SET cp = ? WHERE id = ?");
	query.bind(1, cp);
	query.bind(2, id);
	query.exec();

	transaction.commit();
}

void character::set_username(const std::string& _username)
{
	this->username = _username;

	Transaction transaction (database);

	Statement query (database, "UPDATE character SET username = ? WHERE id = ?");
	query.bind(1, username);
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

const std::set<int> character::get_characters_ids(SQLite::Database& database)
{
	std::set<int> ids;
	Statement query (database, "SELECT id FROM character");

	while (query.executeStep())
	{
		ids.insert(query.getColumn(0));
	}

	return ids;
}