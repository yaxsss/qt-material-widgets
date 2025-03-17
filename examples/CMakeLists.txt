set(CMAKE_INCLUDE_CURRENT_DIR ON)

# 设置可执行文件输出路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 收集所有源文件
file(GLOB SOURCES
    "*.cpp"
)

# 收集所有头文件
file(GLOB HEADERS
    "*.h"
)

# 收集所有UI文件
file(GLOB UI_FILES
    "*.ui"
)

# 添加资源文件
set(RESOURCES
    examples.qrc
)

# 创建可执行文件
add_executable(qt-material-widgets-examples
    ${SOURCES}
    ${HEADERS}
    ${UI_FILES}
    ${RESOURCES}
)

# 设置目标属性
set_target_properties(qt-material-widgets-examples PROPERTIES
    WIN32_EXECUTABLE TRUE
)

# 确保在链接前qt-material-widgets库已经构建完成
add_dependencies(qt-material-widgets-examples qt-material-widgets)

# 链接Qt库和Material Widgets库
target_link_libraries(qt-material-widgets-examples PRIVATE
    qt-material-widgets
)

# 设置包含目录
target_include_directories(qt-material-widgets-examples PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/components
    ${CMAKE_SOURCE_DIR}/components/lib
)

# 安装目标
install(TARGETS qt-material-widgets-examples
    RUNTIME DESTINATION bin
) 