#ifndef HTTPS_SERVER_HPP_
#define HTTPS_SERVER_HPP_

#define CPPHTTPLIB_OPENSSL_SUPPORT

#include <tgbot/tgbot.h>

#include "../../subprojects/cpp-httplib/httplib.h"

namespace pathfinder2
{
	class https_server
	{
		private: 
			httplib::SSLServer server;
			int port;

		public: 
			https_server(int port, const TgBot::EventHandler& handler);

			void start();
	};
}

#endif // HTTPS_SERVER_HPP_