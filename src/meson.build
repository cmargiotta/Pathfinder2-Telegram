subdir('common')
subdir('database')
subdir('inventory')
subdir('character')
subdir('bot')

executable('inventory_bot', dependencies: [sqlitecpp, character, database, inventory, tgbot, json, bot], sources: ['main.cpp'], install: true, install_dir: '/usr/bin/')
