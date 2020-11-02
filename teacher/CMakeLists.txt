cmake_minimum_required(VERSION 3.5)

project(QATeacher LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_IMG_RESOURCES
    ${CMAKE_SOURCE_DIR}/src/img/resources.qrc
    ${CMAKE_SOURCE_DIR}/src/resources.rc
    )

add_subdirectory(src)
