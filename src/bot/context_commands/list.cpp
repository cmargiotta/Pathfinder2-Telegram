#include "context_commands.hpp"

#include <string>
#include <exception>

#include "../master.hpp"
#include "../keyboards.hpp"
#include "../local_data.hpp"
#include "common/string_utils.hpp"
#include "character/character_cache.hpp"

std::string progress_bar(float progress)
{
    std::string bar ("");

    int bar_width = 25;
    int pos = bar_width * progress;

    for (int i = 0; i < bar_width; ++i) 
    {
        if (i < pos) 
        {
            bar += "█";
        }
        else 
        {
            bar += "▒";
        }
    }

    return bar;
}

void pathfinder2::list_(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database)
{
	static auto& messages = pathfinder2::get_messages(message->from->languageCode);
    static auto& buttons = pathfinder2::get_commands(message->from->languageCode);

    const auto& text = message->text;
	auto id = message->chat->id;
	auto character_ = pathfinder2::character_cache[id];

    if (text == buttons["list_brief"])
    {
        std::stringstream message_text; 

        float occupied = character_->get_inventory().get_occupied_bulk();
        auto capacity = character_->get_capacity();
        message_text << static_cast<int>(occupied) << '/' << capacity << '\n';
        message_text << "```" << progress_bar(occupied/capacity) << "```\n\n";

        for (auto& category: character_->get_inventory().get_categorised_items())
        {
			message_text << '*' << ((category.first != "") ? category.first : std::string(messages["default_category"])) << "*:\n";
			
            for (std::shared_ptr<inventory_entry> item: category.second)
            {
				if (item)
				{
					message_text << "   " << common::escape(item->get_name(), common::to_escape, '\\') << ", bulk: " << item->get_bulk_string();

					if (item->get_quantity() > 1)
					{
						message_text << " \\(" << item->get_quantity() << "\\)";
					}

					message_text << '\n';
				}
            }
            
        }

        character_->set_context("");
        bot.getApi().sendMessage(id, message_text.str(), false, 0, pathfinder2::remove_keyboard, "MarkdownV2");
	    bot.getApi().sendMessage(id, messages["default_message"], false, 0, pathfinder2::get_default_keyboard(message->from->languageCode, master::get_instance().is_master(id)));
    }
    else if (text == buttons["list_detail"])
    {
        auto keyboard = pathfinder2::create_keyboard({});

        for (auto& item: character_->get_inventory().get_item_list())
        {
            pathfinder2::add_button_row(keyboard, item);
        }

        pathfinder2::add_button_row(keyboard, buttons["cancel"]);

        character_->set_context(messages["list_detail_selection"]);
        bot.getApi().sendMessage(id, character_->get_context(), false, 0, keyboard);
    }
    else
    {
        throw std::runtime_error("selection_error");
    }	
}
