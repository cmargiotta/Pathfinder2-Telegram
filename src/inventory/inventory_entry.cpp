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
	if (bulk_string.back() == 'l')
	{
		bulk_string.back() = 'L';
	}

	if (bulk_string.empty() || 
		bulk_string[0] == '-' ||
		!(common::is_number(bulk_string) || (bulk_string.back() == 'L' && (
											common::is_number(bulk_string.substr(0, bulk_string.size() - 1)) ||
											bulk_string.size() == 1))))
	{
		throw std::runtime_error("bulk_error");
	}

	if (bulk_string == "1L")
	{
		bulk_string = "L";
	}

	if (bulk_string.back() == 'L')
	{
		if (bulk_string.size() == 1)
		{
			this->bulk = 0.1;
		}
		else 
		{
			bulk_string.back() = '\0';

			this->bulk = 0.1 * atoi(bulk_string.c_str());
			bulk_string.back() = 'L';
		}
	}
	else 
	{
		this->bulk = static_cast<double>(atoi(bulk_string.c_str()));
	}
}

void inventory_entry::set_bulk(double _bulk) const
{
	if (_bulk < 0)
	{
		throw std::runtime_error("bulk_error");
	}

	bulk = _bulk;

	if (bulk - static_cast<long>(bulk) >= 0.1)
	{
		bulk_string = std::to_string(static_cast<int>(bulk*10));
		bulk_string += "L";

		if (bulk_string == "1L")
		{
			bulk_string = "L";
		}
		else if (bulk_string == "0L")
		{
			bulk_string = "0";
		}
	}
	else 
	{
		bulk_string = std::to_string(static_cast<int>(bulk));
	}
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