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

add_library(fmatvec SHARED ${fmatvecSrc} ${fmatvecHdr} )

target_include_directories( fmatvec 
   PUBLIC 
   $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
   # $<INSTALL_INTERFACE:include/mylib>  # <prefix>/include/mylib
   PRIVATE
   $<BUILD_INTERFACE:${FMATVEC_CONFIG_INCLUDE}>
   $<BUILD_INTERFACE:${Boost_INCLUDE_DIRS}>
)

target_link_libraries(fmatvec ${LAPACK_LIBRARIES})

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

