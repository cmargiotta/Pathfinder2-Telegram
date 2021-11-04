dice_parser_lib = static_library('dice_parser',
						[
							'node.cpp',

							'operators/sum_node.cpp',
							'operators/dice_node.cpp',
							'operators/leaf_node.cpp'
						],
						dependencies: [string_utils])

dice_parser = declare_dependency(link_with: dice_parser_lib, include_directories: ['..'])