#include "callback_commands.hpp"

const std::unordered_map<char, std::function<void(TgBot::Bot&, TgBot::CallbackQuery::Ptr, SQLite::Database&)>> pathfinder2::callback_commands = {
    {'+', add},
    {'-', remove},
};