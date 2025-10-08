project(ProjectLib)

set(SOURCE_FILES temp.cpp pch.h
        Game.cpp
        Game.h
        MainFrame.cpp
        MainFrame.h
        Football.cpp
        Football.h
        Item.cpp
        Item.h
        Enemy.cpp
        Enemy.h
        UMichEnemy.cpp
        UMichEnemy.h
        NDEnemy.cpp
        NDEnemy.h
        MovingItem.cpp
        MovingItem.h
        Level.cpp
        Level.h
        Coin.cpp
        Coin.h
        SilverCoin.cpp
        SilverCoin.h
        GoldCoin.cpp
        GoldCoin.h
        PowerUp.cpp
        PowerUp.h
        Wall.cpp
        Wall.h
        Platform.cpp
        Platform.cpp
        GameView.cpp
        GameView.h
)

set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

include(${wxWidgets_USE_FILE})

include_directories(${APPLICATION_LIBRARY})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)