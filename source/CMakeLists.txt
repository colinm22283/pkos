set(BITS "32")

add_subdirectory(bootloader)
add_subdirectory(kernel)
add_subdirectory(pklib)
add_subdirectory(system)

file(WRITE null.cpp "")
add_executable(pkos.img null.cpp)
target_link_libraries(pkos.img PUBLIC bootloader kernel)

file(GLOB_RECURSE LD_SOURCES "linker/*.ld")
set_property(TARGET pkos.img PROPERTY LINK_DEPENDS "${LD_SOURCES}")
list(TRANSFORM LD_SOURCES PREPEND "-T")
target_link_options(pkos.img PRIVATE "${LD_SOURCES}")