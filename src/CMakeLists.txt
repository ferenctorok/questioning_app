find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(HEADERS_DIR ${CMAKE_SOURCE_DIR}/include)

# ui_utils library
add_library(utils STATIC
    utils.cpp
    ${HEADERS_DIR}/utils.h
    )
target_include_directories(utils PUBLIC ${HEADERS_DIR})
target_link_libraries(utils PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# new_questions library
add_library(new_questions STATIC
    new_questions.cpp
    new_questions_window.cpp
    ${HEADERS_DIR}/new_questions.h
    )
target_include_directories(new_questions PUBLIC ${HEADERS_DIR})
target_link_libraries(new_questions PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    utils
    )

# main executable
add_executable(questioning_app
    main.cpp
    questioningapp.cpp
    ${HEADERS_DIR}/questioningapp.h
)
target_include_directories(questioning_app PUBLIC ${HEADERS_DIR})
target_link_libraries(questioning_app PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    new_questions
    utils
    )
