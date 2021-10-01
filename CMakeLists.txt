add_executable(GC_commodore
        main.c
        )



target_sources(GC_commodore PRIVATE main.c)

target_include_directories(GC_commodore PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(GC_commodore pico_stdlib)



pico_add_extra_outputs(GC_commodore)

# add url via pico_set_program_url
example_auto_set_url(GC_commodore)
