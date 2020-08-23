cmake_minimum_required(VERSION 3.12)

add_executable(polyh_test
    main.cpp

    crtp_macro/crtp_friend.cpp
    crtp_macro/crtp_underlying.cpp
    crtp_macro/crtp_variadic_friend.cpp

    virtual_base/diamond_problem.cpp
    virtual_base/inheritance.cpp
    virtual_base/multilevel_inheritance.cpp
)

target_include_directories(polyh_test PRIVATE
                           $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>)

target_compile_features(polyh_test PRIVATE cxx_std_17)

target_compile_options(polyh_test
                       PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/std:c++17>
                       $<$<CXX_COMPILER_ID:MSVC>:/W4>
                       $<$<CXX_COMPILER_ID:MSVC>:/WX>
                       $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wall>
                       $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Werror>
                       $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-pedantic>)
