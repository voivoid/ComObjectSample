add_executable(ComApp main.cpp)
target_compile_options(ComApp PRIVATE /W4 /WX)
target_link_libraries(ComApp PRIVATE ComGuid)