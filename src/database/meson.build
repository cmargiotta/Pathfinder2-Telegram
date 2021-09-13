database_lib = static_library(	'database',
								[
									'database.cpp',
								],
								dependencies: [sqlitecpp])

database = declare_dependency(link_with: database_lib, include_directories: ['..'])