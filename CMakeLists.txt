cmake_minimum_required(VERSION 3.12)
project("plateau")

add_executable(plateau main.c)

add_subdirectory(2drenderer)
add_subdirectory(engine)

target_link_libraries(plateau PUBLIC 2drenderer engine m SDL2)

target_include_directories(plateau PUBLIC
                            "${PROJECT_BINARY_DIR}"
                            "${PROJECT_SOURCE_DIR/2drenderer/src}"
                            "${PROJECT_SOURCE_DIR/engine/src}"
)