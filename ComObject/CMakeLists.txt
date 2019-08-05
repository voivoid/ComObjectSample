add_library(ComObject STATIC inc/arithmetics_factory.h
                             arithmetics_factory.cpp
                             inc/arithmetics_impl.h
                             arithmetics_impl.cpp
                             stdafx.h)

target_link_libraries(ComObject PUBLIC ComGuid)
target_include_directories(ComObject PUBLIC inc)