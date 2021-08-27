inventory_lib = library('inventory',
						[
							'custom_item.cpp',
							'inventory_entry.cpp',
							'item_database.cpp',
							'item.cpp',
							'inventory.cpp'
						],
						dependencies: [sqlitecpp, cache])

inventory = declare_dependency(link_with: inventory_lib, include_directories: ['..'])