cmake_minimum_required(VERSION 3.10)
project("2drenderer")

add_library(2drenderer src/image.c src/renderer.c src/sprite.c src/animated_sprite.c)