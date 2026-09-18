## Вмикання пакування застосунку робочого столу

Віконний (GUI) застосунок належить до меню застосунків робочого столу, тоді як консольний запускається всередині термінала. CMake змінна `ENABLE_DESKTOP_APPLICATION` повідомляє пакувальникам, до якого виду належить бінарний файл проекту - GUI гілки шаблону типово вмикають її, а консольні залишають вимкненою:

```
# в середині кореневої директорії проекту

cmake -S . -B build -DENABLE_DESKTOP_APPLICATION=ON
```

Коли змінна увімкнена, крок встановлення розміщує [файл робочого столу](https://specifications.freedesktop.org/desktop-entry-spec/latest/) і піктограму застосунку в каталогах `share/applications` та `share/icons/hicolor/scalable/apps`, обидва названі за зворотним DNS ідентифікатором застосунку (наприклад, `ua.org.kytok.template.CppAppTemplate.desktop`), і кожен пакувальник позначає застосунок як застосунок робочого столу:

- flatpak експортує файл робочого столу та піктограму до меню робочого столу, а його метаінформація [AppStream](https://www.freedesktop.org/software/appstream/docs/) стає компонентом `desktop-application`, який запускається через цей файл робочого столу;
- snap отримує файл робочого столу та інтерфейси `desktop`, `desktop-legacy`, `wayland`, `x11` і `opengl`, потрібні вікну;
- файл робочого столу AppImage отримує ключ `Terminal=false`;
- пакунки DEB, RPM та FreeBSD pkg містять файл робочого столу та піктограму, тож меню робочого столу показують встановлений застосунок.

Файл робочого столу та піктограма конфігуруються з шаблонів каталогу [misc/packagers/desktop](/misc/packagers/desktop), які AppImage використовує й для консольного застосунку:

- [desktop.entry.in](/misc/packagers/desktop/desktop.entry.in) - файл робочого столу;
- [desktop.icon.svg.in](/misc/packagers/desktop/desktop.icon.svg.in) - піктограма, яку називає файл робочого столу.

Наступні змінні кешу можливо за бажанням перевизначити:

- `TEMPLATE_PROJECT_DESKTOP_CATEGORIES` - завершений крапкою з комою перелік категорій файлу робочого столу (типово: `Utility;`). Іншими типовими значеннями є `Development;`, `Network;`, `Graphics;`.
- `DESKTOP_ICON_SRC` - файл-джерело піктограми SVG (типово: наведений вище шаблон).

Детальніше у файлі [cmake/enablers/packagers/template-project-desktop-entry.cmake](/cmake/enablers/packagers/template-project-desktop-entry.cmake).
