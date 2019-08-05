add_library(ComDll SHARED ComDll.def
                          dll_main.cpp)

target_compile_options(ComDll PRIVATE /W4 /WX)
target_include_directories(ComDll PUBLIC inc)
target_link_libraries(ComDll PRIVATE ComObject)