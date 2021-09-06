test_main = static_library('test_main', sources: ['catch_main.cpp'], dependencies: [catch2])

inventory_test = executable('inventory_test', 'inventory.cpp', link_with: [test_main], dependencies: [sqlitecpp, database, inventory, catch2])
test('Inventory manager test', inventory_test)