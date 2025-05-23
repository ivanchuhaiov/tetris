cmake_minimum_required(VERSION 3.30)
project(tetris)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

add_executable(tetris main.cpp
        Constants.cpp
        Constants.h
        Field.cpp
        Field.h
        Tetromino.cpp
        Tetromino.h
        Utils.cpp
        Utils.h
        Game.cpp
        Game.h
        ScoreManager.cpp
        ScoreManager.h
        Button.cpp
        Button.h
)

target_link_libraries(tetris PRIVATE sfml-graphics sfml-window sfml-system)

set_target_properties(tetris PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

add_custom_command(TARGET tetris POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:tetris>/resources
)