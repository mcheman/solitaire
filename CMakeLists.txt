cmake_minimum_required(VERSION 3.15)
project(solitaire C)

#find_library(ALLEGRO_LIB allegro)
#find_library(ALLEGRO_IMAGE_LIB allegro_image)
#find_library(ALLEGRO_AUDIO_LIB allegro_audio)

set(CMAKE_C_STANDARD 11)
#set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Werror")

add_executable(solitaire solitaire.c)

target_link_libraries(solitaire "allegro" "allegro_image" "allegro_audio" "allegro_acodec")
