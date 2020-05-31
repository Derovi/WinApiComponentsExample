cmake_minimum_required(VERSION 3.14)
project(winapi2)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")

add_executable(winapi2 main.cpp app.cpp app.h Level.cpp Level.h levels/ButtonLevel.cpp levels/ButtonLevel.h levels/EditLevel.cpp levels/EditLevel.h levels/CheckBoxLevel.cpp levels/CheckBoxLevel.h levels/CalendarLevel.cpp levels/CalendarLevel.h levels/TrackBarLevel.cpp levels/TrackBarLevel.h levels/ComboBoxLevel.cpp levels/ComboBoxLevel.h levels/UpDownLevel.cpp levels/UpDownLevel.h levels/ColorLevel.cpp levels/ColorLevel.h levels/FileLevel.cpp levels/FileLevel.h)
target_link_libraries(winapi2 "Comctl32.lib")
