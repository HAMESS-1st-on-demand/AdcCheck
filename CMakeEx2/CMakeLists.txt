cmake_minimum_required(VERSION 3.0.0)
project(adc_check_channel2 VERSION 0.1.0 LANGUAGES C)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CTest)
include(CPack)
enable_testing()

add_executable(adc_check_channel2 sensor1.c)
target_link_libraries(adc_check_channel2 wiringPi)
target_link_libraries(adc_check_channel2 bcm2835)
target_link_libraries(adc_check_channel2 pthread)
