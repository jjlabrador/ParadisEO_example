######################################################################################
### 1) Include the sources
######################################################################################

# include ParadisEO
include_directories(${PARADISEO_INCLUDE_DIR})

# include my own source
include_directories(${CMAKE_SOURCE_DIR}/src)

######################################################################################


######################################################################################
### 2) Define your target(s): just the flow-shop lib here
######################################################################################

# set where the library must be compiled
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

# add my *.cpp files in a list
set(ZDT_SOURCES
		ZDT.cpp
		ZDTEval.cpp
		ZDT1Eval.cpp
		ZDT2Eval.cpp)

# declare what is in my library: all my *.cpp files define in a list
add_library(lZDT STATIC ${ZDT_SOURCES})

######################################################################################

