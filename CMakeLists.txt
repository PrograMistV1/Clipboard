cmake_minimum_required(VERSION 3.30)
project(Clipboard C)

set(APP_NAME "Clipboard")
set(CMAKE_C_STANDARD 11)
set(CMAKE_INSTALL_PREFIX "$ENV{HOME}/.local")

add_definitions(-DAPP_NAME="${APP_NAME}")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

add_executable(Clipboard main.c
        window.c
        window.h
        events.c
        events.h)

configure_file(resources/style.css ${CMAKE_BINARY_DIR}/style.css COPYONLY)
configure_file(resources/pin-icon.svg ${CMAKE_BINARY_DIR}/style.css COPYONLY)
configure_file(resources/delete-icon.svg ${CMAKE_BINARY_DIR}/style.css COPYONLY)
install(FILES
        resources/style.css
        resources/pin-icon.svg
        resources/delete-icon.svg
        DESTINATION share/Clipboard/resources)

install(TARGETS Clipboard RUNTIME DESTINATION bin)

target_include_directories(Clipboard PRIVATE ${GTK3_INCLUDE_DIRS})
target_link_libraries(Clipboard PRIVATE ${GTK3_LIBRARIES})
target_compile_options(Clipboard PRIVATE ${GTK3_CFLAGS_OTHER})