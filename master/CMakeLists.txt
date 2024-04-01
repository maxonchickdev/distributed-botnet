cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME master)
project(${PROJECT_NAME} C CXX)

set(CMAKE_CXX_STANDARD 20)

if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif ()

add_executable(${PROJECT_NAME} main.cpp src/db_methods.cpp includes/db_methods.hpp)


include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG 3b15fa82ea74739b574d705fea44959b58142eb8)
FetchContent_MakeAvailable(cpr)

FetchContent_Declare(Crow GIT_REPOSITORY https://github.com/CrowCpp/Crow.git
                         GIT_TAG v1.1.0)
FetchContent_MakeAvailable(Crow)

find_package(SQLite3)
include_directories(${SQLite3_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${SQLite3_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE cpr::cpr)

target_link_libraries(${PROJECT_NAME} PRIVATE Crow)

target_include_directories(${PROJECT_NAME} PRIVATE includes)
target_include_directories(${PROJECT_NAME} PRIVATE src)

INSTALL(PROGRAMS
		$<TARGET_FILE:${PROJECT_NAME}>
		DESTINATION bin)

set(ALL_TARGETS ${PROJECT_NAME})
