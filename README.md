# Simple Game Engine

This is a working in progress Game Engine and Space Shooter Game.

## Project Structure 

```text
assets/
│    ├─── audio/
│    ├─── bullets/
│    │    ├─── laserBlue01.png
│    │    └─── laserRed01.png
│    ├─── enemies/
│    ├─── fonts/
│    │    ├─── OrbitronBlack.ttf
│    │    ├─── OrbitronBold.ttf
│    │    ├─── OrbitronLight.ttf
│    │    └─── OrbitronMedium.ttf
│    └─── player/
│    │    └─── playerShip1_blue.png
cmake/
│    ├─── x64-windows-clang-static.cmake
│    └─── x64-windows-clang.cmake
include/
│    ├─── engine/
│    │    ├─── api/
│    │    │    ├─── AssetsAPI.hpp
│    │    │    ├─── EntityAPI.hpp
│    │    │    ├─── EventsAPI.hpp
│    │    │    ├─── InputAPI.hpp
│    │    │    ├─── ManagerAPI.hpp
│    │    │    ├─── ScenesAPI.hpp
│    │    │    ├─── TimeAPI.hpp
│    │    │    ├─── TimerAPI.hpp
│    │    │    ├─── WindowAPI.hpp
│    │    │    └─── WorldAPI.hpp
│    │    ├─── assets/
│    │    │    ├─── AssetDatabase.hpp
│    │    │    ├─── AssetHandle.hpp
│    │    │    ├─── AssetManager.hpp
│    │    │    └─── AssetManagerRegistry.hpp
│    │    ├─── backend/
│    │    │    └─── SDL/
│    │    │    │    ├─── audio/
│    │    │    │    │    └─── SDLAudio.hpp
│    │    │    │    ├─── graphics/
│    │    │    │    │    ├─── SDLRenderer.hpp
│    │    │    │    │    └─── SDLTexture.hpp
│    │    │    │    ├─── input/
│    │    │    │    │    └─── SDLInputManager.hpp
│    │    │    │    └─── window/
│    │    │    │    │    └─── SDLWindowManager.hpp
│    │    ├─── core/
│    │    │    ├─── audio/
│    │    │    │    └─── Audio.hpp
│    │    │    ├─── events/
│    │    │    │    ├─── ConnectionSlot.hpp
│    │    │    │    ├─── Connections.hpp
│    │    │    │    ├─── Event.hpp
│    │    │    │    ├─── EventBus.hpp
│    │    │    │    ├─── EventConnectionGroup.hpp
│    │    │    │    ├─── EventRegistry.hpp
│    │    │    │    ├─── Listener.hpp
│    │    │    │    ├─── QueuedEvent.hpp
│    │    │    │    └─── Signal.hpp
│    │    │    ├─── graphics/
│    │    │    │    ├─── Renderer.hpp
│    │    │    │    └─── Texture.hpp
│    │    │    ├─── helpers/
│    │    │    │    ├─── Flags.hpp
│    │    │    │    └─── Hash.hpp
│    │    │    ├─── input/
│    │    │    │    ├─── InputManager.hpp
│    │    │    │    ├─── KeyInput.hpp
│    │    │    │    ├─── MouseInput.hpp
│    │    │    │    └─── MouseState.hpp
│    │    │    ├─── log/
│    │    │    │    ├─── Log.hpp
│    │    │    │    ├─── LogLevel.hpp
│    │    │    │    ├─── Logger.hpp
│    │    │    │    └─── TypeName.hpp
│    │    │    ├─── math/
│    │    │    │    ├─── Circle.hpp
│    │    │    │    ├─── Math.hpp
│    │    │    │    ├─── Matrix3x3.hpp
│    │    │    │    ├─── Quaternion.hpp
│    │    │    │    ├─── Rect2D.hpp
│    │    │    │    ├─── Vector2D.hpp
│    │    │    │    └─── Vector3D.hpp
│    │    │    ├─── string/
│    │    │    │    ├─── StringHandle.hpp
│    │    │    │    ├─── StringIntern.hpp
│    │    │    │    └─── StringTable.hpp
│    │    │    └─── window/
│    │    │    │    └─── WindowManager.hpp
│    │    ├─── ecs/
│    │    │    ├─── components/
│    │    │    │    ├─── scripts/
│    │    │    │    │    ├─── Script.hpp
│    │    │    │    │    └─── ScriptComponent.hpp
│    │    │    │    ├─── BoxCollider.hpp
│    │    │    │    ├─── Lifetime.hpp
│    │    │    │    ├─── Renderable.hpp
│    │    │    │    ├─── Scoped.hpp
│    │    │    │    ├─── SpriteRenderer.hpp
│    │    │    │    ├─── Transform.hpp
│    │    │    │    └─── Velocity.hpp
│    │    │    ├─── entities/
│    │    │    │    └─── EntityBuilder.hpp
│    │    │    ├─── handle/
│    │    │    │    └─── Entity.hpp
│    │    │    ├─── registry/
│    │    │    │    ├─── components/
│    │    │    │    │    ├─── ComponentRegistry.hpp
│    │    │    │    │    ├─── ComponentSparseSet.hpp
│    │    │    │    │    └─── ComponentStorage.hpp
│    │    │    │    ├─── entities/
│    │    │    │    │    ├─── EntityId.hpp
│    │    │    │    │    └─── EntitySlot.hpp
│    │    │    │    ├─── managers/
│    │    │    │    │    ├─── ComponentManager.hpp
│    │    │    │    │    ├─── EntityManager.hpp
│    │    │    │    │    └─── SystemManager.hpp
│    │    │    │    ├─── systems/
│    │    │    │    │    ├─── SystemEntry.hpp
│    │    │    │    │    ├─── SystemRegistry.hpp
│    │    │    │    │    └─── SystemStage.hpp
│    │    │    │    ├─── views/
│    │    │    │    │    ├─── View.hpp
│    │    │    │    │    ├─── ViewEntity.hpp
│    │    │    │    │    ├─── ViewEntityIterator.hpp
│    │    │    │    │    └─── ViewIterator.hpp
│    │    │    │    └─── Registry.hpp
│    │    │    ├─── systems/
│    │    │    │    ├─── LifetimeSystem.hpp
│    │    │    │    ├─── MovementSystem.hpp
│    │    │    │    ├─── RenderSystem.hpp
│    │    │    │    └─── System.hpp
│    │    │    └─── world/
│    │    │    │    └─── World.hpp
│    │    ├─── scenes/
│    │    │    ├─── Scene.hpp
│    │    │    ├─── SceneCommand.hpp
│    │    │    ├─── SceneId.hpp
│    │    │    └─── SceneManager.hpp
│    │    ├─── scopes/
│    │    │    └─── ScopeId.hpp
│    │    ├─── time/
│    │    │    ├─── Time.hpp
│    │    │    ├─── Timer.hpp
│    │    │    └─── TimerManager.hpp
│    │    ├─── Engine.hpp
│    │    └─── Game.hpp
│    └─── game/
│    │    ├─── ecs/
│    │    │    ├─── components/
│    │    │    │    ├─── bullet/
│    │    │    │    ├─── common/
│    │    │    │    │    ├─── Damage.hpp
│    │    │    │    │    ├─── Dead.hpp
│    │    │    │    │    ├─── Health.hpp
│    │    │    │    │    ├─── OutOfBounds.hpp
│    │    │    │    │    ├─── ScreenClamp.hpp
│    │    │    │    │    └─── Weapon.hpp
│    │    │    │    ├─── enemy/
│    │    │    │    └─── player/
│    │    │    │    │    └─── PlayerInput.hpp
│    │    │    ├─── factories/
│    │    │    ├─── scripts/
│    │    │    └─── systems/
│    │    │    │    ├─── bullets/
│    │    │    │    ├─── common/
│    │    │    │    │    ├─── DamageSystem.hpp
│    │    │    │    │    ├─── DeathSystem.hpp
│    │    │    │    │    ├─── OutOfBoundsSystem.hpp
│    │    │    │    │    ├─── ScreenClampSystem.hpp
│    │    │    │    │    └─── WeaponCooldownSystem.hpp
│    │    │    │    ├─── enemy/
│    │    │    │    └─── player/
│    │    │    │    │    ├─── PlayerInputSystem.hpp
│    │    │    │    │    ├─── PlayerMoveSystem.hpp
│    │    │    │    │    └─── PlayerShootSystem.hpp
│    │    ├─── scenes/
│    │    │    └─── SceneFactory.hpp
│    │    └─── SpaceShooterGame.hpp
src/
│    ├─── engine/
│    │    ├─── backend/
│    │    │    └─── SDL/
│    │    │    │    ├─── graphics/
│    │    │    │    │    ├─── SDLRenderer.cpp
│    │    │    │    │    └─── SDLTexture.cpp
│    │    │    │    ├─── input/
│    │    │    │    │    └─── SDLInputManager.cpp
│    │    │    │    └─── window/
│    │    │    │    │    └─── SDLWindowManager.cpp
│    │    ├─── core/
│    │    │    ├─── log/
│    │    │    │    └─── Logger.cpp
│    │    │    └─── string/
│    │    │    │    └─── StringTable.cpp
│    │    ├─── ecs/
│    │    │    ├─── registry/
│    │    │    │    └─── managers/
│    │    │    │    │    ├─── EntityManager.cpp
│    │    │    │    │    └─── SystemManager.cpp
│    │    │    ├─── systems/
│    │    │    │    ├─── LifetimeSystem.cpp
│    │    │    │    ├─── MovementSystem.cpp
│    │    │    │    └─── RenderSystem.cpp
│    │    │    └─── world/
│    │    │    │    └─── World.cpp
│    │    ├─── scenes/
│    │    │    ├─── Scene.cpp
│    │    │    └─── SceneManager.cpp
│    │    ├─── time/
│    │    │    ├─── Time.cpp
│    │    │    ├─── Timer.cpp
│    │    │    └─── TimerManager.cpp
│    │    └─── Engine.cpp
│    ├─── game/
│    │    ├─── ecs/
│    │    │    ├─── factories/
│    │    │    ├─── scripts/
│    │    │    └─── systems/
│    │    │    │    ├─── bullets/
│    │    │    │    ├─── common/
│    │    │    │    │    ├─── DamageSystem.cpp
│    │    │    │    │    ├─── DeathSystem.cpp
│    │    │    │    │    ├─── OutOfBoundsSystem.cpp
│    │    │    │    │    ├─── ScreenClampSystem.cpp
│    │    │    │    │    └─── WeaponCooldownSystem.cpp
│    │    │    │    ├─── enemy/
│    │    │    │    └─── player/
│    │    │    │    │    ├─── PlayerInputSystem.cpp
│    │    │    │    │    ├─── PlayerMoveSystem.cpp
│    │    │    │    │    └─── PlayerShootSystem.cpp
│    │    ├─── scenes/
│    │    │    └─── SceneFactory.cpp
│    │    └─── SpaceShooterGame.cpp
│    └─── main.cpp
vendors/
│    └─── CMakeLists.txt
├── CMakeLists.txt
├── CMakePresets.json
├── CMakeUserPresets.json
├── README.md
└── vcpkg.json
```