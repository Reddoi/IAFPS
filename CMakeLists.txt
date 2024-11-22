cmake_minimum_required(VERSION 3.29)
project(IAFPS_Proiect)

set(CMAKE_CXX_STANDARD 20)

set(SQLite3_INCLUDE_DIR "C:/sqlite")

include_directories(${SQLite3_INCLUDE_DIR})
add_executable(IAFPS_Proiect WIN32 main.cpp
        Reteta.h
        Ingredient.h
        Instructiune.h
        functiiVizualizare.cpp
        functiiBazaDeDate.cpp
        functiiBazaDeDate.h
        functiiVizualizare.h
        RetetaIngredient.h
        MyApp.h
        MainFrame.h
        MainFrame.cpp
        DecisionTreeClassifier.cpp
        DecisionTreeClassifier.h
        Simplex.h
        Simplex.cpp
)
find_package(wxWidgets CONFIG REQUIRED)
find_package(unofficial-sqlite3 CONFIG REQUIRED)
find_package(unofficial-libsvm CONFIG REQUIRED)
find_path(MLPACK_INCLUDE_DIRS "mlpack.hpp")
target_include_directories(IAFPS_Proiect PRIVATE ${MLPACK_INCLUDE_DIRS})
target_link_libraries(IAFPS_Proiect PRIVATE unofficial::sqlite3::sqlite3 wx::core wx::base unofficial::libsvm::libsvm)
