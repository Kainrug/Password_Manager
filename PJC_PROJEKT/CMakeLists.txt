cmake_minimum_required(VERSION 3.24)
project(PJC_PROJEKT)

set(CMAKE_CXX_STANDARD 20)
include(FetchContent)
FetchContent_Declare(
        fmt
        GIT_REPOSITORY  https://github.com/fmtlib/fmt
        GIT_TAG         a33701196adfad74917046096bf5a2aa0ab0bb50
)
FetchContent_MakeAvailable(fmt)
add_executable(PJC_PROJEKT main.cpp  Functions.cpp Functions.hpp Passwords.cpp Passwords.hpp Passwords.hpp)
target_link_libraries(PJC_PROJEKT fmt)