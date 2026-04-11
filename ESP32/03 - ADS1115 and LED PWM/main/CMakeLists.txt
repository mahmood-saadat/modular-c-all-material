FILE(GLOB my_sources
        "main.c"
        ../hal/*/src/*.c
        ../library/*/*/src/*.c
        )
FILE(GLOB my_headers
        ./
        ../hal/*/inc
        ../library/*/*/inc
        )

idf_component_register(
    SRCS "${my_sources}"
    INCLUDE_DIRS "${my_headers}"
    REQUIRES esp_driver_i2c esp_driver_gpio esp_driver_ledc)
