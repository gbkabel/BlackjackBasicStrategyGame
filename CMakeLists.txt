cmake_minimum_required(VERSION 3.26)
project(BlackjackBasicStrategyGame)

set(CMAKE_CXX_STANDARD 17)

add_executable(BlackjackBasicStrategyGame
        code/Blackjack.h
        code/Blackjack.cpp
        code/main.cpp
)
