#include "settings.hpp"

using SQLite::Statement;
using SQLite::Transaction;
using pathfinder2::settings;

settings& settings::get_instance(SQLite::Database* _database)
{
	static settings* instance = nullptr; 
	static bool initialised = false; 

	if (!initialised)
	{
		if (!_database)
		{
			throw std::runtime_error("Cannot init without database"); 
		}
		
		initialised = true; 
		instance = new settings(*_database);
	}

	return *instance; 
}

settings::settings(SQLite::Database& _database):
	database{_database}
{
	Statement query(database, "SELECT coin_bulk FROM settings");

	while (query.executeStep())
	{
		coin_bulk = query.getColumn(0);
		break;
	}
}

double settings::get_coin_bulk() const
{
	return coin_bulk;
}

void settings::set_coin_bulk(double bulk)
{
	coin_bulk = bulk;
	Transaction transaction(database);
	Statement query(database, "UPDATE settings SET coin_bulk = ?");

	query.bind(1, coin_bulk);

	query.exec();
	transaction.commit();
}