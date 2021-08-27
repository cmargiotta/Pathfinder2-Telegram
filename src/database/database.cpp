#include "database.hpp"

using std::string;
using std::unique_ptr;
using std::make_unique;
using SQLite::Database;
using SQLite::Transaction;
using SQLite::Statement;

unique_ptr<Database> pathfinder2::init_database(const string& path)
{
	auto db = make_unique<Database>(path);
	Transaction transaction(*db);

	Statement query (*db, "CREATE TABLE IF NOT EXISTS 'inventory' ( \
		'owner'		INT NOT NULL, \
		'name'		TEXT NOT NULL, \
		'quantity'	INT NOT NULL, \
		'category'	TEXT, \
		FOREIGN KEY('owner') REFERENCES 'character'('id'), \
		FOREIGN KEY('name') REFERENCES 'items'('name') \
	); \
	CREATE VIRTUAL TABLE IF NOT EXISTS items USING FTS5(url, name, bulk, description); \
	CREATE TABLE IF NOT EXISTS 'character' ( \
		'id'		INT NOT NULL, \
		'capacity'	INT NOT NULL, \
		'context'	TEXT, \
		'cp'		INT NOT NULL, \
		'data'		TEXT, \
		PRIMARY KEY('id') \
	); \
	CREATE TABLE IF NOT EXISTS 'custom_items' ( \
		'owner'		INT NOT NULL, \
		'name'		TEXT NOT NULL, \
		'bulk'		REAL NOT NULL, \
		'quantity'	INT NOT NULL, \
		'category'	TEXT, \
		PRIMARY KEY('name','owner'), \
		FOREIGN KEY('owner') REFERENCES 'character'('id') \
	);");
	query.exec();

	transaction.commit();
	return db;
}