## Вмикання інтеграції Box2D

Для того щоб увімкнути бібліотеку симуляції двовимірної фізики твердих тіл [Box2D](https://box2d.org/) для проекту, використовуючи встановлену версію або через завантаження з мережі, необхідно встановити значення `ON` для CMake змінної `ENABLE_BOX2D`:

```
# в середині кореневої директорії проекту

cmake -S . -B build -DENABLE_BOX2D=ON
```

Дивись модуль `cmake/enablers/physics/template-project-box2d-enabler.cmake` щодо цілі (`box2d::box2d` як для системної версії, так і для побудови через FetchContent), яку слід прилінкувати до твоїх цільових об'єктів.

Версія, що завантажується, визначається CMake змінною `TEMPLATE_APP_BOX2D_GIT_TAG` (типово `v3.1.1`). Зверни увагу, що гілка `3.x` Box2D надає звичайний C API навколо непрозорих дескрипторів `b2WorldId` / `b2BodyId`, на відміну від C++ класів гілки `2.x`.

### Симуляція потрібних тіл (приклади для копіювання)

Після `ENABLE_BOX2D=ON` та прилінкування цілі Box2D (наприклад `target_link_libraries(${PROJECT_BINARY_NAME} box2d::box2d)`) підключи `<box2d/box2d.h>` і скопіюй будь-який зі сніпетів нижче.

Світ зі статичною землею та динамічною коробкою, що падає на неї — увесь життєвий цикл Box2D в одній функції:

```cpp
#include <box2d/box2d.h>

#include <cstdio>

void box2d_falling_box()
{
  // Світ утримує усі тіла та керує симуляцією. Кожна структура опису Box2D
  // має походити зі свого b2Default*() породжувача.
  b2WorldDef worldDef = b2DefaultWorldDef();
  worldDef.gravity = b2Vec2{0.0f, -10.0f};
  b2WorldId worldId = b2CreateWorld(&worldDef);

  // Земля: тіла є статичними, доки опис не каже інакше.
  b2BodyDef groundDef = b2DefaultBodyDef();
  groundDef.position = b2Vec2{0.0f, -10.0f};
  b2BodyId groundId = b2CreateBody(worldId, &groundDef);

  // b2MakeBox() приймає половину ширини та половину висоти, тож це плита
  // землі розміром 100x20 метрів.
  b2Polygon groundBox = b2MakeBox(50.0f, 10.0f);
  b2ShapeDef groundShapeDef = b2DefaultShapeDef();
  b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);

  // Тіло, що падає: динамічному потрібна щонайменше одна форма з ненульовою
  // щільністю, щоб його маса була обчислена.
  b2BodyDef boxDef = b2DefaultBodyDef();
  boxDef.type = b2_dynamicBody;
  boxDef.position = b2Vec2{0.0f, 4.0f};
  b2BodyId boxId = b2CreateBody(worldId, &boxDef);

  b2Polygon dynamicBox = b2MakeBox(1.0f, 1.0f);
  b2ShapeDef shapeDef = b2DefaultShapeDef();
  shapeDef.density = 1.0f;
  shapeDef.material.friction = 0.3f;
  b2CreatePolygonShape(boxId, &shapeDef, &dynamicBox);

  // Тримай крок часу сталим та незалежним від частоти кадрів: змінний крок
  // дає змінні результати. 4 підкроки — рекомендоване значення.
  const float timeStep = 1.0f / 60.0f;
  const int subStepCount = 4;

  for (int i = 0; i < 90; ++i) {
    b2World_Step(worldId, timeStep, subStepCount);

    b2Vec2 position = b2Body_GetPosition(boxId);
    b2Rot rotation = b2Body_GetRotation(boxId);
    std::printf("%4.2f %4.2f %4.2f\n", position.x, position.y,
                b2Rot_GetAngle(rotation));
  }

  // Знищення світу знищує кожне тіло та форму, які він утримує.
  b2DestroyWorld(worldId);
}
```

### Керування світом із циклу застосунку

Справжній застосунок створює світ один раз, просуває його на сталий крок на
кожному кадрі та зчитує перетворення тіл для відмальовування:

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

  // Накопичуй час кадру та споживай його сталими за розміром кроками, щоб
  // симуляція лишалася детермінованою за будь-якої частоти кадрів.
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

Виклики `b2Body_GetPosition()` та `b2Body_GetRotation()` дають перетворення для
передачі у відмальовування (`b2Rot_GetAngle()` перетворює повернений `b2Rot` на
радіани). Box2D налаштований на метри, кілограми та секунди, тож масштабуй
одиниці світу до реальних розмірів і переводь їх у пікселі екрана під час
відмальовування.
