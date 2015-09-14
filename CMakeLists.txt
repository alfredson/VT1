cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(VT1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

include(${Geant4_USE_FILE})

find_package(ROOT REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include ${Geant4_INCLUDE_DIR} ${ROOT_INCLUDE_DIR})
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(VT1 VT1Main.cc ${sources} ${headers})
target_link_libraries(VT1 ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

set(VT1_SCRIPTS visTestCo60Decay.mac histoTestCo60Decay.mac co60disk.mac)

foreach(_script ${VT1_SCRIPTS})
		configure_file(
			${PROJECT_SOURCE_DIR}/${_script}
			${PROJECT_BINARY_DIR}/${_script}
			COPYONLY
			)
endforeach()

install(TARGETS VT1 DESTINATION bin)