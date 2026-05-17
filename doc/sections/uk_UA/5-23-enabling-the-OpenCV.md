## Вмикання інтеграції OpenCV

Гілка `appOpenCV` шаблонного проекту інтегрує бібліотеку компʼютерного зору [OpenCV](https://opencv.org/) через окремий CMake-модуль [cmake/enablers/template-project-OpenCV-enabler.cmake](/cmake/enablers/template-project-OpenCV-enabler.cmake).

Інтеграція увімкнена за замовчуванням через CMake-змінну `ENABLE_OPENCV`:

```
# всередині кореневої директорії проекту

cmake -B build -S . -DENABLE_OPENCV=ON
cmake --build build --target all
```

За замовчуванням модуль виконує пошук системної установки OpenCV через `find_package(OpenCV REQUIRED COMPONENTS core objdetect imgcodecs imgproc)`. Перелік компонентів можна змінити через кеш-змінну `TEMPLATE_APP_OPENCV_COMPONENTS` (значення розділяються крапкою з комою).

Після збирання застосунок підтримує два нових параметри командного рядка:

- `--image <шлях>` / `-i <шлях>` - виконати виявлення обличь OpenCV на вказаному зображенні.
- `--face-cascade <шлях>` - перевизначити XML-файл каскаду Хаара, який використовує детектор.

Якщо жоден з параметрів не передано, застосунок лише перевіряє, що попередньо встановлений каскад можна завантажити, і коректно завершує роботу.

XML-файл каскаду Хаара, який постачається разом з системною установкою OpenCV (`haarcascade_frontalface_default.xml`), автоматично шукається у наступних відомих локаціях:

- `/usr/share/opencv4/haarcascades/haarcascade_frontalface_default.xml` (Debian/Ubuntu, пакет `opencv-data`)
- `/usr/share/opencv/haarcascades/haarcascade_frontalface_default.xml`
- `/usr/local/share/opencv4/haarcascades/haarcascade_frontalface_default.xml`
- `/usr/local/share/opencv/haarcascades/haarcascade_frontalface_default.xml`
- Шляхи macOS Homebrew у `/usr/local/Cellar` і `/opt/homebrew`

Деталі публічного інтерфейсу інтеграції шукай у файлі [src/opencv/OpenCVController.h](/src/opencv/OpenCVController.h) (клас `opencvi::OpenCVController`).
