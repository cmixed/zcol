cmake_minimum_required(VERSION 4.0)

project(zcol
    VERSION 1.0.0
    DESCRIPTION "Single-header C++23 colored terminal output & logging library"
    LANGUAGES CXX
)

# ── Header-only library ──────────────────────────────────────────

add_library(zcol INTERFACE)
add_library(zcol::zcol ALIAS zcol)

target_include_directories(zcol INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_compile_features(zcol INTERFACE cxx_std_23)

# ── Install ──────────────────────────────────────────────────────

include(GNUInstallDirs)

install(FILES zcol.hpp DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(TARGETS zcol EXPORT zcolTargets)

install(EXPORT zcolTargets
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/zcol
    NAMESPACE zcol::
)

export(TARGETS zcol FILE zcolTargets.cmake NAMESPACE zcol::)

# ── Tests (optional) ─────────────────────────────────────────────

option(ZCOL_BUILD_TESTS "Build zcol tests" OFF)

if(ZCOL_BUILD_TESTS)
    enable_testing()
    add_executable(zcol_test test/main.cpp)
    target_link_libraries(zcol_test PRIVATE zcol::zcol)
    add_test(NAME zcol_test COMMAND zcol_test)
endif()
