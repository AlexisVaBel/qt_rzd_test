include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

set(MODULES)
macro(add_module FOLDER)
    set(MODULES ${MODULES} "${FOLDER}")
    set(MODULES ${MODULES} PARENT_SCOPE)
endmacro()

set(APP_NAME rzd_test_work)
set(CMAKE_INSTALL_PREFIX "/opt/${APP_NAME}" CACHE PATH "App installation directory" FORCE)
include(GNUInstallDirs)


set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH "$ORIGIN/../${CMAKE_INSTALL_LIBDIR}")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)


# ORDER OF TARGETS IS IMPORTANT - first utils
add_subdirectory(utils)
add_subdirectory(client)


