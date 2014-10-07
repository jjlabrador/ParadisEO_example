include_directories(${PARADISEO_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(ZDT_NSGAII ZDT_NSGAII.cpp)
add_dependencies(ZDT_NSGAII lZDT)

# Only if you need to link libraries
target_link_libraries(ZDT_NSGAII ${PARADISEO_LIBRARIES} lZDT)


######################################################################################
### 5) Copy the instances and the "param" file in the build path for an easy use.
### 
### --> run the "make install" target to copy the parameter file / instances
###	in the directory where you build the application
######################################################################################

add_custom_target(install DEPENDS ${CMAKE_SOURCE_DIR}/application/NSGAII.param
				  ${CMAKE_SOURCE_DIR}/application)
add_custom_command(
    TARGET install
    POST_BUILD
    COMMAND ${CMAKE_COMMAND}
    ARGS -E copy_if_different
      ${CMAKE_SOURCE_DIR}/application/NSGAII.param
      ${CMAKE_BINARY_DIR}/application)

