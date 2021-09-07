#include <stdlib.h>

#include "database/database.hpp"
#include "inventory/item_database.hpp"
#include "bot/bot.hpp"

using namespace pathfinder2;
using std::string;

int main()
{
	auto& db = init_database(getenv("PF2_INV_DB_PATH"));
	item_database::get_instance(&db);
	
	bot b (db);

	return 0;
}