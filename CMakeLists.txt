cmake_minimum_required(VERSION 3.5)

if(ESP_PLATFORM)

idf_component_register(SRCS "ukv.c"
                    INCLUDE_DIRS "include")

else()

project(ukv)

endif()
                    