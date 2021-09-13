project('pathfinder2-telegram', 'cpp', default_options: ['cpp_std=c++17'])

cmake = import('cmake')
cpp = meson.get_compiler('cpp')

# Subproject options
sqlitecpp_opt = cmake.subproject_options()
sqlitecpp_opt.append_compile_args('cpp', '-DSQLITE_ENABLE_FTS5=1')
sqlitecpp_opt.append_compile_args('c', '-DSQLITE_ENABLE_FTS5=1')

# CMake subprojects
sqlitecpp_pro = cmake.subproject('sqlitecpp', options: sqlitecpp_opt)
tgbot_pro = cmake.subproject('tgbot-cpp')
json_pro = subproject('json')
httplib_pro = cmake.subproject('cpp-httplib')

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
tgbot = tgbot_pro.dependency('TgBot')
json = json_pro.get_variable('nlohmann_json_dep')
catch2 = declare_dependency(include_directories: ['subprojects/catch2/single_include/'])
httplib = httplib_pro.dependency('httplib')

subdir('src')
subdir('test')

# Install data
install_data('inventory_bot.service', install_dir: '/usr/lib/systemd/system/')
install_data('inventory_bot.env', install_dir: '/etc/')
install_subdir('localization_data', install_dir : '/usr/share/inventory_bot/')

meson.add_install_script('build_certificates.sh')