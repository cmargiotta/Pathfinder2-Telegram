#ifndef MASTER_HPP_
#define MASTER_HPP_

#include <string>
#include <tgbot/tgbot.h>
#include <SQLiteCpp/SQLiteCpp.h>

namespace pathfinder2
{
	class master
	{
		private:
			int id;
			bool id_set;
			TgBot::Bot& bot;
			SQLite::Database& database;

			master(SQLite::Database& database, TgBot::Bot& bot);
		public: 
			static master& get_instance(SQLite::Database* database = nullptr, TgBot::Bot* bot = nullptr);
			~master() = default;

			void send_message(const std::string& message);
			int get_id(); 

			void load_id();

			void set_id(int id);
	};
}
#endif // MASTER_HPP_