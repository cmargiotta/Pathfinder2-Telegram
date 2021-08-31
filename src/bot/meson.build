bot_lib = library(	'bot',
					[
						'bot.cpp',
						'keyboards.cpp',
						'local_data.cpp',
						'message_handler.cpp',
						
						'commands/commands.cpp',
						'commands/add.cpp',
						'commands/start.cpp',
						'commands/reset.cpp',
						'commands/remove.cpp',
						'commands/list.cpp',
						'commands/set_capacity.cpp',
						'commands/money_transaction.cpp',
						'commands/get_money.cpp',

						'context_commands/context_commands.cpp',
						'context_commands/add.cpp',
						'context_commands/list.cpp',
						'context_commands/remove.cpp',
					],
					dependencies: [tgbot, json, sqlitecpp, character, cache, inventory])

bot = declare_dependency(link_with: bot_lib, include_directories: ['..'])