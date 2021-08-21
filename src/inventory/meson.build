inventory_lib = library('inventory',
						[
							'inventory_entry.cpp',
							'item_database.cpp',
							'item.cpp'
						],
						dependencies: [sqlitecpp, cache])

inventory = declare_dependency(link_with: inventory_lib)