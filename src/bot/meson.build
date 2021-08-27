bot_lib = library(	'bot',
					[
						'bot.cpp',
						'keyboards.cpp',
						'local_data.cpp',
						'commands/start.cpp',
						'message_handler.cpp',
						'commands/commands.cpp'
					],
					dependencies: [tgbot, json, sqlitecpp, character, cache, inventory])

bot = declare_dependency(link_with: bot_lib, include_directories: ['..'])