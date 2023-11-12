cmake_minimum_required(VERSION 3.5)

project(SpendSavvy VERSION 1.0.0 LANGUAGES C CXX)


include_directories(include)


find_package(SQLite3 REQUIRED)


add_executable(SpendSavvy SpendSavvy.cpp src/account.cpp src/date.cpp src/transaction.cpp src/database.cpp)


target_link_libraries(SpendSavvy ${SQLite3_LIBRARIES})


target_include_directories(SpendSavvy PRIVATE ${SQLite3_INCLUDE_DIRS})
