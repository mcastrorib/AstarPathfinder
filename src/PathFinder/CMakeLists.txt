add_library(PathFinder mNode.cpp mGrid.cpp Canvas.cpp AStar.cpp)

target_include_directories(PathFinder INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# Request that library be built with -std=c++11
# As this is public compile feature, anything that links to
# This lib will also be build with -std=c++11
target_compile_features(PathFinder PUBLIC cxx_std_11)

install(TARGETS PathFinder DESTINATION lib)
install(FILES mNode.h mGrid.h mHeap.h Canvas.h AStar.h DESTINATION include)
