cmake_minimum_required(VERSION 3.16)

project(TcpClient LANGUAGES CXX)

# Automatic configuration for UIC, MOC, and RCC (required for Qt applications)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the required Qt packages (add QtWidgets for using QMessageBox)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Network Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Network Widgets)

# Create the executable application TcpClient
add_executable(TcpServer
  main.cpp
  tcpserver.h tcpserver.cpp
  protocol.h protocol.cpp
)

set(SKIP_AUTOMOC TRUE)

# Link the necessary Qt libraries using the "keyword" syntax
target_link_libraries(TcpServer PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::Widgets)

# Set the installation directories
include(GNUInstallDirs)
install(TARGETS TcpServer
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# If using Qt6, call qt_finalize_executable
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(TcpServer)
endif()
