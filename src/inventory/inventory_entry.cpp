#include "inventory_entry.hpp"

#include <cstdlib>
#include <algorithm>
#include <stdexcept>
#include <common/string_utils.hpp>

using std::string;
using pathfinder2::inventory_entry;

inventory_entry::inventory_entry(int _owner, const std::string& _name, double _bulk, const std::string& _category):
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

double inventory_entry::get_bulk() const
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

void inventory_entry::set_category(const string& category) 
{
	this->category = category;
}

void inventory_entry::set_bulk(const string& bulk) 
{
	bulk_string = bulk;
	this->bulk = common::parse_bulk(bulk); 
}

void inventory_entry::set_bulk(double _bulk) const
{
	if (_bulk < 0)
	{
		throw std::runtime_error("bulk_error");
	}

	bulk = _bulk;
	bulk_string = common::bulk_to_string(bulk); 
}

void inventory_entry::set_description(const string& description) 
{}

void inventory_entry::set_url(const string& url) 
{}

void inventory_entry::set_image(const string& image)
{}

bool inventory_entry::is_valid() const
{
	return true;
}

const std::string& inventory_entry::get_bulk_string() const
{
	return bulk_string;
}

const std::string& inventory_entry::get_image() const 
{
	static std::string stub;
	return stub;
}