cmake_minimum_required(VERSION 3.10)

project(MySDL2Project)

# Find SDL2 package
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# Include SDL2 headers
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

# Add your source files
file(GLOB SOURCES "*.cpp")

# Create executable
add_executable(MySDL2Project ${SOURCES})

# Link SDL2 libraries
target_link_libraries(MySDL2Project ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

target_link_libraries(MySDL2Project ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} SDL2main)