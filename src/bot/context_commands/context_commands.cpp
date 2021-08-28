#include "context_commands.hpp"

const std::unordered_map<std::string, std::function<void(TgBot::Bot&, TgBot::Message::Ptr, SQLite::Database&)>> pathfinder2::context_commands = {
    {"add_response", add_}
};