cmake_minimum_required(VERSION 3.7)
project(mtm_ex2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        challenge.c
        challenge.h
        challenge_room_system_fields.h
        challenge_system.c
        challenge_system.h
        challenge_system_test_1.c
        constants.h
        visitor_room.c
        visitor_room.h)

add_executable(mtm_ex2 ${SOURCE_FILES})