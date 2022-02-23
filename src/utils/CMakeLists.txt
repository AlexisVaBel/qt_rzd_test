set(SOURCES)
set(HEADERS)

set(UTILS_MODULES
        json
        )

foreach (X ${UTILS_MODULES})
    file(GLOB ${X}_SOURCES "${X}/*.cpp")
    file(GLOB ${X}_HEADERS "${X}/*.h")
    list(APPEND SOURCES ${${X}_SOURCES})
    list(APPEND HEADERS ${${X}_HEADERS})
    add_module("${CMAKE_CURRENT_SOURCE_DIR}/${X}")
endforeach ()


add_library(utils STATIC ${SOURCES} ${HEADERS})

target_link_libraries(utils PUBLIC Qt5::Core)
