project('pathfinder2-telegram', 'cpp', default_options : ['cpp_std=c++17'])

cmake = import('cmake')
cpp = meson.get_compiler('cpp')

# External dependencies
dl = cpp.find_library('dl', required : true)
threads = dependency('threads')
sqlitecpp = declare_dependency(
	dependencies: [
		dl,
		threads,
		cmake.subproject('sqlitecpp').dependency('SQLiteCpp'),
		cmake.subproject('sqlitecpp').dependency('sqlite3')
	]
)


subdir('src')
