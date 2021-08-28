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
					],
					dependencies: [tgbot, json, sqlitecpp, character, cache, inventory])

bot = declare_dependency(link_with: bot_lib, include_directories: ['..'])