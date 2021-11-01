#set (CMAKE_GENERATOR "NMake Makefiles" CACHE INTERNAL "" FORCE)
cmake_minimum_required(VERSION 3.21.2)

project(Chess)

file(GLOB SOURCES CONFIGURE_DEPENDS "*.h" "*.cpp" "API/*.h" "API/*.cpp" "API/*/*.h" "API/*/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

add_custom_command(
         TARGET ${PROJECT_NAME} POST_BUILD
         COMMAND ${CMAKE_COMMAND} -E copy_directory              
             ${CMAKE_SOURCE_DIR}/resources/textures $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources/textures
         COMMENT "Copying textures" VERBATIM
         )

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/resources/shaders/BoardFragmentShader.fs
    ${CMAKE_CURRENT_BINARY_DIR}/resources/shaders/BoardFragmentShader.fs COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/resources/shaders/BoardVertexShader.vs
    ${CMAKE_CURRENT_BINARY_DIR}/resources/shaders/BoardVertexShader.vs COPYONLY)


set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(external/glfw)
add_subdirectory(external/glew)
add_subdirectory(external/gtest)

target_include_directories(${PROJECT_NAME}
    PUBLIC external/glfw/include
    PUBLIC external/glew/include
    PUBLIC external/glad/include
    PUBLIC external/glm
    PUBLIC external/gtest/googletest/include
    PUBLIC external/gtest/googlemock/include
)

target_link_libraries(${PROJECT_NAME}
    glfw
    opengl32
    libglew_static libglew_shared
    gtest gtest_main
    gmock gmock_main
)

