cmake_minimum_required(VERSION 2.6)

project(simplerumble2)
set(EXECUTABLE_NAME "SimpleRumble")

add_definitions(-std=gnu++0x) # -Wno-unused-parameter -Wno-unused-function -Wno-unused-variable)

# Version :
set(Simplerumble_VERSION_MAJOR 2)
set(Simplerumble_VERSION_MINOR 2)


message("${PROJECT_SOURCE_DIR}")
message("${PROJECT_BINARY_DIR}")
message("${CMAKE_SOURCE_DIR}")

# configure header for some cmake settings :
configure_file(
    "${PROJECT_SOURCE_DIR}/src/SRConfig.h.in"
    "${PROJECT_BINARY_DIR}/SRConfig.h"
    )

file(GLOB_RECURSE Simplerumble_SOURCES "src/*.cpp")
list(REMOVE_ITEM Simplerumble_SOURCES "${PROJECT_SOURCE_DIR}/src/main2.cpp")
list(REMOVE_ITEM Simplerumble_SOURCES "${PROJECT_SOURCE_DIR}/src/main3.cpp")
message(${Simplerumble_SOURCES})
file(GLOB_RECURSE Simplerumble_real_SOURCES "src/*.cpp")
list(REMOVE_ITEM Simplerumble_real_SOURCES "${PROJECT_SOURCE_DIR}/src/main.cpp")
list(REMOVE_ITEM Simplerumble_real_SOURCES "${PROJECT_SOURCE_DIR}/src/main3.cpp")
message(${Simplerumble_real_SOURCES})
file(GLOB_RECURSE Simplerumble_real2_SOURCES "src/*.cpp")
list(REMOVE_ITEM Simplerumble_real2_SOURCES "${PROJECT_SOURCE_DIR}/src/main.cpp")
list(REMOVE_ITEM Simplerumble_real2_SOURCES "${PROJECT_SOURCE_DIR}/src/main2.cpp")
message(${Simplerumble_real_SOURCES})

include_directories("${PROJECT_BINARY_DIR}")

#message(${Simplerumble_SOURCES})

# executable built
add_executable(${EXECUTABLE_NAME} ${Simplerumble_SOURCES})
add_executable(${EXECUTABLE_NAME}_real ${Simplerumble_real_SOURCES})
add_executable(${EXECUTABLE_NAME}_real2 ${Simplerumble_real2_SOURCES})

add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/media ${CMAKE_BINARY_DIR}/media)
add_custom_command(TARGET ${EXECUTABLE_NAME}_real POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/media ${CMAKE_BINARY_DIR}/media)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
    target_link_libraries(${EXECUTABLE_NAME}_real ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
    target_link_libraries(${EXECUTABLE_NAME}_real2 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()



