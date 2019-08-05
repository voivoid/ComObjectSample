cmake_minimum_required(VERSION 3.14)

project(ComApp LANGUAGES C CXX CSharp)

add_subdirectory(ComIdl)
add_subdirectory(ComDll)
add_subdirectory(ComApp)
add_subdirectory(ComObject)
add_subdirectory(ComServer)