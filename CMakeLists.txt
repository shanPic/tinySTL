cmake_minimum_required(VERSION 3.9)
project(tinySTL)

set(CMAKE_CXX_STANDARD 11)

add_executable(tinySTL main.cpp alloc.h construct.h type_traits.h iterator.h uninitialized.h vector.h deque.h RB_tree.h list.h RB_tree_handle.h RB_tree_dataClass.h pair.h function.h TEST/rb_tree_test.cpp map.h)