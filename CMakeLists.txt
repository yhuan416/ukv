cmake_minimum_required(VERSION 3.5)

if(ESP_PLATFORM)

idf_component_register(SRCS "ukv.c"
                    INCLUDE_DIRS "include"
                    PRIV_INCLUDE_DIRS private_include
                    PRIV_REQUIRES nvs_flash freertos)

else()

project(ukv)

endif()
                    