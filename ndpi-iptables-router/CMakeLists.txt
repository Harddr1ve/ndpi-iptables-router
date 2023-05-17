cmake_minimum_required(VERSION 3.16)

project(ndpi-iptables-router VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 REQUIRED COMPONENTS Quick)


qt_add_executable(appndpi-iptables-router
    main.cpp
    networkinterfacemodel.h
    networkinterfacemodel.cpp
    dpiworker.h
    dpiworker.cpp
    protocolmodel.h
    protocolmodel.cpp
    commandrunner.h
    commandrunner.cpp
)

qt_add_qml_module(appndpi-iptables-router
    URI ndpi-iptables-router
    VERSION 1.0
    QML_FILES Main.qml
)

set_target_properties(appndpi-iptables-router PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appndpi-iptables-router
    PRIVATE Qt6::Quick
    ndpi
    pcap
)

install(TARGETS appndpi-iptables-router
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
