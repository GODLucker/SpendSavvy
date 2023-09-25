cmake_minimum_required(VERSION 3.5)

project(SpendSavvy
        VERSION 1.0.0
	LANGUAGES C CXX

)
include_directories(include)
add_executable(SpendSavvy SpendSavvy.cpp src/account.cpp src/date.cpp src/transaction.cpp)

