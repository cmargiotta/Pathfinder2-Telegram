#include "catch2/catch.hpp"

#include <iostream>

#include "database/database.hpp"
#include "inventory/inventory.hpp"
#include "inventory/item_database.hpp"

using Catch::Matchers::Equals;
using Catch::Matchers::WithinRel;
using pathfinder2::item_database;

SCENARIO("Item database can be accessed and modified")
{
	GIVEN("Fully loaded database and item database")
	{
		auto& db = pathfinder2::init_database("test.db");
		auto& item_db = item_database::get_instance(&db);

		WHEN("A new item with invalid bulk is registered")
		{
			THEN("An exception is thrown")
			{
				REQUIRE_THROWS(item_db.register_new_item("test_fail", "test", "test", "test", "invalid bulk"));
			}
			AND_THEN("The item is not added to the database")
			{
				REQUIRE_THROWS(item_db.get_item("test_fail"));
			}
		}

		WHEN("A new item is registered")
		{
			THEN("No execeptions are thrown")
			{
				REQUIRE_NOTHROW(item_db.register_new_item("test", "test", "test", "test", "1"));
			}
			AND_THEN("It is possible to retrieve the item")
			{
				REQUIRE_NOTHROW(item_db.get_item("test"));
			}
			AND_THEN("Its values are correct")
			{
				auto item = item_db.get_item("test");
				REQUIRE_THAT(item->name, Equals("test"));
				REQUIRE_THAT(item->url, Equals("test"));
				REQUIRE_THAT(item->category, Equals("test"));
				REQUIRE_THAT(item->description, Equals("test"));
				REQUIRE(item->bulk == 1.0);
			}
		}

		WHEN("An item already in database is registered")
		{
			THEN("An exception is thrown")
			{
				REQUIRE_THROWS(item_db.register_new_item("test", "test", "test", "test", "1"));
			}
		}

		WHEN("An item has bulk 'L'")
		{
			THEN("Its real value bulk is 0.1")
			{
				item_db.update_bulk("test", "L");
				REQUIRE_THAT(item_db.get_item("test")->bulk, WithinRel(0.1, 0.00001));
			}
		}

		WHEN("An item is updated from the database")
		{
			THEN("Its previously obtained references are updated too")
			{
				auto item = item_db.get_item("test");
				item_db.update_bulk("test", "2");
				REQUIRE(item->bulk == 2);
			}
		}
	}
}

SCENARIO("Items can be deleted from database")
{
	auto& item_db = item_database::get_instance();

	WHEN("A non existing item is deleted from database")
	{
		THEN("An exception is thrown")
		{
			REQUIRE_THROWS(item_db.delete_item("fake_item"));
		}
	}

	WHEN("An item is deleted")
	{
		auto test_item = item_db.get_item("test");
		THEN("No exceptions are thrown and it is no more accessible")
		{
			REQUIRE_NOTHROW(item_db.delete_item("test"));
			REQUIRE_THROWS(item_db.get_item("test"));
			REQUIRE(test_item->deleted);
		}
	}
}

SCENARIO("An inventory can handle an heterogeneous set of items")
{
	auto& db = pathfinder2::init_database("test.db");
	pathfinder2::inventory inv (1, db);
	auto& item_db = item_database::get_instance(&db);

	WHEN("A custom item is added to the inventory")
	{
		THEN("No exceptions are thrown")
		{
			REQUIRE_NOTHROW(inv.add_item("custom_test", "3", "custom"));
		}
		AND_THEN("Data are correctly considered")
		{
			REQUIRE(inv.get_occupied_bulk() >= 3);
			REQUIRE(inv.get_item_list().size() == 1);
		}
	}
	
	WHEN("An item from database is added")
	{
		THEN("No exceptions are thrown")
		{
			item_db.register_new_item("test_inv", "test", "test", "test", "1");
			item_db.register_new_item("test", "test", "test", "test", "1");

			REQUIRE_NOTHROW(inv.add_item("test"));
			REQUIRE_NOTHROW(inv.add_item("test_inv"));
		}
		AND_THEN("Its fields are correctly retrieved from the database")
		{
			for (auto& item: inv.get_item_list())
				std::cout << item << std::endl;
			REQUIRE(inv.get_occupied_bulk() == 5);
		}
	}
}