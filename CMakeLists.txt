cmake_minimum_required(VERSION 4.0)
project(ray_tracer)

set(CMAKE_CXX_STANDARD 20)

include_directories(external/catch2 src)

add_executable(ray_tracer main.cpp
        src/Tuple.h
        src/Point.h
        src/Vector.h
        src/Vector.cpp
        src/Projectile.h
        src/Environment.h
        src/Color.h
        src/Canvas.h
        src/CanvasUtils.h)

add_executable(ray_tracer_tests
        tests/test_tuples.cpp
        src/Tuple.h
        tests/test_canvas.cpp
)
