## Опції супровідника проекту

Цілі пакувальників, які вбудовують особу супровідника у згенерований артефакт (DEB, RPM, FreeBSD pkg, WIX MSI), беруть її з спільної пари Meson-опцій:

| Опція | За замовчуванням | Використовується |
|---|---|---|
| `-DPROJECT_MAINTAINER='Імʼя Прізвище'` | `Your Name` | `deb`, `rpm`, `freebsd-pkg`, `wix` |
| `-DPROJECT_MAINTAINER_EMAIL='you@example.com'` | `yourname@your.email.org` | `deb`, `rpm`, `freebsd-pkg` |

Ці опції можна комбінувати з будь-яким із перемикачів-вмикачів пакувальників, описаних у відповідних підсекціях. Наприклад:

```
meson setup build -DENABLE_DEB=true \
  -DPROJECT_MAINTAINER='Імʼя Прізвище' \
  -DPROJECT_MAINTAINER_EMAIL='you@example.com'
meson compile -C build deb
```

Залишення цих опцій у значеннях за замовчуванням все одно дозволить отримати робочий пакет, проте метадані не будуть правильно ідентифікувати проект - встановлюй опції перед публікацією артефактів.
