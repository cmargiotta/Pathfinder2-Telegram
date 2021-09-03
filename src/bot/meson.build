bot_lib = static_library(	'bot',
					[
						'bot.cpp',
						'master.cpp',
						'keyboards.cpp',
						'local_data.cpp',
						'message_handler.cpp',
						'callback_handler.cpp',
						
						'commands/commands.cpp',
						'commands/add.cpp',
						'commands/start.cpp',
						'commands/reset.cpp',
						'commands/remove.cpp',
						'commands/list.cpp',
						'commands/set_capacity.cpp',
						'commands/money_transaction.cpp',
						'commands/get_money.cpp',
						'commands/register_item_master.cpp',
						'commands/edit_item_master.cpp',
						'commands/delete_item_master.cpp',

						'context_commands/context_commands.cpp',
						'context_commands/add.cpp',
						'context_commands/list.cpp',
						'context_commands/remove.cpp',
						'context_commands/add_item.cpp',
						'context_commands/list_detail.cpp',
						'context_commands/set_capacity.cpp',
						'context_commands/edit_selection.cpp',
						'context_commands/add_custom_item.cpp',
						'context_commands/edit_item_master.cpp',
						'context_commands/money_transaction.cpp',
						'context_commands/edit_value_request.cpp',
						'context_commands/delete_item_master.cpp',
						'context_commands/register_item_master.cpp',

						'callback_commands/callback_commands.cpp',
						'callback_commands/add.cpp',
						'callback_commands/remove.cpp'
					],
					dependencies: [tgbot, json, sqlitecpp, character, cache, inventory, string_utils])

bot = declare_dependency(link_with: bot_lib, include_directories: ['..'])