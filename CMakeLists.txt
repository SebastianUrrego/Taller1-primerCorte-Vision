cmake_minimum_required(VERSION 2.8)

project(Taller1Vision)

include_directories("/usr/local/include")
find_package( OpenCV REQUIRED )

#add_executable(${PROJECT_NAME} "punto1.cpp")
#add_executable(${PROJECT_NAME} "punto2.cpp")
#add_executable(${PROJECT_NAME} "punto2b.cpp")
#add_executable(${PROJECT_NAME} "punto3a.cpp")
#add_executable(${PROJECT_NAME} "punto3b.cpp")
#add_executable(${PROJECT_NAME} "punto4a.cpp")
add_executable(${PROJECT_NAME} "punto4b.cpp")
target_link_libraries( ${PROJECT_NAME}  ${OpenCV_LIBS} )
