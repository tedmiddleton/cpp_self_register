cmake_minimum_required( VERSION 3.0 )

add_library( aclass INTERFACE
    aclass.hpp
    )

target_include_directories( aclass
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
    )

target_link_libraries( aclass
    INTERFACE
        self_register
    )

add_library( sr_test_1 SHARED
    sr_test_1.cpp
    sr_test_1.hpp
    )

target_include_directories( sr_test_1
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
    )

target_link_libraries( sr_test_1
    PRIVATE
        aclass
    )

add_library( sr_test_2 SHARED
    sr_test_2.cpp
    sr_test_2.hpp
    )

target_include_directories( sr_test_2
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
    )

target_link_libraries( sr_test_2
    PRIVATE
        aclass
    )

add_executable( self_register_test
    self_register_test.cpp
    )

target_link_libraries( self_register_test
    PRIVATE
        self_register
        sr_test_1
        sr_test_2
    )

add_test( self_register_test 
    self_register_test )

