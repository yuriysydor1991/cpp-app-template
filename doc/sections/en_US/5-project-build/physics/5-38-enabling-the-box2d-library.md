## Enabling the Box2D library

In order to enable the [Box2D](https://box2d.org/) 2D rigid body physics simulation library for the project by using the installed system one or by fetching it through the available connection set an `ON` value to the `ENABLE_BOX2D` CMake variable.

```
# Inside the source root directory

cmake -S . -B build -DENABLE_BOX2D=ON
```

See the `cmake/enablers/physics/template-project-box2d-enabler.cmake` module for the target (`box2d::box2d` for both a system install and the FetchContent build) to link to your targets of interest.

The fetched revision is driven by the `TEMPLATE_APP_BOX2D_GIT_TAG` CMake variable (`v3.1.1` by default). Note that the `3.x` line of Box2D exposes a plain C API built around opaque `b2WorldId` / `b2BodyId` handles, unlike the C++ classes of the `2.x` line.

### Simulating the bodies of interest (copy-paste examples)

After `ENABLE_BOX2D=ON` and linking the Box2D target (e.g. `target_link_libraries(${PROJECT_BINARY_NAME} box2d::box2d)`), include `<box2d/box2d.h>` and copy-paste any of the snippets below.

A world with a static ground and a dynamic box falling onto it — the whole Box2D lifecycle in one function:

```cpp
#include <box2d/box2d.h>

#include <cstdio>

void box2d_falling_box()
{
  // A world holds all the bodies and drives the simulation. Every Box2D
  // definition structure must come from its b2Default*() maker.
  b2WorldDef worldDef = b2DefaultWorldDef();
  worldDef.gravity = b2Vec2{0.0f, -10.0f};
  b2WorldId worldId = b2CreateWorld(&worldDef);

  // The ground: bodies are static unless the definition says otherwise.
  b2BodyDef groundDef = b2DefaultBodyDef();
  groundDef.position = b2Vec2{0.0f, -10.0f};
  b2BodyId groundId = b2CreateBody(worldId, &groundDef);

  // b2MakeBox() takes the half width and the half height, so this is a
  // 100x20 meters ground slab.
  b2Polygon groundBox = b2MakeBox(50.0f, 10.0f);
  b2ShapeDef groundShapeDef = b2DefaultShapeDef();
  b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);

  // The falling body: a dynamic one needs at least a single shape with a
  // non zero density to get its mass computed.
  b2BodyDef boxDef = b2DefaultBodyDef();
  boxDef.type = b2_dynamicBody;
  boxDef.position = b2Vec2{0.0f, 4.0f};
  b2BodyId boxId = b2CreateBody(worldId, &boxDef);

  b2Polygon dynamicBox = b2MakeBox(1.0f, 1.0f);
  b2ShapeDef shapeDef = b2DefaultShapeDef();
  shapeDef.density = 1.0f;
  shapeDef.material.friction = 0.3f;
  b2CreatePolygonShape(boxId, &shapeDef, &dynamicBox);

  // Keep the time step fixed and independent of the frame rate: a varying
  // step produces varying results. 4 sub steps is the suggested value.
  const float timeStep = 1.0f / 60.0f;
  const int subStepCount = 4;

  for (int i = 0; i < 90; ++i) {
    b2World_Step(worldId, timeStep, subStepCount);

    b2Vec2 position = b2Body_GetPosition(boxId);
    b2Rot rotation = b2Body_GetRotation(boxId);
    std::printf("%4.2f %4.2f %4.2f\n", position.x, position.y,
                b2Rot_GetAngle(rotation));
  }

  // Destroying the world destroys every body and shape it holds.
  b2DestroyWorld(worldId);
}
```

### Driving the world from the application loop

A real application creates the world once, advances it by a fixed step on every
frame and reads the body transforms back for the rendering:

```cpp
#include <box2d/box2d.h>

class Physics2D
{
 public:
  Physics2D()
  {
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = b2Vec2{0.0f, -9.81f};
    world = b2CreateWorld(&worldDef);
  }

  ~Physics2D() { b2DestroyWorld(world); }

  b2BodyId add_dynamic_box(float x, float y, float halfWidth, float halfHeight)
  {
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = b2Vec2{x, y};
    b2BodyId bodyId = b2CreateBody(world, &bodyDef);

    b2Polygon box = b2MakeBox(halfWidth, halfHeight);
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    b2CreatePolygonShape(bodyId, &shapeDef, &box);

    return bodyId;
  }

  // Accumulate the frame time and consume it in fixed sized steps so that the
  // simulation stays deterministic whatever the frame rate is.
  void advance(float frameSeconds)
  {
    accumulator += frameSeconds;
    while (accumulator >= step) {
      b2World_Step(world, step, 4);
      accumulator -= step;
    }
  }

 private:
  static constexpr float step = 1.0f / 60.0f;

  b2WorldId world{};
  float accumulator{0.0f};
};
```

The `b2Body_GetPosition()` and `b2Body_GetRotation()` calls give the transform to
feed into the rendering (`b2Rot_GetAngle()` converts the returned `b2Rot` into
radians). Box2D is tuned for meters, kilograms and seconds, so scale the world
units to the real world sizes and convert to the screen pixels while drawing.
