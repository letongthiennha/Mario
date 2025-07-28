cmake_minimum_required(VERSION 3.16)

project(Mario)



# Set C++ standard

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

# Include directories for headers
include_directories(
 ${CMAKE_SOURCE_DIR}/include
)


#Find all source file in /src folder
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp)



# Path to Raylib 

set(RAYLIB_DIR "C:/raylib/raylib")


# Add Raylib

add_subdirectory(${RAYLIB_DIR} raylib_build)


# Create executable

add_executable(${PROJECT_NAME} ${SOURCES} "include/CourseClearToken.h" "src/CourseClearToken.cpp" "include/Slider.h" "src/Slider.cpp" "include/SettingMenuState.h" "src/SettingMenuState.cpp" "src/TextBox.cpp" "include/TextBox.h" "include/ChatBot.h" "src/ChatBot.cpp" "src/ChatBotScreen.cpp" "include/ChatBotScreen.h" "include/GameModeSelectionState.h" "src/GameModeSelectionState.cpp")
target_compile_definitions(${PROJECT_NAME} PRIVATE RAYLIB_STATIC)

file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})






# Link Raylib and required system libraries

target_link_libraries(Mario raylib)



if (WIN32)
target_link_libraries(Mario winmm gdi32 opengl32)

endif()

if (WIN32)
    set_target_properties(Mario PROPERTIES
        WIN32_EXECUTABLE OFF#TRUE
    )
endif()