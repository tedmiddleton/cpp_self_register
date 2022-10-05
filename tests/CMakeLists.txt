cmake_minimum_required( VERSION 3.0 )

add_executable( self_register_test
    self_register_test.cpp
    )

target_link_libraries( self_register_test
    PRIVATE
        self_register
    )

add_test( self_register_test 
    self_register_test )

