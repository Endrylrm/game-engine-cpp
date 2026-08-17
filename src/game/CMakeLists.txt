set(GAME_SOURCES
    SpaceShooterGame.cpp
    ecs/systems/common/DamageSystem.cpp
    ecs/systems/common/DeathSystem.cpp
    ecs/systems/common/OutOfBoundsSystem.cpp
    ecs/systems/common/ScreenClampSystem.cpp
    ecs/systems/common/WeaponCooldownSystem.cpp
    ecs/systems/player/PlayerInputSystem.cpp
    ecs/systems/player/PlayerMoveSystem.cpp
    ecs/systems/player/PlayerShootSystem.cpp
    scenes/SceneFactory.cpp
)

add_library(Game STATIC ${GAME_SOURCES})
target_include_directories(Game PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(Game PUBLIC Engine)
