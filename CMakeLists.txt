cmake_minimum_required(VERSION 3.0.0)

project(RPG-41 VERSION 0.1.0)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()


# Allows us to outputfiles into the project instead of the build directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS "-std=c++20")


# VERSION USE: This is going to be a message notifying just in case, I forget.
# VERSION: Cmake works on an M1 Mac 2022 December (Current month)
# This CMAKE Will be able to compile the following libraries
# OpenCV, SFML, SDL, OPENGL on mac

#################[SFML]##################
# Add to detect SFML Libraries here!
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED COMPONENTS network audio graphics window system)

# Searching for OpenGL frameworks
# OpenGL
# find_package(glfw3 3.4 REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
# find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${GLUT_INCLUDE_DIRS})


# We are adding more compile options
# Applying linked-time optimizations.
add_compile_options(
  -flto # Combines all multiple objs into one executable
  -fdata-sections #  Enabling data optimization. Data not used by program will not be in executable.
  -fvisibility-inlines-hidden # Hide functions in headers helping reduce size of executable
  -fno-rtti # This flag disables generation of run-tiome type info (which may be used to reduce code size)
)


# Handling our file structures here.
# This allows us to include our libraries throughout this entire project.
# This lets us get access to our includes and headers
file(GLOB
    "main.cpp"
    "include/*.h"
    "include/core/*.h"
)



# Globalizes our *.cpp files
file(
   GLOB
   SRC
   "src/*.cpp"
   "src/core/*.cpp"
)

add_executable(RPG-41 main.cpp)


# LINK OUR XENOS GAME ENIGINE LIBRARY THROUGH THE CMAKE FILE WE CREATED IN THE DIRECTORY
# Try to include my own headers...
# target_include_directories(${PROJECT_NAME} PUBLIC "XenosGameEngine")

# NOTE: These below here are going to grab our targeted and link our libraries opencv, sfml, sdl, and opengl

# Target including directories and libraries for SFML only!
# This includes are specifics to SFML
target_include_directories(${PROJECT_NAME} PRIVATE "include" "lib")
target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics)
if (UNIX)
   target_link_libraries(${PROJECT_NAME} pthread)
endif (UNIX)

# Copy res dir to the binary directory
# file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

if(MSVC)
   foreach(lib ${SFML_LIBS})
      get_target_property(lib_path ${lib} LOCATION)
      file(COPY ${lib_path} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
   endforeach()
endif(MSVC)




# Help link our SDL libraries
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

# Help for linking the opengl libraries
# Linking the link that helped get opengl working: 
# https://carette.xyz/posts/opengl_and_cpp_on_m1_mac/
# target_link_directories(${PROJECT_NAME} PUBLIC $(OPENGL_INCLUDE_DIR)) # Not gonna delete this commented, just so I know this wont work for future ref.

# Linking the libraries for Cocoa, OpenGL, IOKit, and glfw
target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
target_link_libraries(${PROJECT_NAME} "-framework IOKit")
target_link_libraries(${PROJECT_NAME} glfw ${OPENGL_gl_LIBRARY})
target_link_libraries(${PROJECT_NAME} GLEW::GLEW) # This helps us get rid of the "___glewGenBuffers" reference error

target_link_libraries(
    ${PROJECT_NAME}
    -flto
    -fdata-sections
    -fvisibility-inlines-hidden
)