#include "database/database.hpp"
#include "inventory/item_database.hpp"
#include "bot/bot.hpp"

using namespace pathfinder2;
using std::string;

int main()
{
	auto& db = init_database("test.db");
	item_database::get_instance(&db);
	
	bot b (db);

	return 0;
}