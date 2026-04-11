FILE(GLOB my_sources
        "main.c"
        ../hal/*/src/*.c
        )
FILE(GLOB my_headers
        ./
        ../hal/*/inc
        )

idf_component_register(
    SRCS "${my_sources}"
    INCLUDE_DIRS "${my_headers}")
