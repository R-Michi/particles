# CMakeList.txt : CMake project for particles, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

project ("particles")

# Add source to this project's executable.
add_executable (particles 
    "main.cpp" "app.cpp" "app.hpp" "particles.hpp" "static_obj.cpp" "fountain.cpp" "particle.cpp" "particle_pool.cpp" # c++ source files for the program
    "GLshader/src/shader_load_src.cpp" "GLshader/src/shader_other_src.cpp" "GLshader/src/shader_uniform_src.cpp" # R-Michi's Shader loader library
  "random.hpp")

# copy shaders (copy from $src/shaders/* to $bin/shaders/*)
if(WIN32)
    add_custom_command(TARGET particles POST_BUILD
    COMMAND "robocopy" ARGS "\"${CMAKE_CURRENT_SOURCE_DIR}/assets\"" "\"${CMAKE_BINARY_DIR}/assets\"" "\"*.*\"" "/e" "/mir" "/njh" "/njs" "/ndl"
    )

    # OpenGL stuff thanks to windows not convenient
    include_directories("${CMAKE_CURRENT_SOURCE_DIR}/lib/glew-2.1.0/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw-3.3.3/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/glm")
else()
    add_custom_command(TARGET particles POST_BUILD
    COMMAND "cp" ARGS "\"${CMAKE_CURRENT_SOURCE_DIR}/assets\"" "\"${CMAKE_BINARY_DIR}/assets\"" "-rf"
    #COMMAND "echo" ARGS "[echo] cp " "\"${CMAKE_CURRENT_SOURCE_DIR}/assets\"" "\"${CMAKE_BINARY_DIR}/assets\"" "-r"
    )
endif()

# OpenMP
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(particles OpenMP::OpenMP_CXX)
endif()

if(WIN32)
    # OpenGL stuff, thanks to windows not convenient
    target_link_libraries(particles
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw-3.3.3/lib/glfw3.lib"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/glew-2.1.0/lib/Release/x64/glew32s.lib"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/glm/glm/lib/glm_static.lib"
    "opengl32"
    "-fopenmp")
else()
    # OpenGL stuff using CMake exporting
    find_package(glfw3 3.3 REQUIRED)
    target_link_libraries(particles glfw)
    set(OpenGL_PREFERENCE GLVND)
    find_package(OpenGL REQUIRED)
    target_link_libraries(particles OpenGL::GL)
    find_package(GLEW REQUIRED)
    target_link_libraries(particles GLEW::GLEW)
endif()
