## Вмикання інтеграції бібліотеки HTML шаблонів inja

Для того щоб увімкнути бібліотеку [inja](https://github.com/pantor/inja) (рушій шаблонів у стилі Jinja2) для HTML сторінок проекту, використовуючи встановлену версію (наприклад, пакет `inja-devel` у Fedora або порт `devel/inja` у FreeBSD) або через завантаження з мережі, необхідно встановити значення `ON` для CMake змінної `ENABLE_INJA`:

```
# в середині кореневої директорії проекту

cmake -S . -B build -DENABLE_INJA=ON
```

Модуль `cmake/enablers/template-project-inja-enabler.cmake` лінкує ціль `pantor::inja` до будівників сторінок (об'єктна бібліотека `TemplatePagesBuildersObj`) та їх компонентних тестів, тож джерельні файли `src/beasthttp/pages` можуть одразу формувати HTML шаблони:

```
#include <inja/inja.hpp>

nlohmann::json data;
data["name"] = project_decls::PROJECT_NAME;

sctx->response.body() += inja::render("<h1>Hello from {{ name }}!</h1>", data);
```

Завантажена з мережі inja використовує системну бібліотеку nlohmann JSON або ту, яку надає опція `ENABLE_NLOHMANN_JSON`, за їх наявності, і власну вбудовану копію в іншому разі.
