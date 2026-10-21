cmake_minimum_required(VERSION 3.31)

find_package(SDL REQUIRED)

add_executable(fractal3k
	src/main.c
	src/input.c
	src/fractal.c
	src/parameterz.c
	)

add_library(palette src/palette.c)

target_link_libraries(fractal3k
	palette
	SDL::SDL
	m
)