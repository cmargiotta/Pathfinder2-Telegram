#include "https_server.hpp"

using pathfinder2::https_server;

https_server::https_server(int _port, const TgBot::EventHandler& handler):
	server("/usr/share/inventory_bot/certs/public.crt", "/usr/share/inventory_bot/certs/private.key"),
	port(_port)
{
	const TgBot::TgTypeParser _tgTypeParser;
	server.Post("/", [&](const httplib::Request &request, httplib::Response &res)
	{
		handler.handleUpdate(_tgTypeParser.parseJsonAndGetUpdate(_tgTypeParser.parseJson(request.body)));

		res.status = 200;
    	res.set_content("OK", "text/plain");
	});
}

void https_server::start()
{
	server.listen("localhost", port);
}