find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

add_executable(questioning_app
    main.cpp
    questioningapp.cpp
    ../include/questioningapp.h
)

target_include_directories(questioning_app PUBLIC ../include)
target_link_libraries(questioning_app PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
