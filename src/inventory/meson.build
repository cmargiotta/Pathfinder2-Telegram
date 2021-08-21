inventory_lib = library('inventory',
						[
							'item_manager.cpp'
						],
						dependencies: [sqlitecpp, cache])

inventory = declare_dependency(link_with: inventory_lib)