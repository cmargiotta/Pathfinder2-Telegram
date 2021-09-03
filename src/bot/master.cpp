#include "master.hpp"

#include <iostream>
#include <exception>

using pathfinder2::master;

master::master(SQLite::Database& _database, TgBot::Bot& _bot):
	bot(_bot),
	database(_database)
{
	load_id();
}

void master::load_id()
{
	if (id_set)
	{
		return;
	}

	try
	{
		id = database.execAndGet("SELECT id FROM master");
		id_set = true;
	}
	catch(...)
	{
		std::cout << "Warning, master not in database.\n";
		id_set = false;
	}
}

master& master::get_instance(SQLite::Database* database, TgBot::Bot* bot)
{
	static bool init = false;

	if (!init && !bot)
	{
		throw std::runtime_error("No master registered");
	}

	static master instance (*database, *bot);
	init = true;

	return instance;
}

int master::get_id()
{
	load_id();

	if (id_set)
	{
		return id;
	}
	else
	{
		throw std::runtime_error("No master registered");
	}
}

void master::send_message(const std::string& message)
{
	bot.getApi().sendMessage(get_id(), message);
}

bool master::is_master(int id)
{
	if (!id_set)
	{
		return false;
	}

	return id == this->id;
}

void master::set_id(int _id)
{
	id = _id;
	id_set = true;

	SQLite::Transaction transaction (database);
	SQLite::Statement query (database, "INSERT INTO master (id) VALUES (?)");
	query.bind(1, id);
	query.exec();
	transaction.commit();
}