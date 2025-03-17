cmake_minimum_required(VERSION 3.14)

project(qt-material-widgets LANGUAGES CXX)

# 设置源文件编码为UTF-8
if(MSVC)
    # 使用单一的UTF-8选项
    add_compile_options(/utf-8)
    # 添加调试信息
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /DEBUG")
endif()

# 启用调试输出
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 添加Qt安装路径的查找配置
set(CMAKE_PREFIX_PATH $ENV{QTDIR})
if(NOT CMAKE_PREFIX_PATH)
    if(WIN32)
        # 在Windows上查找Qt的常见安装路径
        file(GLOB Qt_DIR "D:/Qt/*/msvc2019_64")
        if(Qt_DIR)
            list(GET Qt_DIR 0 Qt_DIR)  # 使用找到的第一个路径
            set(CMAKE_PREFIX_PATH ${Qt_DIR})
            message(STATUS "Found Qt at: ${Qt_DIR}")
        endif()
    endif()
endif()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

message(STATUS "Qt version: ${QT_VERSION_MAJOR}")
message(STATUS "Qt include dirs: ${Qt${QT_VERSION_MAJOR}Widgets_INCLUDE_DIRS}")

# 启用警告相关选项
add_definitions(-DQT_DEPRECATED_WARNINGS)
# 取消注释下面这行可以禁用所有在Qt 6.0.0之前被弃用的API
# add_definitions(-DQT_DISABLE_DEPRECATED_BEFORE=0x060000)

# 添加子目录
add_subdirectory(components)
add_subdirectory(examples) 
add_subdirectory(chat)