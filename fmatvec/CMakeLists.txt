cmake_minimum_required(VERSION 3.10)

set( fmatvecSrc
   _memory.cc
   ast.cc
   atom.cc
   linear_algebra_complex.cc
   linear_algebra_double.cc
   stream.cc 
   wrapper.cc 
)

file(GLOB_RECURSE fmatvecHdr "*.h")

add_library(fmatvec SHARED ${fmatvecSrc} ${fmatvecHdr})

target_include_directories( fmatvec 
   PUBLIC 
   $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
   # $<INSTALL_INTERFACE:include/mylib>  # <prefix>/include/mylib
   $<BUILD_INTERFACE:${Boost_INCLUDE_DIRS}>
   PRIVATE
   $<BUILD_INTERFACE:${FMATVEC_CONFIG_INCLUDE}>
)

target_link_libraries(fmatvec ${LAPACK_LIBRARIES})

#set_target_properties( fmatvec
#   PROPERTIES
#   WINDOWS_EXPORT_ALL_SYMBOLS 1
#)

target_compile_definitions(fmatvec
    PRIVATE
    "MSVC_DLL_DECLSPEC=__declspec(dllexport)"
)

file(TO_NATIVE_PATH "fmatvec/CMakeFiles/fmatvec.dir/exports.def" fmatvec_exports_def)

set_target_properties(fmatvec 
    PROPERTIES 
    LINK_FLAGS "/DEF:${fmatvec_exports_def}"
)

add_custom_command(TARGET fmatvec 
                   PRE_LINK 
                   COMMAND ${CMAKE_COMMAND} -E __create_def "${fmatvec_exports_def}" "${CMAKE_SOURCE_DIR}/exports.def.objs"
                   COMMAND "${CMAKE_SOURCE_DIR}/filter-dllexport.bat" "${fmatvec_exports_def}"
                   # without the WORKING_DIRECTORY set, cmake cd's to wrong dir and subsequent commands fail!
                   WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
                   COMMENT "Filter exports"
)

if( BLAS_FOUND )
   target_compile_definitions(fmatvec
     PUBLIC
     HAVE_LIBBLAS
   )
endif()

if( LAPACK_FOUND )
   target_compile_definitions(fmatvec
     PUBLIC
     HAVE_LIBLAPACK
   )
endif()

add_subdirectory(check)
