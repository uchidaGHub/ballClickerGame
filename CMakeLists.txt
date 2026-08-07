cmake_minimum_required(VERSION 3.16)

project(ballClickerGame)

set(CMAKE_CXX_STANDARD 17)

set(SFML_DIR "C:/Libraries/SFML/SFML-3.1.0/lib/cmake/SFML")

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

add_executable(ballClickerGame src/main.cpp src/Ball.cpp)

target_link_libraries(ballClickerGame SFML::Graphics SFML::Window SFML::System)

target_include_directories(ballClickerGame PRIVATE include)
