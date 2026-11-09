cmake_minimum_required(VERSION 3.24)
project(kursach)

set(CMAKE_CXX_STANDARD 17)

# 1. Настройка путей в соответствии с твоими папками
if(WIN32)
    # Используем твою папку sfml-win-x64
    set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/sfml-win-x64/lib/cmake/SFML")
    set(SFML_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/sfml-win-x64/include")
elseif(APPLE)
    # Используем твою папку sfml-osx
    set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/sfml-osx/lib/cmake/SFML")
    set(SFML_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/sfml-osx/include")
endif()

# 2. Поиск SFML
find_package(SFML 2.6 COMPONENTS system window graphics audio network REQUIRED)

# 3. Объявление исполняемого файла и всех исходников
add_executable(kursach 
    
    Tetris/src/board.cpp
    Tetris/src/game.cpp
    Tetris/src/gamestate.cpp
    Tetris/src/main.cpp 
    Tetris/src/playstate.cpp
    Tetris/src/score.cpp
    Tetris/src/tetrimino.cpp
)

# 4. Подключение папки include (чтобы работало #include <SFML/Graphics.hpp>)
target_include_directories(kursach PRIVATE ${SFML_INCLUDE_DIR})

# Добавляем путь к исходникам тетриса, чтобы main.cpp видел game.h
target_include_directories(kursach PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Tetris/src")

# 5. Линковка библиотек
target_link_libraries(kursach sfml-graphics sfml-window sfml-system sfml-audio sfml-network)

# 6. Автоматическое копирование DLL для Windows (чтобы игра запустилась)
if(WIN32)
    add_custom_command(TARGET kursach POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/external/sfml-win-x64/bin"
        $<TARGET_FILE_DIR:kursach>
    )
endif()

# Копируем папку с ресурсами (картинки, шрифты) в папку сборки
add_custom_command(TARGET kursach POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/Tetris/data"
    $<TARGET_FILE_DIR:kursach>/data
)