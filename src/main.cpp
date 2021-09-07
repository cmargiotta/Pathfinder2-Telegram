#include <stdlib.h>

#include "database/database.hpp"
#include "inventory/item_database.hpp"
#include "bot/bot.hpp"

using namespace pathfinder2;
using std::string;

int main()
{
	char* db_path = getenv("PF2_INV_DB_PATH");

	if (db_path == nullptr)
	{
		db_path = "./pf2_inv.db";
	}

	auto& db = init_database(db_path);
	item_database::get_instance(&db);
	
	bot b (db);

	return 0;
}