cmake_minimum_required(VERSION 3.31)
project(project1)
set(APPLICATION_LIBRARY ProjectLib)

set(CMAKE_CXX_STANDARD 17)
# Request the required wxWidgets libs
# Turn off wxWidgets own precompiled header system, since
# it doesn't seem to work. The CMake version works much better.
set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

# Include the wxWidgets use file to initialize various settings
include(${wxWidgets_USE_FILE})

add_subdirectory(${APPLICATION_LIBRARY})
include_directories(${APPLICATION_LIBRARY})

#please add app to source files whenever you implement it
set(SOURCE_FILES main.cpp pch.h
        ProjectLib/MainFrame.cpp
        ProjectLib/MainFrame.h
        )

add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES} ${APPLICATION_LIBRARY})
target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/images/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/images/)

add_subdirectory(Tests)
