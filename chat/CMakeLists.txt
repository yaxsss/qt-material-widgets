set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(PROJECT_SOURCES
    main.cpp
    components/loginwindow.h
    components/loginwindow.cpp
    components/captchawidget.h
    components/captchawidget.cpp
)

# 设置目标属性
add_executable(chat WIN32
    ${PROJECT_SOURCES}
)

# 设置 C++ 标准
set_target_properties(chat PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

# Qt5 依赖
find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)

target_link_libraries(chat PRIVATE 
    Qt5::Core
    Qt5::Widgets
    Qt5::Gui
    qt-material-widgets
)

target_include_directories(chat PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/components
    ${CMAKE_SOURCE_DIR}/components/lib
)