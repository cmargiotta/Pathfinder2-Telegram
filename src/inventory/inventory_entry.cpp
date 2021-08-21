#include "inventory_entry.hpp"

using std::string;
using pathfinder2::inventory_entry;

inventory_entry::inventory_entry(const string& _owner, const std::string& _name, float _bulk, const std::string& _category):
	owner(_owner.c_str()),
	name(_name),
	category(_category),
	bulk(_bulk)
{
	quantity = 0;
}

inventory_entry::inventory_entry(const char* _owner, const char* _name, float _bulk, const char* _category):
	owner(_owner),
	name(_name),
	category(_category),
	bulk(_bulk)
{
	quantity = 0;
}

inventory_entry::~inventory_entry()
{}

const std::string& inventory_entry::get_name() const
{
	return name; 
}

const std::string& inventory_entry::get_category() const
{
	return category;
}

float inventory_entry::get_bulk() const
{
	return bulk;
}

int inventory_entry::get_quantity() const
{
	return quantity; 
}

void inventory_entry::update_quantity(int delta)
{
	if (abs(delta) > quantity)
	{
		quantity = 0;
	}
	else  
	{
		quantity += delta;
	}
}

const std::string& inventory_entry::get_url() const
{
	static const string url ("");
	return url;
}

const std::string& inventory_entry::get_description() const
{
	static const string description ("");
	return description;
}