project(ProjectLib)

set(SOURCE_FILES temp.cpp pch.h
        Game.cpp
        Game.h
        MainFrame.cpp
        MainFrame.h
        )

set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

include(${wxWidgets_USE_FILE})

include_directories(${APPLICATION_LIBRARY})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)