## Enabling the inja HTML templates library

In order to enable the [inja](https://github.com/pantor/inja) library (the Jinja2 like templates engine) for the HTML pages of the project by using the installed system one (e.g. the Fedora `inja-devel` package or the FreeBSD `devel/inja` port) or by fetching it through the available connection set an `ON` value to the `ENABLE_INJA` CMake variable.

```
# Inside the source root directory

cmake -S . -B build -DENABLE_INJA=ON
```

The `cmake/enablers/template-project-inja-enabler.cmake` module links the `pantor::inja` target to the pages builders (the `TemplatePagesBuildersObj` object library) and their component tests, so the `src/beasthttp/pages` sources may render the HTML templates right away:

```
#include <inja/inja.hpp>

nlohmann::json data;
data["name"] = project_decls::PROJECT_NAME;

sctx->response.body() += inja::render("<h1>Hello from {{ name }}!</h1>", data);
```

The fetched inja takes the system or the `ENABLE_NLOHMANN_JSON` provided nlohmann JSON library when available and the embedded copy of its own otherwise.
