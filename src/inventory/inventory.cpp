#include "inventory.hpp"

#include <algorithm>

#include "item.hpp"
#include "custom_item.hpp"

using std::list;
using std::string;
using std::make_shared;
using SQLite::Database;
using SQLite::Statement;
using pathfinder2::item;
using pathfinder2::inventory;

inventory::inventory(int _owner, Database& _database):
	owner(_owner),
	database(_database)
{
	Statement query (database, "SELECT name FROM inventory WHERE owner = ?");
	query.bind(1, owner);
	while (query.executeStep())
	{
		string name = query.getColumn(0);
		auto _item = make_shared<item>(owner, name, database);
		
		content_category[_item->get_category()].push_back(_item);
		content_name[_item->get_name()] = _item;
		item_names.push_back(_item->get_name());
	}

	Statement query1 (database, "SELECT name FROM custom_items WHERE owner = ?");
	query1.bind(1, owner);

	while (query1.executeStep())
	{
		string name = query1.getColumn(0);
		auto _item = make_shared<custom_item>(owner, name, database);

		content_category[_item->get_category()].push_back(_item);
		content_name[_item->get_name()] = _item;
		item_names.push_back(_item->get_name());
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
			item_names.push_back(_item->get_name());
		}
		catch(...)
		{
			//Item not in database, error
			throw std::runtime_error("item_not_found");
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
		auto _item = make_shared<custom_item>(owner, name, category, bulk, database);
		content_category[_item->get_category()].push_back(_item);
		content_name[_item->get_name()] = _item;
		item_names.push_back(_item->get_name());
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
			std::remove(item_names.begin(), item_names.end(), _item->get_name());
			std::remove(category_list.begin(), category_list.end(), _item);
		}
	}
}

double inventory::get_occupied_bulk()
{
	double b = 0.0;

	for (auto& i: content_name)
	{
		b += i.second->get_bulk();
	}

	return b;
}

void inventory::reset()
{
	for (auto& i: content_name)
	{
		i.second->remove();
	}

	content_category.clear();
	content_name.clear();
}

const list<string>& inventory::get_item_list()
{
	return item_names;
}

const decltype(inventory::content_category)& inventory::get_categorised_items()
{
	return content_category;
}