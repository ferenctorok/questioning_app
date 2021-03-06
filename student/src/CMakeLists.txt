find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(HEADERS_DIR ${CMAKE_SOURCE_DIR}/include)

# ui_utils library
add_library(utils STATIC
    utils.cpp
    read_write_utils.cpp
    ${HEADERS_DIR}/utils.h
    answer_option.cpp
    ${HEADERS_DIR}/answer_option.h
    question_utils.cpp
    ${HEADERS_DIR}/question_utils.h
)
target_include_directories(utils PUBLIC ${HEADERS_DIR})
target_link_libraries(utils PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# task_solving library
add_library(task_solving
    task_solving.cpp
    ${HEADERS_DIR}/task_solving.h
)
target_include_directories(task_solving PUBLIC ${HEADERS_DIR})
target_link_libraries(task_solving PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    utils
)

# results_window library:
add_library(results_window
    results_window.cpp
    result_details.cpp
    ${HEADERS_DIR}/results.h
)
target_include_directories(results_window PUBLIC ${HEADERS_DIR})
target_link_libraries(results_window PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    utils
)

# main executable
add_executable(QAStudent
    WIN32
    main.cpp
    questioningapp.cpp
    questioningapp_open_task.cpp
    questioningapp_open_results.cpp
    ${HEADERS_DIR}/questioningapp.h
    ${CMAKE_IMG_RESOURCES}
)
target_include_directories(QAStudent PUBLIC ${HEADERS_DIR})
target_link_libraries(QAStudent PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    task_solving
    results_window
    utils
)
