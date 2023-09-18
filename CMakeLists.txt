cmake_minimum_required(VERSION 3.25.1)

project(mandelbrotSet
	VERSION 1.0.0
	LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


find_package(fmt CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)

file(GLOB SOURCES "*.cpp" "*.c")

add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -pedantic -march=native)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)
target_link_libraries(${PROJECT_NAME}
	PRIVATE
	$<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
	$<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>)
