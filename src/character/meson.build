character_lib = library('character',
						[
							'character.cpp',
						],
						dependencies: [inventory, sqlitecpp])

character = declare_dependency(link_with: character_lib, include_directories: ['..'])