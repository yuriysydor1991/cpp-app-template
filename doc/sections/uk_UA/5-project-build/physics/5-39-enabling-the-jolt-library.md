## Вмикання інтеграції Jolt Physics

Для того щоб увімкнути бібліотеку симуляції тривимірної фізики твердих тіл [Jolt Physics](https://github.com/jrouwe/JoltPhysics) для проекту, використовуючи встановлену версію або через завантаження з мережі, необхідно встановити значення `ON` для CMake змінної `ENABLE_JOLT`:

```
# в середині кореневої директорії проекту

cmake -S . -B build -DENABLE_JOLT=ON
```

Дивись модуль `cmake/enablers/physics/template-project-jolt-enabler.cmake` щодо цілі (`Jolt::Jolt` як для системної версії, так і для побудови через FetchContent), яку слід прилінкувати до твоїх цільових об'єктів.

Версія, що завантажується, визначається CMake змінною `TEMPLATE_APP_JOLT_GIT_TAG` (типово `v5.6.0`). CMake проект Jolt розташований у піддиректорії `Build` його репозиторію, тож модуль передає `SOURCE_SUBDIR` до оголошення FetchContent.

Модуль також перевизначає три налаштування Jolt, які увімкнено в оригіналі та які ламають звичайну побудову споживача:

- `INTERPROCEDURAL_OPTIMIZATION` вимкнено, оскільки об'єктні файли Jolt, зібрані з оптимізацією часу лінкування, неможливо прилінкувати, доки увесь проект не увімкне LTO також;
- `ENABLE_ALL_WARNINGS` вимкнено, оскільки воно збирає Jolt із попередженнями, які трактуються як помилки;
- `JPH_USE_VK` вимкнено, оскільки обчислювальний backend Jolt на Vulkan збирає свої шейдери компілятором `dxc` із Vulkan SDK, якого звичайний runtime Vulkan не постачає.

Усі три лишаються звичайними кеш змінними, тож передавай, наприклад, `-DINTERPROCEDURAL_OPTIMIZATION=ON`, якщо сам проект збирається з увімкненим LTO, або `-DJPH_USE_VK=ON` на машині зі встановленим повним Vulkan SDK. Обчислювальний backend на CPU (`JPH_USE_CPU_COMPUTE`) лишається увімкненим у будь-якому разі.

### Симуляція потрібних тіл (приклади для копіювання)

Після `ENABLE_JOLT=ON` та прилінкування цілі Jolt (наприклад `target_link_libraries(${PROJECT_BINARY_NAME} Jolt::Jolt)`) завжди підключай `<Jolt/Jolt.h>` перед будь-яким іншим заголовком Jolt і скопіюй сніпет нижче.

Jolt розкладає тіла по шарах об'єктів (які тіла з якими стикаються) та по шарах широкої фази (як розділено структуру прискорення). Табличні інтерфейси нижче покривають звичний поділ на рухомі / нерухомі без написання жодної реалізації інтерфейсу:

```cpp
#include <Jolt/Jolt.h>

#include <Jolt/Core/Factory.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Collision/BroadPhase/BroadPhaseLayerInterfaceTable.h>
#include <Jolt/Physics/Collision/BroadPhase/ObjectVsBroadPhaseLayerFilterTable.h>
#include <Jolt/Physics/Collision/ObjectLayerPairFilterTable.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/PhysicsSettings.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/RegisterTypes.h>

#include <cstdio>
#include <thread>

JPH_SUPPRESS_WARNINGS

namespace Layers {
static constexpr JPH::ObjectLayer NON_MOVING = 0;
static constexpr JPH::ObjectLayer MOVING = 1;
static constexpr JPH::uint COUNT = 2;
}  // namespace Layers

void jolt_bouncing_sphere()
{
  // Розподілювач пам'яті, фабрика та реєстрація типів є спільними для усього
  // процесу й мають відбутися перед будь-яким іншим викликом Jolt.
  JPH::RegisterDefaultAllocator();
  JPH::Factory::sInstance = new JPH::Factory();
  JPH::RegisterTypes();

  // Наперед виділена чорнова пам'ять для оновлення та робочі потоки, які
  // виконують завдання фізики.
  JPH::TempAllocatorImpl tempAllocator(10 * 1024 * 1024);
  JPH::JobSystemThreadPool jobSystem(JPH::cMaxPhysicsJobs, JPH::cMaxPhysicsBarriers,
                                     std::thread::hardware_concurrency() - 1);

  // Статичні тіла потрапляють у власний шар широкої фази, щоб рухомі ніколи
  // не перевірялися на зіткнення з деревом одне одного.
  JPH::ObjectLayerPairFilterTable objectLayerFilter(Layers::COUNT);
  objectLayerFilter.EnableCollision(Layers::MOVING, Layers::NON_MOVING);
  objectLayerFilter.EnableCollision(Layers::MOVING, Layers::MOVING);

  JPH::BroadPhaseLayerInterfaceTable broadPhaseLayers(Layers::COUNT, Layers::COUNT);
  broadPhaseLayers.MapObjectToBroadPhaseLayer(Layers::NON_MOVING,
                                              JPH::BroadPhaseLayer(Layers::NON_MOVING));
  broadPhaseLayers.MapObjectToBroadPhaseLayer(Layers::MOVING,
                                              JPH::BroadPhaseLayer(Layers::MOVING));

  JPH::ObjectVsBroadPhaseLayerFilterTable objectVsBroadPhase(
      broadPhaseLayers, Layers::COUNT, objectLayerFilter, Layers::COUNT);

  // Система утримує посилання на три фільтри вище, тож вони мають пережити її.
  JPH::PhysicsSystem system;
  system.Init(1024, 0, 1024, 1024, broadPhaseLayers, objectVsBroadPhase,
              objectLayerFilter);

  JPH::BodyInterface& bodies = system.GetBodyInterface();

  // Підлога: статична коробка 200x2x200 метрів (BoxShape приймає половини
  // розмірів).
  JPH::BodyCreationSettings floorSettings(
      new JPH::BoxShape(JPH::Vec3(100.0f, 1.0f, 100.0f)),
      JPH::RVec3(0.0f, -1.0f, 0.0f), JPH::Quat::sIdentity(),
      JPH::EMotionType::Static, Layers::NON_MOVING);
  JPH::BodyID floorId = bodies.CreateAndAddBody(floorSettings, JPH::EActivation::DontActivate);

  JPH::BodyCreationSettings sphereSettings(
      new JPH::SphereShape(0.5f), JPH::RVec3(0.0f, 2.0f, 0.0f),
      JPH::Quat::sIdentity(), JPH::EMotionType::Dynamic, Layers::MOVING);
  JPH::BodyID sphereId = bodies.CreateAndAddBody(sphereSettings, JPH::EActivation::Activate);

  // Варто викликати один раз після масової вставки тіл, ніколи не покадрово.
  system.OptimizeBroadPhase();

  const float deltaTime = 1.0f / 60.0f;

  while (bodies.IsActive(sphereId)) {
    JPH::RVec3 position = bodies.GetCenterOfMassPosition(sphereId);
    std::printf("%4.2f %4.2f %4.2f\n", float(position.GetX()),
                float(position.GetY()), float(position.GetZ()));

    // Один крок зіткнень на кожну 1/60 секунди часу, що минув.
    system.Update(deltaTime, 1, &tempAllocator, &jobSystem);
  }

  bodies.RemoveBody(sphereId);
  bodies.DestroyBody(sphereId);
  bodies.RemoveBody(floorId);
  bodies.DestroyBody(floorId);

  JPH::UnregisterTypes();
  delete JPH::Factory::sInstance;
  JPH::Factory::sInstance = nullptr;
}
```

Тримай крок `PhysicsSystem::Update()` сталим (рекомендовано `1/60` секунди) та
збільшуй кількість кроків зіткнень замість розміру кроку, коли треба спожити
більше часу за раз, інакше симуляція втрачає стабільність. Макрос
`JPH_SUPPRESS_WARNINGS` глушить попередження, які заголовки Jolt спричиняють у
одиниці трансляції, що їх підключає.
