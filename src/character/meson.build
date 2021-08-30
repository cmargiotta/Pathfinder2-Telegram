character_lib = static_library('character',
						[
							'character.cpp',
							'character_cache.cpp'
						],
						dependencies: [inventory, sqlitecpp, database])

character = declare_dependency(link_with: character_lib, include_directories: ['..'])