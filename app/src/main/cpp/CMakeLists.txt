cmake_minimum_required(VERSION 3.4.1)

add_library( root_checks SHARED root_checks.cpp )

find_library( log-lib log )

target_link_libraries( root_checks ${log-lib} )
