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

find_library(LAPACK_LIBRARIES name mkl_rt.lib PATHS $ENV{LIB})

target_link_libraries(fmatvec ${LAPACK_LIBRARIES})

set_target_properties( fmatvec
   PROPERTIES
   WINDOWS_EXPORT_ALL_SYMBOLS 1
)

target_compile_definitions(fmatvec
    PRIVATE
    "MSVC_DLL_DECLSPEC=__declspec(dllexport)"
)

   target_compile_definitions(fmatvec
     PUBLIC
     HAVE_LIBBLAS
   )

   target_compile_definitions(fmatvec
     PUBLIC
     HAVE_LIBLAPACK
   )

add_subdirectory(check)
