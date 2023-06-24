cmake_minimum_required(VERSION 3.12)
project("engine")

add_library(engine ../math/src/geometry.c src/game_object.c)