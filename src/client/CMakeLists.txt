set(SOURCES)
set(HEADERS)
set(UIS)

set(CLIENT_MODULES ui ui/model ui/controller)

foreach (X ${CLIENT_MODULES})
    file(GLOB ${X}_SOURCES "${X}/*.cpp")
    file(GLOB ${X}_HEADERS "${X}/*.h")
    file(GLOB ${X}_UIS "${X}/*.ui")
    qt5_wrap_ui(${X}_UIS_H ${${X}_UIS})
    list(APPEND SOURCES ${${X}_SOURCES})
    list(APPEND HEADERS ${${X}_HEADERS})
    list(APPEND UIS ${${X}_UIS})
    add_module("${CMAKE_CURRENT_SOURCE_DIR}/${X}")
endforeach ()

configure_file(Deploy.in.h Deploy.h)


qt5_add_resources(QT_RESOURCES qml.qrc)

add_library(client STATIC ${SOURCES} ${HEADERS} ${UIS})
target_include_directories(client PRIVATE "${PROJECT_BINARY_DIR}")
target_include_directories(client PUBLIC "${CMAKE_CURRENT_BINARY_DIR}")
target_link_libraries(client PUBLIC Qt5::Core Qt5::Widgets Qt5::Multimedia Qt5::MultimediaWidgets Qt5::Qml Qt5::Quick)

#add some utils
target_link_libraries(client PUBLIC utils)


add_executable(${APP_NAME} main.cpp ${QT_RESOURCES})

target_link_libraries(${APP_NAME}
        PRIVATE project_options
        project_warnings
        CONAN_PKG::docopt.cpp
        CONAN_PKG::fmt
        CONAN_PKG::spdlog
        PUBLIC
        client
        Qt5::Widgets
        Qt5::Qml
        Qt5::Quick
        )

target_link_options(${APP_NAME} PUBLIC "-Wl,--disable-new-dtags")
target_link_options(${APP_NAME} PUBLIC "-Wl,-z,origin")

