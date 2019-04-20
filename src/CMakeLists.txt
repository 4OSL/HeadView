set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

#QT库
find_package(Qt5Widgets CONFIG REQUIRED)
include_directories(${Qt5Widgets_INCLUDE_DIRS})
find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Gui CONFIG REQUIRED)
find_package(Qt5Network CONFIG REQUIRED)
include_directories(${Qt5Network_INCLUDE_DIRS})
find_package(Qt5PrintSupport CONFIG REQUIRED)
include_directories(${Qt5PrintSupport_INCLUDE_DIRS})
find_package(Qt5Xml CONFIG REQUIRED)
include_directories(${Qt5Xml_INCLUDE_DIRS})
find_package(Qt5Concurrent  CONFIG REQUIRED)
include_directories(${Qt5Concurrent_INCLUDE_DIRS})
find_package(Qt5AxContainer  CONFIG REQUIRED)
include_directories(${Qt5AxContainer_INCLUDE_DIRS})


file(GLOB SRC 
			"${CMAKE_CURRENT_SOURCE_DIR}/*.txt"
			"${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB GUI_UI 
			"${CMAKE_CURRENT_SOURCE_DIR}/*.ui")
			
qt5_wrap_ui(Gui_gen_srcs ${GUI_UI})
add_executable(${CMAKE_PROJECT_NAME} ${SRC} ${Gui_gen_srcs})

target_link_libraries(${CMAKE_PROJECT_NAME} ${Qt5Core_LIBRARIES} ${Qt5Gui_LIBRARIES} ${Qt5Widgets_LIBRARIES} 
							${Qt5Network_LIBRARIES}  ${Qt5PrintSupport_LIBRARIES} ${Qt5Concurrent_LIBRARIES} Qt5::AxContainer)