#include "inventory.hpp"

#include <algorithm>

#include "item.hpp"
#include "custom_item.hpp"

using std::string;
using std::shared_ptr;
using std::make_shared;
using SQLite::Database;
using SQLite::Statement;
using pathfinder2::item;
using SQLite::Transaction;
using pathfinder2::inventory;

inventory::inventory(const string& _owner, Database& _database):
	owner(_owner),
	database(_database)
{
	Statement query (database, "SELECT name FROM FROM inventory WHERE owner = ?");
	query.bind(1, owner);

	while (query.executeStep())
	{
		string name = query.getColumn(0);
		auto _item = make_shared<item>(owner, name, database);
		
		content_category[_item->get_category()].push_back(_item);
		content_name[_item->get_name()] = _item;
	}

	Statement query1 (database, "SELECT name FROM custom_items WHERE owner = ?");
	query1.bind(1, owner);

	while (query1.executeStep())
	{
		string name = query.getColumn(0);
		auto _item = make_shared<custom_item>(owner, name, database);

		content_category[_item->get_category()].push_back(_item);
		content_name[_item->get_name()] = _item;
	}
}

void inventory::add_item(const string& name)
{
	if (content_name.count(name) != 0)
	{
		//Item already in inventory
		content_name[name]->update_quantity(1);
	}
	else
	{
		try
		{
			//Try to add an item from database
			auto _item = make_shared<item>(owner, name, database);
			content_category[_item->get_category()].push_back(_item);
			content_name[_item->get_name()] = _item;
		}
		catch(...)
		{
			//Item not in database, error
			throw std::runtime_error("Item name not registered.");
		}
	}
}

void inventory::add_item(const string& name, const string& bulk, const string& category)
{
	//Try to add it in other ways
	try
	{
		add_item(name);
	}	
	catch (...)
	{
		//This is a new custom_item
		auto _item = make_shared<custom_item>(owner, name, bulk, category, database);
		content_category[_item->get_category()].push_back(_item);
		content_name[_item->get_name()] = _item;
	}
}

void inventory::remove_item(const string& name)
{
	if (content_name.count(name) != 0)
	{
		auto _item = content_name[name];
		_item->update_quantity(-1);

		if (_item->get_quantity() == 0)
		{
			//Quantity reached 0, remove this item from inventory
			content_name.erase(name);

			auto& category_list = content_category[_item->get_category()];
			std::remove(category_list.begin(), category_list.end(), _item);
		}
	}
}