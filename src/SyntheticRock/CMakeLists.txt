add_library(SyntheticRock 
			SyntheticRock.cpp 
			Pore.cpp 
			SquarePore.cpp 
			PrismaticPore.cpp
			SphericalPore.cpp
			CylindricalPore.cpp
			SquarePoreDrawer.cpp
			PrismaticPoreDrawer.cpp
			SphericalPoreDrawer.cpp
			CylindricalPoreDrawer.cpp
			PlaneBarrierDrawer.cpp)

target_include_directories(SyntheticRock
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
          )


# Request that library be built with -std=c++11
# As this is public compile feature, anything that links to
# This lib will also be build with -std=c++11
target_compile_features(SyntheticRock PUBLIC cxx_std_11)

# We need to explicitly state that we need all CUDA files in the 
# library to be built with -dc as the member functions 
# could be called by other libraries and executables
# set(CMAKE_CUDA_FLAGS "-Xcompiler -fopenmp")

install(TARGETS SyntheticRock DESTINATION lib)
install(FILES 
		SyntheticRock.h 
		Pore.h 
		SquarePore.h 
		PrismaticPore.h
		SphericalPore.h
		CylindricalPore.h 
		SquarePoreDrawer.h
		PrismaticPoreDrawer.h
		SphericalPoreDrawer.h
		CylindricalPoreDrawer.h
		PlaneBarrierDrawer.h
		FileHandling.h DESTINATION include)
