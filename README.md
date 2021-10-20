# LOGGER


## Installation

### Install library 

```shell
curl -L -o Logger.zip https://github.com/ita-social-projects/HTTP_Messenger_Logger/releases/tag/release/Logger.zip
```

Or install manually <a href="https://github.com/ita-social-projects/HTTP_Messenger_Logger/releases/tag/release"> here </a>

### Unzip library to your project

### Include Logger to your project

- CMake

Add the following text to your CMakeList.txt

```CMake
target_link_libraries(${CMAKE_PROJECT_NAME} ${CMAKE_SOURCE_DIR}/lib/Logger.lib)
```

- QMake

Add the following text to your .pro file
```QMake
DEPENDPATH += . $$PWD/Logger/
INCLUDEPATH += $$PWD/Logger/
LIBS += -L$$PWD/Logger -lLogger

CONFIG += c++11
TEMPLATE = app
```
### Include "Logger.h" in your code
```c++
#include "Logger.h"
```
---

## Contributing

#### Step 1

- **Option 1**
    - 🍴 Fork this repo!

- **Option 2**
    - 👯 Clone this repo to your local machine using `https://github.com/ita-social-projects/SOMEREPO.git`

#### Step 2

- **HACK AWAY!** 🔨🔨🔨

#### Step 3

- 🔃 Create a new pull request using <a href="https://github.com/ita-social-projects/SOMEREPO/compare/" target="_blank">github.com/ita-social-projects/SOMEREPO</a>.

---
## Issue flow

No isses 🙂

---

## Team

### Or Contributors/People

[![@AndrianKupyniak](https://avatars.githubusercontent.com/u/88183610?s=100&v=2)](https://github.com/AndrianKupyniak)

---

## License

[![License](http://img.shields.io/:license-mit-blue.svg?style=flat-square)](http://badges.mit-license.org)

- **[MIT license](http://opensource.org/licenses/mit-license.php)**
- Copyright 2020 © <a href="https://softserve.academy/" target="_blank"> SoftServe IT Academy</a>.
