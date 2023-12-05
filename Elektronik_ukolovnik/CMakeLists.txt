# CMakeList.txt: Projekt CMake pro Elektronik_ukolovnik, sem přidejte logiku zdrojového
# kódu a definic specifickou pro projekt.
#

# Přidejte zdrojový kód ke spustitelnému souboru tohoto projektu.
add_executable (Elektronik_ukolovnik "Elektronik_ukolovnik.cpp" "Elektronik_ukolovnik.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Elektronik_ukolovnik PROPERTY CXX_STANDARD 20)
endif()

# TODO: V případě potřeby přidejte testy a cíle instalace.
