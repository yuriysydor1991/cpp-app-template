## Enabling the Jolt Physics library

In order to enable the [Jolt Physics](https://github.com/jrouwe/JoltPhysics) 3D rigid body physics simulation library for the project by using the installed system one or by fetching it through the available connection set an `ON` value to the `ENABLE_JOLT` CMake variable.

```
# Inside the source root directory

cmake -S . -B build -DENABLE_JOLT=ON
```

See the `cmake/enablers/physics/template-project-jolt-enabler.cmake` module for the target (`Jolt::Jolt` for both a system install and the FetchContent build) to link to your targets of interest.

The fetched revision is driven by the `TEMPLATE_APP_JOLT_GIT_TAG` CMake variable (`v5.6.0` by default). The Jolt CMake project lives in the `Build` subdirectory of its repository, so the enabler passes a `SOURCE_SUBDIR` to the FetchContent declaration.

The enabler also defaults three Jolt options that upstream turns on and that break a plain consumer build:

- `INTERPROCEDURAL_OPTIMIZATION` is switched `OFF`, since the Jolt objects built with the link time optimization are not linkable unless the whole project enables the LTO as well;
- `ENABLE_ALL_WARNINGS` is switched `OFF`, since it compiles Jolt with the warnings treated as errors;
- `JPH_USE_VK` is switched `OFF`, since the Jolt Vulkan compute backend compiles its shaders with the `dxc` compiler of the Vulkan SDK, which the plain Vulkan runtime does not ship.

All three stay ordinary cache variables, so pass e.g. `-DINTERPROCEDURAL_OPTIMIZATION=ON` if the project itself is built with the LTO enabled, or `-DJPH_USE_VK=ON` on a host with the full Vulkan SDK installed. The CPU compute backend (`JPH_USE_CPU_COMPUTE`) stays on either way.

### Simulating the bodies of interest (copy-paste examples)

After `ENABLE_JOLT=ON` and linking the Jolt target (e.g. `target_link_libraries(${PROJECT_BINARY_NAME} Jolt::Jolt)`), always include `<Jolt/Jolt.h>` before any other Jolt header and copy-paste the snippet below.

Jolt sorts the bodies into the object layers (which bodies collide with which) and the broad phase layers (how the acceleration structure is split). The table based interfaces below cover the usual moving / non moving split without writing a single interface implementation:

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
  // The allocator, the factory and the type registration are process wide and
  // must happen before any other Jolt call.
  JPH::RegisterDefaultAllocator();
  JPH::Factory::sInstance = new JPH::Factory();
  JPH::RegisterTypes();

  // Pre-allocated scratch memory for the update and the worker threads that
  // run the physics jobs.
  JPH::TempAllocatorImpl tempAllocator(10 * 1024 * 1024);
  JPH::JobSystemThreadPool jobSystem(JPH::cMaxPhysicsJobs, JPH::cMaxPhysicsBarriers,
                                     std::thread::hardware_concurrency() - 1);

  // The static bodies land in their own broad phase layer, so that the moving
  // ones never get tested against each other's tree.
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

  // The system keeps references to the three filters above, so they must
  // outlive it.
  JPH::PhysicsSystem system;
  system.Init(1024, 0, 1024, 1024, broadPhaseLayers, objectVsBroadPhase,
              objectLayerFilter);

  JPH::BodyInterface& bodies = system.GetBodyInterface();

  // The floor: a 200x2x200 meters static box (BoxShape takes half extents).
  JPH::BodyCreationSettings floorSettings(
      new JPH::BoxShape(JPH::Vec3(100.0f, 1.0f, 100.0f)),
      JPH::RVec3(0.0f, -1.0f, 0.0f), JPH::Quat::sIdentity(),
      JPH::EMotionType::Static, Layers::NON_MOVING);
  JPH::BodyID floorId = bodies.CreateAndAddBody(floorSettings, JPH::EActivation::DontActivate);

  JPH::BodyCreationSettings sphereSettings(
      new JPH::SphereShape(0.5f), JPH::RVec3(0.0f, 2.0f, 0.0f),
      JPH::Quat::sIdentity(), JPH::EMotionType::Dynamic, Layers::MOVING);
  JPH::BodyID sphereId = bodies.CreateAndAddBody(sphereSettings, JPH::EActivation::Activate);

  // Worth calling once after the bodies are inserted in bulk, never per frame.
  system.OptimizeBroadPhase();

  const float deltaTime = 1.0f / 60.0f;

  while (bodies.IsActive(sphereId)) {
    JPH::RVec3 position = bodies.GetCenterOfMassPosition(sphereId);
    std::printf("%4.2f %4.2f %4.2f\n", float(position.GetX()),
                float(position.GetY()), float(position.GetZ()));

    // One collision step per 1/60th of a second of the passed time.
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

Keep the `PhysicsSystem::Update()` step fixed (`1/60` of a second is the
recommended one) and raise the collision step count instead of the step size
when more time has to be consumed at once, otherwise the simulation loses its
stability. The `JPH_SUPPRESS_WARNINGS` macro silences the warnings the Jolt
headers trigger in the including translation unit.
