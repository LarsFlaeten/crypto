cmake_minimum_required(VERSION 3.1)
set (CMAKE_CXX_STANDARD 11)

file( GLOB APP_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp )
foreach( sourcefile ${APP_SOURCES} )
    # I used a simple string replace, to cut off .cpp.
    string( REPLACE ".cpp" "" appname ${sourcefile} )
    message(${appname} " " ${sourcefile} )
    add_executable( ${appname} ${sourcefile} )
    # Make sure YourLib is linked to each app    
endforeach( sourcefile ${APP_SOURCES} )
