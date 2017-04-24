cmake_minimum_required(VERSION 2.8)
PROJECT(mysqlpp_test)

AUX_SOURCE_DIRECTORY(./ SRC_LIST)
SET(EXECUTABLE_OUTPUT_PATH ../bin)

ADD_DEFINITIONS(-g -O0 -W -Wall -D_REENTRANT -D_FILE_OFFSET_BITS=64 -DAC_HAS_INFO -DAC_HAS_WARNING -DAC_HAS_ERROR -DAC_HAS_CRITICAL -DTIXML_USE_STL -DHAVE_CXX_STDHEADERS -Wno-deprecated ${CMAKE_CXX_FLAGS})


INCLUDE_DIRECTORIES(
./
/usr/local/include/mysql++
/usr/include/mysql
)

LINK_DIRECTORIES(
./
/usr/local/lib
)

ADD_EXECUTABLE(mysqlpp_test ${SRC_LIST})

TARGET_LINK_LIBRARIES(mysqlpp_test pthread dl z mysqlpp)
