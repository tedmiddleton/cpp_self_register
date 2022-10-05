
#          Copyright Ted Middleton 2022.
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          https://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required( VERSION 3.0 )
project( cpp_self_register )

enable_testing()

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

add_library( self_register INTERFACE
    self_register.hpp
    )

set( version 0.1.0 )

add_subdirectory( tests )

target_include_directories( self_register
    INTERFACE
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
    )

install( TARGETS self_register
         EXPORT self_register-targets
    )

install(
    FILES 
        self_register.hpp
    DESTINATION include/self_register 
    )

install( EXPORT self_register-targets
         DESTINATION lib/cmake/self_register
    )

set_property( TARGET self_register PROPERTY VERSION ${version} )
set_property( TARGET self_register PROPERTY SOVERSION 0 )
set_property( TARGET self_register PROPERTY 
    INTERFACE_self_register_MAJOR_VERSION 0 )
set_property( TARGET self_register PROPERTY 
    COMPATIBLE_INTERFACE_STRING self_register_MAJOR_VERSION )

export(EXPORT self_register-targets
       FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/self_register-targets.cmake"
)

# Generate the package version file in the build dir
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/self_register-config-version.cmake"
    VERSION "${version}"
    COMPATIBILITY AnyNewerVersion
    )

# Generate a config file in the build dir
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/self_register-config.cmake"
    INSTALL_DESTINATION lib/cmake/self_register
    )

# Install the config files into the install dir. This is necessary for 
# find_package( self_register ) to work (in config mode)
install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/self_register-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/self_register-config-version.cmake"
    DESTINATION lib/cmake/self_register
    )
