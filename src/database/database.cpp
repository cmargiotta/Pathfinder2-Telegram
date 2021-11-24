#include "database.hpp"

#include <exception>

using std::string;
using SQLite::Database;
using SQLite::Transaction;

Database& pathfinder2::init_database(const string& path)
{
	static bool initialised = false;

	if (!initialised && path == "")
	{
		throw std::runtime_error("Cannot init a database without a path.");
	}

	static Database db (path, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);

	if (!initialised)
	{
		Transaction transaction(db);

		db.exec("CREATE TABLE IF NOT EXISTS 'inventory' ( \
			'owner'		INT NOT NULL, \
			'name'		TEXT NOT NULL, \
			'quantity'	INT NOT NULL, \
			FOREIGN KEY('owner') REFERENCES 'character'('id'), \
			FOREIGN KEY('name') REFERENCES 'items'('name') \
		);");
		db.exec("CREATE VIRTUAL TABLE IF NOT EXISTS items USING FTS5(url, name, bulk, description, category);");
		db.exec("CREATE TABLE IF NOT EXISTS 'item_data' ( \
			'name'		TEXT NOT NULL, \
			'image'		BLOB, \
			PRIMARY KEY('name') \
		);");
		db.exec("CREATE TABLE IF NOT EXISTS 'character' ( \
			'id'		INT NOT NULL, \
			'capacity'	INT NOT NULL, \
			'context'	TEXT, \
			'cp'		INT NOT NULL, \
			'data'		TEXT, \
			PRIMARY KEY('id') \
		);");
		db.exec("CREATE TABLE IF NOT EXISTS 'custom_items' ( \
			'owner'		INT NOT NULL, \
			'name'		TEXT NOT NULL, \
			'bulk'		REAL NOT NULL, \
			'quantity'	INT NOT NULL, \
			'category'	TEXT, \
			PRIMARY KEY('name','owner'), \
			FOREIGN KEY('owner') REFERENCES 'character'('id') \
		);");
		db.exec("CREATE TABLE IF NOT EXISTS 'master' (\
			'id' INT NOT NULL, \
			PRIMARY KEY('id') \
		);");
		db.exec("CREATE TABLE IF NOT EXISTS 'settings' (\
			'coin_bulk' DOUBLE \
		);");

		db.exec("CREATE INDEX IF NOT EXISTS 'inventory_owner' ON 'inventory' ( \
			'owner' \
		);");
		db.exec("CREATE INDEX IF NOT EXISTS 'custom_items_owner' ON 'custom_items' ( \
			'owner' \
		);");

		//Ensuring only one row in settings
		db.exec("CREATE TRIGGER IF NOT EXISTS settings_only_one_row \
				BEFORE INSERT ON settings \
				WHEN (SELECT COUNT(*) FROM settings) >= 1 \
				BEGIN \
					SELECT RAISE(FAIL, 'only one row!'); \
				END;"
		);

		//Init settings
		try
		{
			db.exec("INSERT INTO settings VALUES (0);");
		}
		catch(...)
		{
			;
		}

		//ALTER TABLE for backward compatibility
		try 
		{
			db.exec("ALTER TABLE character ADD username VARCHAR(255);");
		}
		catch(...)
		{
			;
		}

		transaction.commit();

		initialised = true;
	}
	
	return db;
}
