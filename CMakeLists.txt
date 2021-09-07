cmake_minimum_required(VERSION 2.8)
project(HV)

#Added to detect compiler support for C++11
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake/modules)

#option(CRY "Enable CRY library for cosmic event generation" OFF)

#if(CRY)
#add_definitions(-DUSE_CRY)
#endif(CRY)

#----------------------------------------------------------------------------
find_package(ROOT REQUIRED)
include_directories(${ROOT_INCLUDE_DIR})

#file(GLOB MAC_FILES ${PROJECT_SOURCE_DIR}/MacFiles/*)
#message(STATUS ${MAC_FILES})
#file(COPY ${MAC_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

include_directories(${PROJECT_SOURCE_DIR}/inc)

include_directories(inc)
file(GLOB hvSources src/*.cpp) 
add_library(hv SHARED ${hvSources})
target_link_libraries(hv ${ROOT_LIBRARIES})


SET(TESTSDIR ${TESTSDIR}
${CMAKE_SOURCE_DIR}/test
)


#COLLECTING ALL TEST FILES
macro(collect_tests TESTS)
  foreach(TEST ${TESTS})
    file(GLOB tests ${tests} ${TEST}/*.cpp)
  endforeach()
endmacro()

macro(build_executables EXECUTABLES)
  foreach(EXECUTABLE ${EXECUTABLES})
    get_filename_component(TARGET_NAME ${EXECUTABLE} NAME_WE)
    add_executable(${TARGET_NAME} ${EXECUTABLE}) # ${headers} ${sources})
    target_link_libraries(${TARGET_NAME} hv)
 endforeach()
endmacro()

collect_tests("${TESTSDIR}")
build_executables("${tests}")

#add_executable(AnalyzeData test/AnalyzeData.cpp ${sources} ${headers})
#target_link_libraries(AnalyzeData ${ROOT_LIBRARIES} ${TOMOLIB} Tracklib)


