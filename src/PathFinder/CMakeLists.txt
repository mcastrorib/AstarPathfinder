add_library(PathFinder PathFinder.cxx)
target_include_directories(PathFinder INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(PathFinder PUBLIC cxx_std_11)
install(TARGETS PathFinder DESTINATION lib)
install(FILES PathFinder.h mNode.h mGrid.h mHeap.h Canvas.h AStar.h PathFinderApp.h DESTINATION include)
