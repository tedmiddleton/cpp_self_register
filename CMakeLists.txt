
#          Copyright Ted Middleton 2022.
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          https://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required( VERSION 3.0 )
project( cpp_self_register )

enable_testing()

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

add_library( self_register STATIC
    self_register.hpp
    self_register.cpp
    )

add_subdirectory( tests )

target_include_directories( self_register
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
    )

###install( TARGETS self_register
###         EXPORT self_register-targets
###    )
###
###install(
###    FILES 
###        self_register.hpp
###    DESTINATION include/self_register 
###    )
###
###install( EXPORT self_register-targets
###         DESTINATION lib/cmake/self_register
###    )
###
###set_property( TARGET mainframe PROPERTY VERSION ${version} )
###set_property( TARGET mainframe PROPERTY SOVERSION 0 )
###set_property( TARGET mainframe PROPERTY 
###    INTERFACE_mainframe_MAJOR_VERSION 0 )
###set_property( TARGET mainframe PROPERTY 
###    COMPATIBLE_INTERFACE_STRING mainframe_MAJOR_VERSION )
