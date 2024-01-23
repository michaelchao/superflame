
add_executable(how_const_string how_const_string.cc)
add_executable(how_fixed_string how_fixed_string.cc)
add_executable(how_raii_helper how_raii_helper.cc)
add_executable(how_static_initializer how_static_initializer.cc)
add_executable(how_ignore_unused how_ignore_unused.cc)

target_compile_options(how_ignore_unused PRIVATE -Werror=unused-parameter)

