#ifndef MASTER_HPP_
#define MASTER_HPP_

#include <string>
#include <tgbot/tgbot.h>

namespace pathfinder2
{
	class master
	{
		private:
			int id;
			TgBot::Bot& bot;

			master(int id, TgBot::Bot& bot);
		public: 
			static master& get_instance(int id = 0, TgBot::Bot* bot = nullptr);
			~master() = default;

			void send_message(const std::string& message);
			int get_id(); 
	};
}
#endif // MASTER_HPP_