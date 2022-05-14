find_package(OpenCV REQUIRED)

add_library(diffgrowth_lib
)

target_include_directories(diffgrowth_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(diffgrowth_lib LINK_PUBLIC ${OpenCV_LIBS})