## Вмикання інтеграції OpenCV

Гілка `appOpenCV` шаблонного проекту інтегрує бібліотеку компʼютерного зору [OpenCV](https://opencv.org/) через окремий CMake-модуль [cmake/enablers/template-project-OpenCV-enabler.cmake](/cmake/enablers/template-project-OpenCV-enabler.cmake).

Інтеграція увімкнена за замовчуванням через CMake-змінну `ENABLE_OPENCV`:

```
# всередині кореневої директорії проекту

cmake -B build -S . -DENABLE_OPENCV=ON
cmake --build build --target all
```

Файл `src/opencv/CMakeLists.txt` шукає системну установку OpenCV через `find_package(OpenCV REQUIRED COMPONENTS core objdetect imgcodecs imgproc)`, оскільки бібліотеку використовують і його тести. Перелік компонентів можна змінити через кеш-змінну `TEMPLATE_APP_OPENCV_COMPONENTS` (значення розділяються крапкою з комою).

Оскільки приклад `src/opencv` потребує бібліотеки, значення `OFF` параметра `ENABLE_OPENCV` зупиняє конфігурацію з поясненням, доки з файлу `src/CMakeLists.txt` не буде вилучено виклик `add_subdirectory(opencv)` разом з підкаталогом `src/opencv` і прикладом OpenCV у файлі `src/app/applications/Application.cpp`.

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

Метод `app::Application::run` лише делегує виклик до `opencvi::OpenCVController::run` для того щоб можна було швидко перемикатися між наявними прикладами OpenCV без редагування компоненту `app`. Поточний диспетчер викликає `opencvi::OpenCVController::face_recognition_example`, в якому розміщено код завантаження каскаду Хаара і сканування зображення. Щоб додати новий приклад - оголоси новий метод у класі `opencvi::OpenCVController` і переадресуй на нього виклик з `opencvi::OpenCVController::run`.

Деталі публічного інтерфейсу інтеграції шукай у файлі [src/opencv/OpenCVController.h](/src/opencv/OpenCVController.h) (клас `opencvi::OpenCVController`).
