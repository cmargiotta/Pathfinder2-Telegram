#ifndef BOT_HPP_
#define BOT_HPP_

#include <tgbot/tgbot.h>
#include <nlohmann/json.hpp>
#include <SQLiteCpp/SQLiteCpp.h>

namespace pathfinder2
{
	class bot
	{
		private:
			TgBot::Bot _bot;
			nlohmann::json messages;
			SQLite::Database& database;

		public:
			bot(SQLite::Database& database);
			~bot() = default;
	};
}
#endif // BOT_HPP_