cmake_minimum_required(VERSION 3.15)
project(pspg VERSION 5.8.12 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_definitions(-D_CRT_SECURE_NO_WARNINGS)

# PDCurses
find_package(unofficial-pdcurses CONFIG REQUIRED)
set(CURSES_LIBRARIES unofficial::pdcurses::pdcurses)
add_definitions(-DPDCURSES -DPDC_WIDE -DPDC_FORCE_UTF8 -DHAVE_CURSES_H)

# getopt
find_package(getopt CONFIG REQUIRED)
if(TARGET getopt::getopt_shared)
    set(GETOPT_LIBRARIES getopt::getopt_shared)
else()
    set(GETOPT_LIBRARIES getopt::getopt_static)
endif()

# PostgreSQL
find_package(PostgreSQL REQUIRED)
add_definitions(-DHAVE_POSTGRESQL)

# Source files
set(PSPG_SOURCES
    src/args.c
    src/bscommands.c
    src/commands.c
    src/config.c
    src/export.c
    src/infra.c
    src/inputs.c
    src/linebuffer.c
    src/pgclient.c
    src/pretty-csv.c
    src/print.c
    src/pspg.c
    src/readline.c
    src/sort.c
    src/string.c
    src/table.c
    src/theme_loader.c
    src/themes.c
    src/unicode.c
    src/platform/windows.c
    src/st_menu.c
    src/st_menu_styles.c
    src/menu.c
)

add_definitions(-DCOMPILE_MENU)

# Create executable
add_executable(pspg ${PSPG_SOURCES})

# Include directories
target_include_directories(pspg PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/platform
    ${CMAKE_CURRENT_SOURCE_DIR}/src/platform/compat/windows
    ${PostgreSQL_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(pspg PRIVATE
    ${CURSES_LIBRARIES}
    ${GETOPT_LIBRARIES}
    PostgreSQL::PostgreSQL
    ws2_32
)

# Compiler flags
if(MSVC)
    target_compile_options(pspg PRIVATE /W3)
else()
    target_compile_options(pspg PRIVATE -Wall -Wextra)
endif()

# Install
install(TARGETS pspg DESTINATION bin)
