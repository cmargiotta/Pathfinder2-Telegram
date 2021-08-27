database_lib = library(	'database',
						[
							'database.cpp',
						],
						dependencies: [sqlitecpp])

database = declare_dependency(link_with: database_lib, include_directories: ['..'])