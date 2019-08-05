set(GENERATED_DIR ${CMAKE_CURRENT_BINARY_DIR}/generated)
set(GENERATED_IDL_DIR ${GENERATED_DIR}/idl)
set(IDL_FILE ${CMAKE_CURRENT_SOURCE_DIR}/Arithmetics.idl)

foreach(FILE Arithmetics.h Arithmetics_i.c)
  list(APPEND MIDL_GUID_FILES ${GENERATED_IDL_DIR}/${FILE})
endforeach()

foreach(FILE Arithmetics_p.c dlldata.c)
  list(APPEND MIDL_PROXY_FILES ${GENERATED_IDL_DIR}/${FILE})
endforeach()

add_custom_command(OUTPUT ${MIDL_GUID_FILES} ${MIDL_PROXY_FILES}
                   DEPENDS ${IDL_FILE}
                   COMMAND midl ARGS ${IDL_FILE}
                   WORKING_DIRECTORY ${GENERATED_IDL_DIR})

add_library(ComGuid ${MIDL_GUID_FILES})
add_library(ComProxy SHARED ComProxy.def ${MIDL_PROXY_FILES})



target_include_directories(ComGuid PUBLIC src ${GENERATED_DIR})
target_compile_definitions(ComGuid PRIVATE _MIDL_USE_GUIDDEF_)
target_compile_definitions(ComProxy PRIVATE REGISTER_PROXY_DLL _WIN32_DCOM)
target_link_libraries(ComProxy PRIVATE ComGuid rpcns4 rpcrt4)