project('pathfinder2-telegram', 'cpp', default_options : ['cpp_std=c++17'])

cmake = import('cmake')
cpp = meson.get_compiler('cpp')

# Subproject options
sqlitecpp_opt = cmake.subproject_options()
sqlitecpp_opt.append_compile_args('cpp', '-DSQLITE_ENABLE_FTS5=1')
sqlitecpp_opt.append_compile_args('c', '-DSQLITE_ENABLE_FTS5=1')
sqlitecpp_pro = cmake.subproject('sqlitecpp', options: sqlitecpp_opt)

# External dependencies
dl = cpp.find_library('dl', required : true)
threads = dependency('threads')
sqlitecpp = declare_dependency(
	dependencies: [
		dl,
		threads,
		sqlitecpp_pro.dependency('SQLiteCpp'),
		sqlitecpp_pro.dependency('sqlite3')
	]
)


subdir('src')
