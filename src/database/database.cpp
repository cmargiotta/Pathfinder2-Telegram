#include "database.hpp"

using std::string;
using std::unique_ptr;
using std::make_unique;
using SQLite::Database;
using SQLite::Transaction;
using SQLite::Statement;

unique_ptr<Database> pathfinder2::init_database(const string& path)
{
	auto db = make_unique<Database>(path, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);

	Transaction transaction(*db);
	db->exec("CREATE TABLE IF NOT EXISTS 'inventory' ( \
		'owner'		INT NOT NULL, \
		'name'		TEXT NOT NULL, \
		'quantity'	INT NOT NULL, \
		FOREIGN KEY('owner') REFERENCES 'character'('id'), \
		FOREIGN KEY('name') REFERENCES 'items'('name') \
	);");
	db->exec("CREATE VIRTUAL TABLE IF NOT EXISTS items USING FTS5(url, name, bulk, description, category);");
	db->exec("CREATE TABLE IF NOT EXISTS 'character' ( \
		'id'		INT NOT NULL, \
		'capacity'	INT NOT NULL, \
		'context'	TEXT, \
		'cp'		INT NOT NULL, \
		'data'		TEXT, \
		PRIMARY KEY('id') \
	);");
	db->exec("CREATE TABLE IF NOT EXISTS 'custom_items' ( \
		'owner'		INT NOT NULL, \
		'name'		TEXT NOT NULL, \
		'bulk'		REAL NOT NULL, \
		'quantity'	INT NOT NULL, \
		'category'	TEXT, \
		PRIMARY KEY('name','owner'), \
		FOREIGN KEY('owner') REFERENCES 'character'('id') \
	);");
	transaction.commit();

	return db;
}