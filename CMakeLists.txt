cmake_minimum_required(VERSION 3.10)

# https://devblogs.microsoft.com/cppblog/permissive-switch/
string(APPEND CMAKE_CXX_FLAGS_INIT "/permissive- /wd4996 ")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(fmatvec VERSION 1.0)

# cmake 3.12.18081601-MSVC_2 fails to find c:\local\boost_1_72_0 (it ONLY detects the coexisting c:\local\boost_1_60_0)
#     With boost 1.67 it works as expected
# cmake 3.17 finds c:\local\boost_1_72_0 extracted from boost_<version>-bin-msvc-all-32-64.7z
# Alternative: set BOOST_INCLUDEDIR to boost installation
find_package(Boost 1.67 REQUIRED ) # COMPONENTS spirit uuid ... => all header only ???

# Path with blas and lapack lib/dll needs to be in environment variable LIB
# find_package(BLAS) called separately for slightly better error message
find_package(BLAS REQUIRED) 
find_package(LAPACK REQUIRED ) 

set(FMATVEC_CONFIG_INCLUDE ${CMAKE_BINARY_DIR}/include)
file(WRITE ${FMATVEC_CONFIG_INCLUDE}/config.h "/* DUMMY FILE*/")

add_subdirectory(fmatvec)
#add_subdirectory(doc)
