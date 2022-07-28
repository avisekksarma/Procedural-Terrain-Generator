find_package (SFML REQUIRED system window graphics)
set(source_dir "${PROJECT_SOURCE_DIR}/project/src/")
# set (CMAKE_CXX_STANDARD 11)
set(include_dir "${myproject_SOURCE_DIR}/project/include")
# include_directories(${myproject_SOURCE_DIR}/project/include)
include_directories(${include_dir})
link_directories(${include_dir})

# include_directories(${myproject_SOURCE_DIR}/project/include/glMath)

# include_directories(${myproject_SOURCE_DIR}/glalib/include)
#link_directories(${myproject_SOURCE_DIR}/glalib/src)
# link_directories(${myproject_SOURCE_DIR}/project/src)

include_directories(${SFML_INCLUDE_DIR})
# set (SOURCE_FILES src/main.cpp src/glMath.cpp src/Cube.cpp)
#we add the executable of the program
file(GLOB SOURCE_FILES "${source_dir}/*.cpp" "${source_dir}/*.c" "${include_directories}/glMath.h")
add_executable (myproject ${SOURCE_FILES})
target_link_libraries(myproject PRIVATE sfml-graphics sfml-system sfml-window)
