#include "item.hpp"

using std::string;
using pathfinder2::item;

item::item(const string& name, const string& url, const string& description, float bulk) noexcept
{
    this->url = url;
    this->name = name;
    this->description = description;

    this->bulk = bulk;
}

const string& item::get_url() const noexcept
{
    return url; 
}

const string& item::get_name() const noexcept
{
    return name; 
}

const string& item::get_description() const noexcept
{
    return description; 
}

const float& item::get_bulk() const noexcept
{
    return bulk; 
}