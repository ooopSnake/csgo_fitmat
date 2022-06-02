cmake_minimum_required(VERSION 3.16)

project(fit_mat VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)

set(fit_mat_res_windows "${CMAKE_CURRENT_SOURCE_DIR}/win_res.rc")

qt_add_executable(fit_mat
    main.cpp 
    displaysetting.cpp
    display.cpp
    ${fit_mat_res_windows}
)

qt_add_qml_module(fit_mat
    URI fit_mat
    VERSION 1.0
    QML_FILES main.qml
)

set_target_properties(fit_mat PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(fit_mat
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(fit_mat
    PRIVATE Qt6::Quick)
