cmake_minimum_required(VERSION 3.12)
project(CarTracking)

set(CMAKE_CXX_STANDARD 17)
#add_definitions(-DDEBUG)

find_package(OpenCV REQUIRED)

# Ajoutez le répertoire "include" aux chemins d'inclusion
include_directories(include)

# Liste des fichiers source de votre projet
set(SOURCES
    src/Image.cpp
    src/Video.cpp
    main.cpp
)

add_executable(main ${SOURCES})

# Liaison avec la bibliothèque OpenCV
target_link_libraries(main PRIVATE ${OpenCV_LIBS})
