cmake_minimum_required(VERSION 3.14)
project(ZType)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(SFML 2 REQUIRED COMPONENTS graphics window system audio)

add_executable(ZType main.cpp Entity.cpp Entity.h EntityProxy.cpp EntityProxy.h Storage.cpp Storage.h GameManager.cpp GameManager.h weapon.h weapon.cpp bullet.cpp bullet.h State.h Machine.cpp Machine.h MenuManager.cpp MenuManager.h NewGame.cpp NewGame.h SettingsWindow.cpp SettingsWindow.h Levels.cpp Levels.h Sound/SoundManager.cpp Sound/SoundManager.h scoreboard.cpp scoreboard.h)
target_link_libraries (ZType sfml-graphics sfml-window sfml-system sfml-audio)
