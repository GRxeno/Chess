cmake_minimum_required(VERSION 3.21.2)

project(Chess)

file(GLOB SOURCES CONFIGURE_DEPENDS "*.h" "*.cpp" "API/*.h" "API/*.cpp" "API/*/*.h" "API/*/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

add_custom_command(
         TARGET ${PROJECT_NAME} POST_BUILD
         COMMAND ${CMAKE_COMMAND} -E copy_directory              
             ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
         COMMENT "Copying resources" VERBATIM
         )

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(external/glfw)
add_subdirectory(external/glew)

target_include_directories(${PROJECT_NAME}
    PUBLIC external/glfw/include
    PUBLIC external/glew/include
    PUBLIC external/glad/include
    PUBLIC external/glm
)

# target_link_directories(${PROJECT_NAME}
#     PRIVATE external/glfw/src
#     PRIVATE external/glew/src
# )

target_link_libraries(${PROJECT_NAME}
    glfw
    opengl32
    libglew_static
)

