set(CMAKE_INCLUDE_CURRENT_DIR ON)

# 设置库文件输出路径
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 收集所有源文件
file(GLOB SOURCES
    "*.cpp"
    "lib/*.cpp"
)

# 收集所有头文件
file(GLOB HEADERS
    "*.h"
    "lib/*.h"
)

# 添加资源文件
set(RESOURCES
    resources.qrc
)

# 创建静态库目标
add_library(qt-material-widgets STATIC
    ${SOURCES}
    ${HEADERS}
    ${RESOURCES}
)

# 设置目标属性
set_target_properties(qt-material-widgets PROPERTIES
    VERSION 1.0.0
    EXPORT_NAME QtMaterialWidgets
    DEBUG_POSTFIX "d"  # Debug版本添加后缀
    POSITION_INDEPENDENT_CODE ON  # 添加-fPIC选项
)

# 链接Qt库
target_link_libraries(qt-material-widgets PUBLIC
    Qt${QT_VERSION_MAJOR}::Widgets
)

# 设置包含目录
target_include_directories(qt-material-widgets PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib>
    $<INSTALL_INTERFACE:include/qt-material-widgets>
)

# 安装目标
install(TARGETS qt-material-widgets
    EXPORT QtMaterialWidgetsTargets
    ARCHIVE DESTINATION lib
    INCLUDES DESTINATION include/qt-material-widgets
)

# 安装头文件
install(FILES ${HEADERS}
    DESTINATION include/qt-material-widgets
) 